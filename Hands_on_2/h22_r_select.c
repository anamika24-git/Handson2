/*
============================================================================
Name : h22
 
 Author : Anamika Mishra
Description :Write a program to wait for data to be written into FIFO within 10 seconds
, use select system call with FIFO.
Date: 10th October , 2023.
============================================================================
*/


#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    fd_set rfds;
    char buf[80];
    int fd, retval;
    struct timeval tv;

    fd = open("mkfifo_file" ,O_RDONLY);
    FD_ZERO(&rfds);
    FD_SET(fd, &rfds);
    tv.tv_sec = 5;
    tv.tv_usec = 0;
    retval = select(fd+1, &rfds,NULL,NULL,&tv);
    if(!retval)
        printf("No data is available for reading yet\n");
    else {
        printf("Data is available now\n");
        read(fd,buf,sizeof(buf));
        printf("Data from FIFO: %s\n" , buf);
    }

}