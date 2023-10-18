#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
int main()
{
    char buff[50];
    int fd = open("mkfifo_file" , O_RDONLY , 0744);
    read(fd , buff , sizeof(buff));
    printf("the text from fifo write process : %s" , buff);
    return 0;
}
