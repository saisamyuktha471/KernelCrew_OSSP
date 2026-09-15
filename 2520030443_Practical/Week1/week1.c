#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;
    char command[100];

    
    printf("Enter a Linux command: ");
    scanf("%s", command);

    
    pid = fork();

    if (pid < 0)
    {
        printf("Fork failed\n");
        return 1;
    }

    if (pid == 0)
    {
        
        printf("\nChild Process\n");
        printf("Child PID: %d\n", getpid());
        printf("Parent PID: %d\n", getppid());

       
        execlp(command, command, (char *)NULL);

        
        printf("Command execution failed\n");
        exit(1);
    }
    else
    {
       
        printf("\nParent Process\n");
        printf("Parent PID: %d\n", getpid());
        printf("Waiting for child process...\n");

       
        wait(NULL);

        printf("Child process completed.\n");
    }

    return 0;
}
