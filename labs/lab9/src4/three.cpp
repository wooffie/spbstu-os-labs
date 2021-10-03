/*
** shmdemo.cpp -- read and write to a shared memory segment
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1023  /* make it a 1K shared memory segment */

int main()
{
	int shmid;
	char *data;
	int mode;
	for(int i = 0;i < 3; i++){
		
		/* make the key: */

		/* connect to (and possibly create) the segment: */
		if ((shmid = shmget(15*i, SHM_SIZE, 0644 | IPC_CREAT)) == -1) {
			perror("shmget");
			exit(1);
		}

		/* attach to the segment to get a pointer to it: */
		data = (char *) shmat(shmid, 0, 0);
		if (data == (char *)(-1)) {
			perror("shmat");
			exit(1);
		}

		
	
}
	
	return 0;
}
