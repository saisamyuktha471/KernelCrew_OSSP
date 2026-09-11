#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main()
{
    char msg[100];

    mkfifo("myfifo", 0666);

    int fd = open("myfifo", O_RDONLY);

    read(fd, msg, sizeof(msg));

    printf("Server received: %s\n", msg);

    close(fd);

    return 0;
}
