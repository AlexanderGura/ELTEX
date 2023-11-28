#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
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
	const int nums_len = rand() % 10;

	int shmid = shmget(IPC_PRIVATE,
		sizeof(int) * (nums_len + OPC_COUNT), 0666 | IPC_CREAT);
	if (shmid == -1)
		perror("shmget\n");

	int semid = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT);
	if (semid == -1)
		perror("semget\n");

	union semun arg;
	arg.val = 1;
	semctl(semid, 0, SETVAL, arg);

	int *nums = (int *) shmat(shmid, NULL, 0);
	if (nums == (int *)(-1))
		perror("shmat\n");

	int max, min, package;
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

			sleep(1);
			semop(semid, &lock, 1);
			printf("min - %d\n", nums[nums_len + 0]);
			printf("max - %d\n", nums[nums_len + 1]);
			printf("sum - %d\n", nums[nums_len + 2]);
			printf("avr - %d\n", nums[nums_len + 3]);
			semop(semid, unlock, 2);
		}
		if (shmdt(nums) == -1)
			perror("shmdt\n");
	}
	sleep(1);

	printf("Count of package - %d\n", package);

	if (shmctl(shmid, IPC_RMID, NULL) == -1)
		perror("shmctl\n");

	if (semctl(semid, 0, IPC_RMID) == -1)
		perror("semctl\n");

	return 0;
}
