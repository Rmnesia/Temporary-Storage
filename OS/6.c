#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>

void use_pipe(){
	int fd[2];
	pid_t pid = fork();
	if (pid == 0) {
		char data[100];
		sprintf(data, "%d is sending a message to parent", getpid());
		write(fd[1], data, 100);
		exit(0);
	} else {
		char data[100];
		read(fd[0], data, 100);
		printf("%s", data);
		exit(0);
	}
}

void use_queue(){
	typedef struct MSG {
		long type;
		char msg[512];
	} MSG;
	const int SVKEY = 75;
	const int REQ = 1;

	pid_t pid = fork();

	if (pid == 0) {
		MSG msg;
		msg.type = REQ;
		sprintf(msg.msg, "%d", getpid());
		int qid = msgget(SVKEY, IPC_EXCL);
		msgsnd(qid, &msg, sizeof(MSG), 0);
		msgrcv(qid, &msg, sizeof(MSG), 0, 0);
		printf("receive reply from %s\n", msg.msg);
	} else {
		MSG msg;
		int qid = msgget(SVKEY, IPC_CREAT | IPC_EXCL);
		msgrcv(qid, &msg, sizeof(MSG), 0, 0);
		printf("serving for client %s\n", msg.msg);
		sprintf(msg.msg, "%d", getpid());
		msgsnd(qid, &msg, sizeof(MSG), 0);
	}
}

void use_share(){
	pid_t pid = fork();
	if (pid == 0) {
		int shmid=shmget(1, 512, 0666);
		char *data = (char *)shmat(shmid, 0, 0);
		sprintf(data, "this is data");
		shmdt(shmid);
	} else {
		int shmid = shmget(1, 512, IPC_CREAT | 0666);
		char *data = (char *)shmat(shmid, 0, 0);
		printf("%s", data);
		shmdt(shmid);
		shmctl(shmid,IPC_RMID,0);
		exit(0);
	}
}
int main() {
	int choice;
	printf("请选择通信方式\n 1. 管道通信 2.消息缓冲队列 3. 共享存储区\n");
	scanf("%d", &choice);
	switch (choice) {
		case 1: use_pipe(); break;
		case 2: use_queue(); break;
		case 3: use_share(); break;
		default:printf("输入错误");
	}
	return 0;
}
