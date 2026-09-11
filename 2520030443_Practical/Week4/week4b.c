#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    pid_t c1, c2, c3;

    c1 = fork();

    if(c1 == 0)
    {
        printf("Child 1: PID = %d\n", getpid());
        sleep(3);
        printf("Child 1 completed\n");
        exit(0);
    }

    c2 = fork();

    if(c2 == 0)
    {
        printf("Child 2: PID = %d\n", getpid());
        sleep(1);
        printf("Child 2 completed\n");
        exit(0);
    }

    c3 = fork();

    if(c3 == 0)
    {
        printf("Child 3: PID = %d\n", getpid());
        sleep(2);
        printf("Child 3 completed\n");
        exit(0);
    }

    waitpid(c2, NULL, 0);
    printf("Child 2 collected\n");

    waitpid(c3, NULL, 0);
    printf("Child 3 collected\n");

    waitpid(c1, NULL, 0);
    printf("Child 1 collected\n");

    printf("All children completed\n");

    return 0;
}
