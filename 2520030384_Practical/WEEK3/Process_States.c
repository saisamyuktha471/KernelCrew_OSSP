#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
int main(){
int pid=fork();
if(pid == 0)
{
printf("Child PID: %d\n", getpid());
printf("Child PPID: %d\n", getppid());
printf("Child State: Running\n");
sleep(5);
printf("Child State: Terminated\n");
}
else
{
printf("Parent PID: %d\n", getpid());
printf("Parent PPID: %d\n", getppid());
printf("Parent State: Waiting\n");
wait(NULL);
printf("Parent State: Running\n");
}
return 0;
}
