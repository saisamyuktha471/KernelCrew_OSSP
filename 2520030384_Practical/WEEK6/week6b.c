#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handle(int sig)
{
    printf("Signal received: %d\n", sig);
}

int main()
{
    signal(SIGINT, handle);
    signal(SIGTERM, handle);
    signal(SIGUSR1, handle);

    printf("PID = %d\n", getpid());

    while(1)
        pause();

    return 0;
}
