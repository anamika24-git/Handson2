/*
============================================================================
Name : h14.c
 
 Author : Anamika Mishra
Description : Write a simple program to create a pipe, write to the pipe, read from pipe and display on
 the monitor.
Date: 3rd October , 2023.
============================================================================
*/



#include<stdio.h>
#include<unistd.h> //pipe header
#include<string.h>
int main(){
    int pipefd[2];
    if(pipe(pipefd) == -1){
        perror("pipe call failed\n");
    }
    char c[50] = "Hello! how are you ?";
    char buf[50];
    printf("write to one end of a pipe\n");
    write(pipefd[1] , c , strlen(c));
    printf("writing finish......\n");
    printf("Read from other end of pipe\n");
    read(pipefd[0] , buf , sizeof(buf));
    printf("read finish.......\n");
    printf("Dispaly read write meassage:\n");
    write(1,buf,sizeof(buf));
    
    return 0;
}
