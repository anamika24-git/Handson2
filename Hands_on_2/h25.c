/*
============================================================================
Name : h25.c
Author : Anamika Mishra
Description : Write a program to print a message queue's 
	(use msqid_ds and ipc_perm structures)
	a. access permission
	b. uid, gid
	c. time of last message sent and received
	d. time of last change in the message queue
	d. size of the queue
	f. number of messages in the queue
	g. maximum number of bytes allowed
	h. pid of the msgsnd and msgrcv
============================================================================
*/
#include<sys/ipc.h>
#include<sys/types.h>
#include<sys/msg.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

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

	int status = msgctl(msqid, IPC_STAT, &mqinfo);
	if(status == -1) {
		perror("Failed to get status\n");
		exit(1);
	}

	printf("Access Permission: %od\n", mqinfo.msg_perm.mode);
	printf("UID: %d\n", mqinfo.msg_perm.uid);
	printf("GID: %d\n", mqinfo.msg_perm.gid);
	printf("Time of last message sent: %ld and received: %ld\n", mqinfo.msg_stime, mqinfo.msg_rtime);
	printf("Time of last change in message queue: %ld\n", mqinfo.msg_ctime);
	printf("Size of Queue %ld\n", mqinfo.msg_cbytes);
	printf("Number of message in Queue: %ld\n", mqinfo.msg_qnum);
	printf("Maximum number of bytes allowed: %ld\n", mqinfo.msg_qbytes);
	printf("pid of msgsnd: %d and msgrcv: %d\n", mqinfo.msg_lspid, mqinfo.msg_lrpid);

	return 0;
}