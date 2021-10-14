#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
int main() 
{
 pid_t PID;
 PID = fork();
 int i;
if (PID) {    /* I must be the parent  */
    for(i=0; i<1000 ; i++) sleep(7);
    }
else {      /* I must be the child   */
    for(i=0; i<1000 ; i++) sleep(7);
    }
    return 0;
}
