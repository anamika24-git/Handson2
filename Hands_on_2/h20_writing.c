#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
int main()
{
    char message[50];
    int fd = open("mkfifo_file" , O_CREAT|O_WRONLY , 0744);
    printf("Enter the text: ");
    scanf("%[^\n]",message);
    write(fd , message , sizeof(message));
    return 0;
}
