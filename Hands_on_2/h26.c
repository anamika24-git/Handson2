/*
============================================================================
Name : h26.c
Author : Anamika Mishra
Description : Write a program to send messages to the message queue. 
	Check $ipcs -q
    Date - 11th October, 2023
============================================================================
*/
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct message {
	long mtype;
	char mtext[100];
};

int main() {
	key_t key = ftok("Msgqueue.txt", 'P');
	if(key == -1) {
		perror("failed to get key\n");
		exit(1);
	}

	int msqid = msgget(key, IPC_CREAT | 0777);
	struct msqid_ds mqinfo;
	if(msqid == -1) {
		perror("Failed to create message queue\n");
		exit(1);
	}
	struct message msg;
	msg.mtype = 1;
	strcpy(msg.mtext, "Hello, Message QueueIPC!");

	msgsnd(msqid, &msg, sizeof(msg.mtext), 0);
    printf("Message sent  :)");

	return 0;
}

/* ipsc -q output
(base) anamikamishra@Anamikas-MacBook-Pro Hands_on_2 % ipcs -q
IPC status from <running system> as of Wed Oct 18 16:05:00 IST 2023
T     ID     KEY        MODE       OWNER    GROUP
Message Queues:
q  65536 0x501274c7 --rw-rw-rw- anamikamishra    staff*/

