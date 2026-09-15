#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

#define NUM_ITEMS 10000

int main()
{
    int fd[2];
    int i, data, count = 0;
    pid_t pid;
    clock_t start, end;

    pipe(fd);
    pid = fork();

    if (pid > 0)
    {
        close(fd[0]);

        start = clock();

        for (i = 1; i <= NUM_ITEMS; i++)
            write(fd[1], &i, sizeof(i));

        close(fd[1]);
        wait(NULL);

        end = clock();

        double time_taken = (double)(end - start) / CLOCKS_PER_SEC;

        printf("Producer generated %d items.\n", NUM_ITEMS);
        printf("Communication time: %.6f seconds\n", time_taken);
        printf("Communication efficiency: %.2f items/second\n",
               NUM_ITEMS / time_taken);
    }
    else
    {
        close(fd[1]);

        while (read(fd[0], &data, sizeof(data)) > 0)
            count++;

        close(fd[0]);

        printf("Consumer received %d items.\n", count);
    }

    return 0;
}
