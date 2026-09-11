#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

#define NUM_ITEMS 10000

int main()
{
    int fd[2];
    pid_t pid;

    if (pipe(fd) == -1)
    {
        perror("pipe");
        exit(1);
    }

    pid = fork();

    if (pid < 0)
    {
        perror("fork");
        exit(1);
    }

    if (pid > 0)
    {
        // Parent - Producer
        close(fd[0]);

        struct timespec start, end;

        clock_gettime(CLOCK_MONOTONIC, &start);

        for (int i = 1; i <= NUM_ITEMS; i++)
        {
            write(fd[1], &i, sizeof(i));
        }

        close(fd[1]);

        wait(NULL);

        clock_gettime(CLOCK_MONOTONIC, &end);

        double time_taken =
            (end.tv_sec - start.tv_sec) +
            (end.tv_nsec - start.tv_nsec) / 1e9;

        printf("Producer generated %d items.\n", NUM_ITEMS);
        printf("Communication time: %.6f seconds\n", time_taken);
        printf("Communication efficiency: %.2f items/second\n",
               NUM_ITEMS / time_taken);
    }
    else
    {
        // Child - Consumer
        close(fd[1]);

        int data;
        int count = 0;

        while (read(fd[0], &data, sizeof(data)) > 0)
        {
            count++;
        }

        close(fd[0]);

        printf("Consumer received %d items.\n", count);
    }

    return 0;
}

