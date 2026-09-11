#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

int main()
{
    int fd;
    char buffer[100];

    // Create named pipe
    mkfifo("myfifo", 0666);

    // Open FIFO for reading
    fd = open("myfifo", O_RDONLY);

    // Read message from client
    read(fd, buffer, sizeof(buffer));

    printf("Client message: %s\n", buffer);

    close(fd);

    // Process the message and send response
    fd = open("myfifo", O_WRONLY);

    char response[] = "Message received and processed by server";

    write(fd, response, strlen(response) + 1);

    close(fd);

    unlink("myfifo");

    return 0;
}
