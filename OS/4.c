#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <signal.h>

pid_t p1;
pid_t p2;
void quit(int sig) {
	kill(p1,SIGUSR1);
	kill(p2,SIGUSR2);
	printf("Parent Process is killed\n");
}

void kill1(int sig) {
	printf("Child Process 1 is killed by Parent\n");
	exit(0);
}

void kill2(int sig) {
	printf("Child Process 2 is killed by Parent\n");
	exit(0);
}

int main() {
	int fd[2];
	pipe(fd);
	p1 = fork();
	if (p1 == 0) {
		signal(SIGUSR1, kill1);
		signal(SIGINT,SIG_IGN);
		close(fd[0]);
		char in[30];
		for (int i=0; i<100000; i++) {
			sprintf(in, "I send message %d times\n", i);
			write(fd[1], in, 30);
			sleep(1);
		}
	}
	p2 = fork();
	if (p2 == 0) {
		signal(SIGUSR2, kill2);
		signal(SIGINT, SIG_IGN);
		char out[30];
		close(fd[1]);
		while (1) {
			read(fd[0], out, 30);
			printf("%s\n", out);
		}
	}
	signal(SIGINT, quit);
	int status;
	wait(&status);
	return 0;
}
