#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define MAX_RETRIES 10

int main(void)
{
	char u_char = 'J';
	key_t key = ftok(".", u_char);
	int semid;


	if ((semid = semget(key, 1, 0)) < 0) {
		perror("semget");
		exit(1);
	}


	int waitingCount;
	while(1) {
		waitingCount = semctl(semid, 0, GETNCNT);
		if (waitingCount < 0) {
			perror("semctl");
			exit(1);
		}
		printf("Processes in queue: %d\n", waitingCount);
		sleep(10);
	}

	return 0;
}
