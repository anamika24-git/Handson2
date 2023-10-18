/*
============================================================================
Name : h27a.c
Author : Anamika Mishra
Description : Write a program to receive messages from the message queue.
 a. with 0 as a flag
 Date - 11th October 2023
============================================================================
*/

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>

struct message {
	long mtype;
	char mtext[100];
};

int main() {
	key_t key = ftok("Msgqueue.txt", 'P');
	int msqid = msgget(key, 0666 | IPC_CREAT);
 printf("USE 0\n");
	struct message rcv_msg;
	msgrcv(msqid, &rcv_msg, sizeof(rcv_msg.mtext), 1, 0);

	printf("Received message: %s\n", rcv_msg.mtext);

	return 0;
}
