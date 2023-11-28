#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <time.h>

int is_active = 1;

void hand_sigint(int sig)
{
	is_active = 0;
}

union semun
{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
	struct sem_info *__buf;
};

int main()
{
	srand(time(0));

	signal(SIGINT, hand_sigint);

	const char *mname = "memory";
	const char *semname = "semaphore";
	const int nums_len = rand() % 10;
	const int size = sizeof(int) * (nums_len + 2);
	printf("count - %d\n", nums_len);


	int shmid = shm_open(mname, O_CREAT | O_RDWR, 0666);
	if (shmid == -1)
		perror("shm_open\n");
	if (ftruncate(shmid, size) == -1)
		perror("fruncate\n");

	sem_t *semid = sem_open(semname, O_CREAT | O_RDWR , 0666, 1);
	if (semid == SEM_FAILED)
		perror("sem_open\n");


	pid_t pid = fork();
	int *nums = (int *) mmap(NULL, size,
		PROT_READ | PROT_WRITE, MAP_SHARED, shmid, 0);
	if (nums == (int *)(-1))
		perror("mmap\n");

	int max, min, package;
	switch(pid)
	{
		case -1:
			perror("fork");

		case 0:
			while (is_active)
			{
				sleep(1);
				sem_wait(semid);

				max = nums[0];
				min = nums[0];
				for (int i = 1; i < nums_len; i++)
				{
					if (nums[i] > max)
						max = nums[i];
					if (nums[i] < min)
						min = nums[i];
				}

				nums[nums_len] = min;
				nums[nums_len + 1] = max;

				sem_post(semid);
			}
			if (munmap(nums, size) == -1)
				perror("munmap\n");
			exit(EXIT_SUCCESS);

		default:
			while (is_active)
			{
				sem_wait(semid);
				printf("\nPackage #%d:\n", ++package);

				for (int i = 0; i < nums_len; i++)
				{
					nums[i] = rand() % 1000;
					printf("parrent: %d\n", nums[i]);
				}

				sem_post(semid);

				sleep(1);
				sem_wait(semid);
				printf("min - %d\n", nums[nums_len]);
				printf("max - %d\n", nums[nums_len + 1]);
				sem_post(semid);
			}
			if (munmap(nums, size) == -1)
				perror("munmap\n");
	}
	sleep(1);

	printf("Count of package - %d\n", package);

	if (shm_unlink(mname) == -1)
		perror("shm_unlink\n");

	if (sem_close(semid) == -1)
		perror("sem_close\n");
	if (sem_unlink(semname) == -1)
		perror("sem_unlink\n");

	return 0;
}

