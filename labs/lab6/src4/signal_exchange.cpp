#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

main(void)
{
	void signal1(int);

	if (signal(SIGUSR1, signal1) == SIG_ERR)
	{
		exit(1);
	}

	if (signal(SIGUSR2, signal1) == SIG_ERR)
	{
		exit(2);
	}

	int p_pid = getpid();
	int c_pid = fork();
	if (c_pid == -1)
	{
		perror("Bad fork");
		exit(4);
	}

	if (c_pid == 0)
	{
		c_pid = getpid();
		printf("Child PID: %d\n\n", c_pid);

		for (int i = 1;; i++)
		{
			sleep(1);
			switch (i % 3)
			{
				case 0:
					kill(c_pid, SIGUSR1);
					break;
				case 1:
					kill(p_pid, SIGUSR1);
					break;
				default:
					kill(p_pid, SIGUSR2);
			}
		}
	}
	else
	{
		printf("Parent PID: %d\n", p_pid);

		for (int i = 1;; i++)
		{
			sleep(1);
			switch (i % 3)
			{
				case 0:
					kill(c_pid, SIGUSR1);
					break;
				case 1:
					kill(c_pid, SIGUSR2);
					break;
				default:
					kill(p_pid, SIGUSR2);
			}
		}
	}
}

void signal1(int the_sig)
{
	signal(the_sig, signal1);
	printf("Signal %d received on %d\n\n", the_sig, getpid());

}
