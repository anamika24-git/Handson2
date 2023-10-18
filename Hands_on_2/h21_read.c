#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main()
{
    char writeBuffer[50] , readBuffer[50];
    int fd1 = open("myfifo21_1.txt", O_RDONLY);
    int fd2 = open("myfifo21_2.txt" , O_WRONLY|O_CREAT,0644);
    read(fd1 , readBuffer ,sizeof(readBuffer));
    printf("Data received: %s\t", readBuffer);
    printf("ENTER THE TEXT:\n");
    scanf("%[^\n]",writeBuffer);
    write(fd2,writeBuffer,strlen(writeBuffer));
    return 0;
}
