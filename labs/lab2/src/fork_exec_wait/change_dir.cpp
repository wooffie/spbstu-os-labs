#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
int main()
{
 int i;
  if (fork()) {  /*I must be the parent */
	printf("\n %s \n", get_current_dir_name());
	for(i=0; i<15 ; i++)
		printf("\t\tPARENT %d\n", i);
		sleep(7);
	}
  else {  /*I must be the child */
	printf("\n %d \n", chdir("home/zina/OS"));
	printf("\n %s \n", get_current_dir_name());
	for(i=0; i<15 ; i++)
		printf("CHILD %d\n",i);
		sleep(7);
	}
  return 0;
}
