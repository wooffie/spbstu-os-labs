#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<limits.h>

int main(int argc, char *argv[])
{
	FILE *fin, *fout;
	char buf[PIPE_BUF];
	if (argc < 3) 
	{
		fprintf(stderr, "Usage %s cmd1 cmd2 ...\n", argv[0]);
		exit(1);
	}
	int n;
	for (int i = 1; i < argc - 2; i++)
	{
		if ((fin = popen(argv[1], "r"))==NULL)
		{
			fprintf(stderr, "err");
			exit(1);
		}
		if ((fout = popen(argv[2], "w"))==NULL)
		{
			fprintf(stderr, "err");
			exit(1);
		}
		if ((n = read(fileno(fin), buf, PIPE_BUF))==-1)
		{
			fprintf(stderr, "err: not possible to read");
			exit(1);
		}
		if ((write(fileno(fout), buf, n))==-1)
		{
			fprintf(stderr, "err");
			exit(1);
		}
		if (pclose(fin)==-1) 
		{
			fprintf(stderr, "err");
			exit(1);
		}
		if (pclose(fout)==-1) 
		{
			fprintf(stderr, "err");
			exit(1);
		}
	}
}
