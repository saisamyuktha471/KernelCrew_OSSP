#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int source, destination;
    char buffer[1000];
    int n;

    // Open source file
    source = open("source.txt", O_RDONLY);

    if (source == -1)
    {
        printf("Error opening source file\n");
        return 1;
    }

    // Open destination file
    destination = open("destination.txt",
                       O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (destination == -1)
    {
        printf("Error opening destination file\n");
        close(source);
        return 1;
    }

    // Read and write contents
    while ((n = read(source, buffer, sizeof(buffer))) > 0)
    {
        write(destination, buffer, n);
    }

    // Close files
    close(source);
    close(destination);

    printf("File copied successfully\n");

    return 0;
}
