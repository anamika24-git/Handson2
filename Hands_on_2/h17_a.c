#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>
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
            dup(pipefd[1]); // write end duplicate to stdout
            close(pipefd[1]);  //close extra descriptor // closing original one
        }
        execlp("ls", "ls", "-l", NULL);
    }
    else
    {
        close(pipefd[1]); //write end close
        if(pipefd[0] != STDIN_FILENO) {
            close(STDIN_FILENO);
            dup(pipefd[0]); //read duplicate to stdin
            close(pipefd[0]); //close read fd of pipe
        }
        execlp("wc", "wc", NULL);
    }
    return 0;
    
    
}
