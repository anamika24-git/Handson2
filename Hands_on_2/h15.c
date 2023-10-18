/*
============================================================================
Name : h15.c
 
 Author : Anamika Mishra
Description : Write a simple program to send some data from parent to the child process.
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
    pid_t pid = fork();
    if(pid <0)
        perror("fork call failed");
    else if(pid == 0)
    {
        //child process
        close(pipefd[1]);
        printf("child is reading message\n");
        read(pipefd[0] , buf , sizeof(buf));
        printf("child read mesaage: %s \n",buf);
        close(pipefd[0]);
    }
    else
    {
        close(pipefd[0]);
        printf("parent process sending message\n");
        write(pipefd[1] , c , sizeof(c));
        printf("parent message send to child\n");
        close(pipefd[1]);
    }
    return 0;
}
