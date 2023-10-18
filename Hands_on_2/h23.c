/*
============================================================================
Name : h23
 
 Author : Anamika Mishra
Description :Write a program to print the maximum number of files 
	can be opened within a process and size of a pipe (circular buffer).
Date: 10th October , 2023.
============================================================================
*/

#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int main() {
	long maxOpen, size;
	size = pathconf("myfifo_file", _PC_PIPE_BUF);
	maxOpen = sysconf(_SC_OPEN_MAX);

	printf("Max size of pipe is: %ld and max number of files which can be opened in a process is: %ld\n", size, maxOpen);

	return 0;
}