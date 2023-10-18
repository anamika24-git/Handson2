#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(){
    
    int pipefd[2];
    int pfd[2];
    if(pipe(pipefd) == -1)
        perror("error while creating pipe");
    if(pipe(pfd) == -1)
        perror("error while creating pipe");
    pid_t pid = fork();
    if(pid == -1)
        perror("fork call failed");
    else if(pid == 0)
    {
        //child process
        close(pipefd[0]); //read end close
        close(pfd[0]);
        close(pfd[1]);
        if(pipefd[1] != STDOUT_FILENO){
            dup2(pipefd[1],STDOUT_FILENO); // write end duplicate to stdout
            close(pipefd[1]);  //close extra descriptor // closing original one
        }
        execlp("ls", "ls", "-l", NULL);
    }
    else
    {
        //parent
         // another child
        close(pipefd[1]); //write end close
        close(pfd[0]);
        close(pfd[1]);
        if(pipefd[0] != STDIN_FILENO) {
            dup2(pipefd[0],STDIN_FILENO); //read duplicate to stdin
            close(pipefd[0]); //close read fd of pipe
        }
        execlp("grep", "grep", "^d", NULL);
    }
    wait(NULL); // wait for first child to finish
    
    // another child
    pid_t pid1 = fork();
    if(pid1 == -1)
        perror("fork call failed");
    else if(pid1 == 0)
    {
        //child process
        close(pfd[0]); //read end close
        close(pipefd[0]);
        close(pipefd[1]);
        if(pfd[1] != STDOUT_FILENO){
            dup2(pfd[1],STDOUT_FILENO); // write end duplicate to stdout
            close(pfd[1]);  //close extra descriptor // closing original one
        }
        execlp("grep", "grep", "^d", NULL);
    }
    else
    {
        //parent
        close(pfd[1]); //write end close
        close(pipefd[0]);
        close(pipefd[1]);
        if(pfd[0] != STDIN_FILENO) {
            dup2(pfd[0],STDIN_FILENO); //read duplicate to stdin
            close(pfd[0]); //close read fd of pipe
        }
        execlp("wc", "wc", NULL);
    }
    
    return 0;
    
    
}


