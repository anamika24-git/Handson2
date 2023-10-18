/*
============================================================================
Name : h16.c
 
 Author : Anamika Mishra
Description : Write a program to send and receive data from parent to child vice versa. Use two way
 communication.
Date: 3rd October , 2023.
============================================================================
*/



#include<stdio.h>
#include<unistd.h> //pipe header
#include<sys/wait.h>
#include<string.h>
int main(){
    int pfd1[2];
    int pfd2[2];
    if(pipe(pfd1) == -1){
        perror("pipe1 call failed\n");
    }
    if(pipe(pfd2) == -1) {
        perror("pipe2 call failed\n");
    }
    char buff[50];
    char buff1[50];
   // printf("enter exit to break the communication\n");
    pid_t pid = fork();
    if(pid <0)
        perror("fork call failed\n");
    else if(pid == 0)
    {
        //child process
       
            close(pfd1[0]); //child read end close
            printf("Writing message to parent\n");
            scanf("%[^\n]" , buff);
            write(pfd1[1] , buff , sizeof(buff));
            close(pfd1[1]);
            close(pfd2[1]);
            read(pfd2[0] , buff1 , sizeof(buff1));
            printf("Message from Parent: %s \n",buff1);
            close(pfd2[0]);
            scanf("%s", buff);  // Assuming the user inputs a single word
           // if (strcmp(buff, "exit") == 0)
        
        
    }
    else
    {
        
            close(pfd1[1]); //parent write end close
            read(pfd1[0] , buff , sizeof(buff));
            printf("Message from Child: %s \n",buff);
            close(pfd1[0]);
            close(pfd2[0]);
            printf("Writing message to child\n");
            scanf("%[^\n]" , buff1);
            write(pfd2[1] , buff1 , sizeof(buff1));
            close(pfd2[1]);
            scanf("%s", buff1);  // Assuming the user inputs a single word
           /* if (strcmp(buff1, "exit") == 0)
                break;*/
    }
       
        
   wait(0);
}

