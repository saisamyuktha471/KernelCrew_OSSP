#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    int fd[2];
    pid_t pid1, pid2;

    pipe(fd);

    pid1 = fork();

    if (pid1 == 0)
    {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);

        execlp("ls", "ls", "-l", NULL);
        exit(1);
    }

    pid2 = fork();

    if (pid2 == 0)
    {
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);

        execlp("grep", "grep", ".c", NULL);
        exit(1);
    }

    close(fd[0]);
    close(fd[1]);

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return 0;
}
