/*
============================================================================
Name : h28.c
Author : Anamika Mishra
Description : Write a program to change the exiting message 
	queue permission. (use msqid_ds structure)

    Date - 11th October ,2023
============================================================================
*/
#include<sys/ipc.h>
#include<sys/types.h>
#include<sys/msg.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main() {
	key_t key = ftok("Msgqueue.txt", 'P');
	if(key == -1) {
		perror("Failed to create key\n");
		exit(1);
	}

	int msgqid = msgget(key, IPC_CREAT|0777);
	if(msgqid == -1) {
		perror("Failed to create the message queue\n");
		exit(1);
	}
	
	struct msqid_ds mqInfo;
	int status = msgctl(msgqid, IPC_STAT, &mqInfo);
	if(status  == -1) {
		perror("Failed to get info\n");
		exit(1);
	} else {
		mqInfo.msg_perm.mode = 0776;
	}

	status = msgctl(msgqid, IPC_SET, &mqInfo);
	if(status  == -1) {
                perror("Failed to set info\n");
              
                  exit(1);
        }
    printf("changed permission : %o",mqInfo.msg_perm.mode);

	return 0;
}