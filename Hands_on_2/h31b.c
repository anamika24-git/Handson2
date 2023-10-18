/*
============================================================================
Name : h31b.c
Author : Anamika Mishra
Description : Write a program to create a semaphore and initialize 
	value to the semaphore.
	b. create a counting semaphore
    Date - 13th October, 2023
============================================================================
*/
#include<sys/ipc.h>
#include<sys/types.h>
#include<sys/sem.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main() {
	key_t key = ftok("countSem.txt", 'c');
	if(key == -1) {
		perror("Failed to create the key\n");
		exit(1);
	}

	int cosid = semget(key, 1, IPC_CREAT | 0777);
	if(cosid == -1) {
                perror("Failed to create the semaphore\n");
                exit(1);
        }

	union semun {
		int val;
	} sem;

	sem.val = 5;

	printf("Press enter to initialize semaphore\n");
	getchar();

	int status = semctl(cosid, 0, SETVAL, sem);
	if(status == -1) {
                perror("Faied to initialize semaphore\n");
                exit(1);
        }
        if(status == 0) printf("Counting semaphore created successfully\n");
    	else perror("semctl");

	return 0;
}

