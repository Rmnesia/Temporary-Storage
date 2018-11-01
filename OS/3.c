#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

void __create(){
	char input[10];
	printf("请输入文件名\n");
	scanf("%s", input);
	int c = open(input, O_CREAT, S_IRUSR|S_IWUSR);
	close(c);
}
void __write(){
	char input[100];
	printf("请输入文件名\n");
	scanf("%s", input);
	int w = open(input, O_WRONLY);
	printf("请输入文件内容\n");
	scanf("%s", input);
	write(w, input, 100);
	close(w);
}
void __read(){
	char input[100];
	printf("请输入文件名\n");
	scanf("%s", input);
	int r = open(input, O_RDONLY);
	read(r, input, 100);
	printf("%s", input);
	close(r);
}
void __change(){
	char name[10];
	char input[10];
	printf("请输入文件名:\n");
	scanf("%s", name);
	printf("请输入新的权限:\n");
	scanf("%s", input);
	int right = atoi(input);
	int cur_right = right / 100;
	mode_t mode;
	if (cur_right==7) mode |= S_IRUSR | S_IWUSR | S_IXUSR;
	else if (cur_right==6) mode |= S_IRUSR | S_IWUSR;
	else if (cur_right==4) mode |= S_IRUSR;
	else if (cur_right==3) mode |= S_IWUSR | S_IXUSR;
	else if (cur_right==2) mode |= S_IWUSR;
	else if (cur_right==1) mode |= S_IXUSR;
	cur_right = (right/10)%10 ;
	if (cur_right==7) mode |= S_IRGRP | S_IWGRP | S_IXGRP;
	else if (cur_right==6) mode |= S_IRGRP | S_IWGRP;
	else if (cur_right==4) mode |= S_IRGRP;
	else if (cur_right==3) mode |= S_IWGRP | S_IXGRP;
	else if (cur_right==2) mode |= S_IWGRP;
	else if (cur_right==1) mode |= S_IXGRP;
	cur_right = right % 10;
	if (cur_right==7) mode |= S_IROTH | S_IWOTH | S_IXOTH;
	else if (cur_right==6) mode |= S_IROTH | S_IWOTH;
	else if (cur_right==4) mode |= S_IROTH;
	else if (cur_right==3) mode |= S_IWOTH | S_IXOTH;
	else if (cur_right==2) mode |= S_IWOTH;
	else if (cur_right==1) mode |= S_IXOTH;
	chmod(name, mode);
}
void __check(){
	char input[10];
	printf("请输入文件名:\n");
	scanf("%s", input);
	char *pargv[] = {"ls", "-l", input, NULL};
	execv("/bin/ls",pargv);
}

int main() {
	while (1) {
		printf("请输入功能号：\n");
		printf("1.创建新文件\n");
		printf("2.写文件\n");
		printf("3.读文件\n");
		printf("4.修改文件权限\n");
		printf("5.查看当前文件权限\n");
		printf("0.退出\n");
		int choice;
		scanf("%d", &choice);
		switch (choice) {
			case 1: __create();
				break;
			case 2: __write();
				break;
			case 3: __read();
				break;
			case 4: __change();
				break;
			case 5: __check();
				break;
			default:
				return 0;
		}
	}
}
