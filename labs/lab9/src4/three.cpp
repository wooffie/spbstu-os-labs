/*
** shmdemo.cpp -- read and write to a shared memory segment
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1023  /* make it a 1K - 1 shared memory segment */

int main()
{
	int shmid_1, shmid_2,shmid_3;
	char *data_1 , *data_2, *data_3;
	int mode;
	if ((shmid_1=shmget(0, SHM_SIZE, 0644|IPC_CREAT)) == -1){
    			perror("shmget shmid_1");
    			exit(1);
    			}
    	if ((shmid_2=shmget(0, SHM_SIZE, 0644|IPC_CREAT)) == -1){
    			perror("shmget shmid_1");
    			exit(1);
    			}
    	if ((shmid_3=shmget(0, SHM_SIZE, 0644|IPC_CREAT)) == -1){
    			perror("shmget shmid_1");
    			exit(1);
    			}

	data_1 = (char *) shmat(shmid_1, 0, 0);
		if (data_1 == (char *)(-1)) {
			perror("shmat");
			exit(1);
			}
	data_2 = (char *) shmat(shmid_1, 0, 0);
		if (data_1 == (char *)(-1)) {
			perror("shmat");
			exit(1);
			}
	data_3 = (char *) shmat(shmid_1, 0, 0);
		if (data_1 == (char *)(-1)) {
			perror("shmat");
			exit(1);
			}
	
	
	return 0;
}
