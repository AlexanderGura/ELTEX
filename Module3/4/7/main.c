#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
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
	const int id = 1313;
	const int nums_len = rand() % 10;
	printf("count - %d\n", nums_len);

	struct sembuf lock = {0, -1, 0};
	struct sembuf unlock[2] = { {0, 0, 0}, {0, 1, 0} };

	int shmid = shmget(IPC_PRIVATE, sizeof(int) * (nums_len + 2), 0666 | IPC_CREAT);
	if (shmid == -1)
		perror("shmget\n");

	int semid = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT);
	if (semid == -1)
		perror("semget\n");

	union semun arg;
	arg.val = 1;
	semctl(semid, 0, SETVAL, arg);

	pid_t pid = fork();
	int *nums = (int *) shmat(shmid, NULL, 0);
	if (nums == (int *)(-1))
		perror("shmat\n");

	int max, min, package;
	switch(pid)
	{
		case -1:
			perror("fork");

		case 0:
			while (is_active)
			{
				sleep(1);
				semop(semid, &lock, 1);

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

				semop(semid, unlock, 2);
			}
			if (shmdt(nums) == -1)
				perror("shmdt\n");
			exit(EXIT_SUCCESS);

		default:
			while (is_active)
			{
				semop(semid, &lock, 1);
				printf("\nPackage #%d:\n", ++package);
				nums = (int *) shmat(shmid, NULL, 0);
				if (nums == (int *)(-1))
					perror("shmat\n");

				for (int i = 0; i < nums_len; i++)
				{
					nums[i] = rand() % 1000;
					printf("parrent: %d\n", nums[i]);
				}

				semop(semid, unlock, 2);

				sleep(5);
				semop(semid, &lock, 1);
				printf("min - %d\n", nums[nums_len]);
				printf("max - %d\n", nums[nums_len + 1]);
				semop(semid, unlock, 2);
			}
			if (shmdt(nums) == -1)
				perror("shmdt\n");
	}
	sleep(3);

	printf("Count of package - %d\n", package);

	if (shmctl(shmid, IPC_RMID, NULL) == -1)
		perror("shmctl\n");

	if (semctl(semid, 0, IPC_RMID) == -1)
		perror("semctl\n");

	return 0;
}
