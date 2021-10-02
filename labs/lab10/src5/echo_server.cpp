/*
** echo_server.cpp -- the echo server for echo_cient.cpp; demonstrates UNIX sockets
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCK_PATH "echo_socket"

int main(void)
{
	int s, s2, t, len;
	struct sockaddr_un local, remote;
	char str[100];

	if ((s = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		exit(1);
	}

	local.sun_family = AF_UNIX;
//	remote.sun_family = AF_UNIX;       //
	strcpy(local.sun_path, SOCK_PATH);
	unlink(local.sun_path);
	len = strlen(local.sun_path) + sizeof(local.sun_family);
	if (bind(s, (struct sockaddr *)&local, len) == -1) {
		perror("bind");
		exit(1);
	}

	if (listen(s, 5) == -1) {
		perror("listen");
		exit(1);
	}

	for(;;) {
		int done, n;
		t = sizeof(remote);
		if ((s2 = accept(s, (struct sockaddr *)&remote, (socklen_t *)&t)) == -1) {
			perror("accept");
			exit(1);
		}
		printf("\nClient %d connected\n",s2);
		int cpid = (int) fork();
		switch(cpid){
			case -1:
				perror("Bad fork");
				exit(2);
			case 0:
				
				done = 0;
				do {
					n = recv(s2, str, 100, 0);
					if (n <= 0) {
						if (n < 0) perror("recv");
							done = 1;
						}

						if (!done) 
							printf("\nclient %d -> %s",s2,str);
							printf("client %d <- %s",s2,str);
							if (send(s2, str, n, 0) < 0) {
							perror("send");
							done = 1;
							}
				} while (!done);
				printf("\nClient %d disconnected\n",s2);
				close(s2);
				break;
			default:
				continue;
		}
		
	} 

		
	

	return 0;
}



