#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    char msg[100];

    printf("Enter message: ");
    scanf("%s", msg);

    int fd = open("myfifo", O_WRONLY);

    write(fd, msg, sizeof(msg));

    close(fd);

    return 0;
}
