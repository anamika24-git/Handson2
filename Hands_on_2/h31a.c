/*
============================================================================
Name : h31a.c
Author : Anamika Mishra 
Description : Write a program to create a semaphore and initialize 
	value to the semaphore.
	a. create a binary semaphore
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
	key_t key = ftok("binarySem.txt", 'b');
	if(key == -1) {
		perror("Failed to create the key\n");
		exit(1);
	}

	int bsid = semget(key, 1, IPC_CREAT | 0777);
	if(bsid == -1) {
                perror("Failed to create the semaphore\n");
                exit(1);
        }

	union semun {
		int val;
	} sem;

	sem.val = 1;

	printf("Press enter to initialize semaphore\n");
	getchar();

	int status = semctl(bsid, 0, SETVAL, sem);
	if(status == -1) {
                perror("Faied to initialize semaphore\n");
                exit(1);
        }
        if(status == 0) printf("Binary semaphore created successfully\n");
    	else perror("semctl");
    	struct sembuf sem_operation = {0, 0, SEM_UNDO};
    	int current_value = semctl(bsid, 0, GETVAL, sem_operation);
    	printf("Current semaphore value: %d\n", current_value);

	return 0;
}