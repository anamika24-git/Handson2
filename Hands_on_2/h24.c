#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
int main()
{
	key_t key = ftok("Msgqueue.txt", 'P');
    if(key == -1) {
		perror("Failed to create unique key\n");
		exit(1);
	}
	int msqid = msgget(key, 0666 | IPC_CREAT);
    printf("key: %d\n",key);
    printf("Message queue id: %d\n",msqid);
    return 0;
}