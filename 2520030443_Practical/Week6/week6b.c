#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int fd;
    char buffer[100];

    // Open FIFO for writing
    fd = open("myfifo", O_WRONLY);

    char message[] = "Hello Server";

    // Send message to server
    write(fd, message, strlen(message) + 1);

    close(fd);

    // Open FIFO for reading response
    fd = open("myfifo", O_RDONLY);

    read(fd, buffer, sizeof(buffer));

    printf("Server response: %s\n", buffer);

    close(fd);

    return 0;
}
