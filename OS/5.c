#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int ins[320];
void generate() {
	srand((unsigned)time(NULL));
	int i = 0;
	while (1) {
		ins[i] = rand()%(32000-2-1)+1;
		i++;
		ins[i] = ins[i-1]+1;
		i++;
		if(i==320)
			break;
		ins[i] = rand()%(ins[i-1]-0)+0;
		i++;
		ins[i] = ins[i-1]+1;
		i++;
		ins[i] = rand()%(32000-ins[i-1]-2)+ins[i-1]+2;
		i++;
		ins[i] = ins[i-1]+1;
		i++;
	}
}

void swap(int* a, int *b) {
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

#define find 1
#define notfind 0
void fifo(int MAX_NUM) {
	int list[32];
	for (int i=0; i<32; i++)
		list[i] = -1;
	int flag = notfind;
	int page = 0;
	int count= 0;
	int range = 0;
	for (int n=0; n<320; n++) {
		page = ins[n] / 1000;
		for (int i=0; i<MAX_NUM; i++) {
			if (page==list[i])
				flag = find;
		}
		if (flag==find) {
			count++;
			flag = notfind;
			continue;
		} else {
			if (range < MAX_NUM) {
				list[range] = page;
				range++;
			} else {
				for (int i=0; i<MAX_NUM-2; i++)
					list[i] = list[i+1];
				list[MAX_NUM-1] = page;
			}
		}
	}
	printf("fifo命中率 %f\n", (float)count/320.0);
}

void lru(int MAX_NUM) {
	typedef struct Page {
		int t;
		int page;
	} Page;
	Page list[32];
	Page tmp = {-1, -1};

	for (int i=0; i<32; i++)
		list[i] = tmp;
	int findpos = -1;
	int flag = notfind;

	int range = 0;

	int count = 0;

	for (int n=0; n<320; n++) {
		int page = ins[n] / 1000;
		for (int i=0; i<MAX_NUM; i++) {
			if (page==list[i].page) {
				flag = find;
				findpos = i;
			}
		}

		for (int i=0; i<range; i++)
			list[i].t++;

		if (flag==find) {
			list[findpos].t = 0;
			count++;
			findpos = -1;
			flag = notfind;
		} else {
			int replace = -1;
			int lu = 0;
			for (int i=0; i<range; i++) {
				if (lu < list[i].t) {
					lu = list[i].t;
					replace = i;
				}
			}
			tmp.page = page;
			tmp.t = 0;
			if (range<MAX_NUM) {
				list[range] = tmp;
				range++;
			} else {
				list[replace] = tmp;
			}
		}
	}
	printf("lru命中率 %f\n", (float)count/320.0);
}

int main() {
	generate();
	printf("请输入分配用户内存数\n");
	int MAX_NUM;
	scanf("%d", &MAX_NUM);
	fifo(MAX_NUM);
	lru(MAX_NUM);
	return 0;
}
