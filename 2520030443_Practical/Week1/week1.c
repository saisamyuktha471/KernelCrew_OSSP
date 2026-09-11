#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;
    char command[100];

    // Accept command from user
    printf("Enter a Linux command: ");
    scanf("%s", command);

    // Create child process
    pid = fork();

    if (pid < 0)
    {
        perror("fork failed");
        return 1;
    }

    if (pid == 0)
    {
        // Child process
        printf("\nChild Process\n");
        printf("Child PID: %d\n", getpid());
        printf("Parent PID: %d\n", getppid());

        // Execute the command
        execlp(command, command, (char *)NULL);

        // This executes only if exec fails
        perror("exec failed");
        exit(1);
    }
    else
    {
        // Parent process
        printf("\nParent Process\n");
        printf("Parent PID: %d\n", getpid());
        printf("Waiting for child process...\n");

        // Wait for child to finish
        wait(NULL);

        printf("Child process completed.\n");
    }

    return 0;
}
