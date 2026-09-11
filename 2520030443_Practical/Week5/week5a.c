#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>

int main()
{
    int pipefd[2];
    pid_t pid;
    char buffer[100];
    char data[] = "Hello from Producer";

    struct timespec start, end;
    long elapsed;

    pipe(pipefd);

    clock_gettime(CLOCK_MONOTONIC, &start);

    pid = fork();

    if (pid == 0)
    {
        // Child - Consumer
        close(pipefd[1]);

        read(pipefd[0], buffer, sizeof(buffer));

        printf("Consumer received: %s\n", buffer);

        close(pipefd[0]);
    }
    else
    {
        // Parent - Producer
        close(pipefd[0]);

        write(pipefd[1], data, strlen(data) + 1);

        close(pipefd[1]);

        wait(NULL);

        clock_gettime(CLOCK_MONOTONIC, &end);

        elapsed = (end.tv_sec - start.tv_sec) * 1000000L;
        elapsed += (end.tv_nsec - start.tv_nsec) / 1000;

        printf("Communication time: %ld microseconds\n", elapsed);
    }

    return 0;
}
