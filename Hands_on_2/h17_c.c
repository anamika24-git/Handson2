#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<fcntl.h>
int main(){
    
    int pipefd[2];
    if(pipe(pipefd) == -1)
        perror("error while creating pipe");
    pid_t pid = fork();
    if(pid == -1)
        perror("fork call failed");
    else if(pid == 0)
    {
        //child process
        close(pipefd[0]); //read end close
        if(pipefd[1] != STDOUT_FILENO){
            close(STDOUT_FILENO);
            fcntl(pipefd[1],F_DUPFD,STDOUT_FILENO); // write end duplicate to stdout
            close(pipefd[1]);  //close extra descriptor // closing original one
        }
        execlp("ls", "ls", "-l", NULL);
    }
    else
    {
        close(pipefd[1]); //write end close
        if(pipefd[0] != STDIN_FILENO) {
            close(STDIN_FILENO);
            fcntl(pipefd[0],F_DUPFD,STDIN_FILENO); //read duplicate to stdin
            close(pipefd[0]); //close read fd of pipe
        }
        execlp("wc", "wc", NULL);
    }
    return 0;
    
    
}


