#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
int main() {
	FILE *ptr;
	size_t length = 0;
	ssize_t upcome;
	char* buf = (char*)malloc (100*sizeof(char));
	if ((ptr = fopen("input.txt", "r")) == NULL) {
		printf("File error occured\n");
		exit(1);
	}
	if (fork() == 0){
		if((upcome = getline(&buf, &length, ptr)) != -1) printf("Child: %s", buf);
		exit(0);
	} else {
		wait(NULL);
		if((upcome = getline(&buf, &length, ptr)) != -1) printf("Parent: %s", buf);
		fclose(ptr);
	}
	free(buf);
	return 0;
}