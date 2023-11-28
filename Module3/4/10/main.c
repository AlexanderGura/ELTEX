#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <time.h>
#include "func.h"

extern int is_active;
extern struct sembuf lock;
extern struct sembuf unlock[2];

int main()
{
	srand(time(0));

	signal(SIGINT, hand_sigint);

	const char *mname = "memory";
	const char *semname = "semaphore";
	const int nums_len = rand() % 10;
	const int size = sizeof(int) * (nums_len + OPC_COUNT);
	printf("count - %d\n", nums_len);

	int shmid = shm_open(mname, O_CREAT | O_RDWR, 0666);
	if (shmid == -1)
		perror("shm_open\n");
	if (ftruncate(shmid, size) == -1)
		perror("fruncate\n");

	sem_t *semid = sem_open(semname, O_CREAT | O_RDWR , 0666, 1);
	if (semid == SEM_FAILED)
		perror("sem_open\n");

	int *nums = (int *) mmap(NULL, size,
		PROT_READ | PROT_WRITE, MAP_SHARED, shmid, 0);
	if (nums == (int *)(-1))
		perror("mmap\n");

	int  package;
	pid_t pid = fork();
	switch(pid)
	{
	case -1:
		perror("fork");
	case 0:
		child(semid, nums, nums_len, 0);
	default:
		pid = fork();
		switch(pid)
		{
		case -1:
			perror("fork");
		case 0:
			child(semid, nums, nums_len, 1);
		default:
			pid = fork();
			switch(pid)
			{
			case -1:
				perror("fork");
			case 0:
				child(semid, nums, nums_len, 2);
			default:
				pid = fork();
				switch(pid)
				{
					case -1:
						perror("fork");
					case 0:
						child(semid, nums, nums_len, 3);
					default:
						break;
				}
				break;
			}
			break;
		}

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
			printf("min - %d\n", nums[nums_len + 0]);
			printf("max - %d\n", nums[nums_len + 1]);
			printf("sum - %d\n", nums[nums_len + 2]);
			printf("avr - %d\n", nums[nums_len + 3]);
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
