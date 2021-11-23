/* The client program  pipe_client.cpp */
#include"pipe_local.h"

FILE *server;

void sigint_handler(int sig) {
    if (sig == SIGINT) {
        exit(0);
    }
}

int main(void)
{
int	n, privatefifo, publicfifo;
static char buffer[PIPE_BUF];
struct message msg;
    /* Make the name for the private FIFO */
sprintf(msg.fifo_name, "/tmp/fifo %d", getpid());
    struct sigaction sa;

	sa.sa_handler = sigint_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
    if (sigaction(SIGINT, &sa, NULL) == -1) {
            perror("sigaction");
            exit(1);
        }

    /* Generate the private FIFO */
if (mknod(msg.fifo_name, S_IFIFO | 0666, 0)<0){
    perror(msg.fifo_name);
    exit(1);
    }
    /* OPEN the public FIFO for writing */
int pid = 0;
if ((publicfifo=open(PUBLIC, O_WRONLY))==-1){
    pid = fork();
    if (pid == 0) {
        execl("./server", "&");
    }
    else {
        sleep(2);
        publicfifo=open(PUBLIC, O_WRONLY);
    }
}
while(1){	/* FOREVER */
    write(fileno(stdout), "\ncmd>", 6);
    memset(msg.cmd_line, 0x0, B_SIZ);	/* Clear first */
    n = read(fileno(stdin), msg.cmd_line, B_SIZ); /* Get cmd */
	if(!strncmp("quit", msg.cmd_line, n-1))
	break;				/* EXIT? */
    write(publicfifo, (char *) &msg, sizeof(msg)); /* to PUBLIC */
    /* OPEN private FIFO to read returned command oputput */
	if((privatefifo = open(msg.fifo_name, O_RDONLY))==-1){
	    perror(msg.fifo_name);
	    exit(3);
	    }
    /* READ private FIFO and display on standard error */
    while((n=read(privatefifo, buffer, PIPE_BUF))>0){
	write(fileno(stderr), buffer, n);
	}
	close(privatefifo);
    }
    close(publicfifo);
    unlink(msg.fifo_name);
}
