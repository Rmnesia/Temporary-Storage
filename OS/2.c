#include <stdio.h>

#define MAX_POS 999

int min(int list[14]) {
    int m=9999;
    int pos=0;
    for (int i=0; i<14; i++) {
        if (m > list[i]) {
            m = list[i];
            pos = i;
        }
    }
    return pos;
}
int distance(int a, int b){
    return a-b>0 ? a-b : b-a;
}

//先来先服务
void f1(char name[14], int num[14]){
    printf("磁盘的访问顺序为:\n");
    int sum = distance(90, num[0]);
    for (int i=0; i<14; i++)
        printf("%c ", name[i]);
    for (int i=0; i<13; i++)
        sum += distance(num[i], num[i+1]);
    printf("\n");
    printf("平均移动道数为: %f", (float)sum/14.0);
}
//最短寻道优先
void f2(char name[14], int num[14]){
    int list[14];
    for (int i=0; i<14; i++)
        list[i] = MAX_POS;
    printf("磁盘的访问顺序为:\n");
    for (int j = 0; j < 14; j++)
        list[j] = distance(90, num[j]);
    int pos = min(list);
    int cur = 0;
    int sum = distance(90, num[pos]);
    for (int i=0; i<14; i++)
        list[i] = MAX_POS;
    for (int i=0; i<14; i++) {
        for (int j = 0; j < 14; j++) {
            if (i == 13 || j != pos)
                list[j] = distance(num[j], num[pos]);
        }
        cur = pos;
        pos = min(list);
        sum += distance(num[cur], num[pos]);
        num[cur] = MAX_POS;
        printf("%c ", name[cur]);
        for (int j = 0; j < 14; j++)
            list[j] = MAX_POS;
    }
    printf("\n");
    printf("平均移动道数为：%f", (float)sum/14.0);
}
//电梯调度算法
#define right 0
#define left 1
#define false 0
#define true 1
void f3(char name[14], int num[14]){
    int flag = right;
    int change;
    int list[14];
    for (int i = 0; i < 14; i++)
        list[i] = MAX_POS;
    for (int i = 0; i < 14; i++) {
        if (num[i] > 90)
            list[i] = distance(90, num[i]);
    }
    int pos = min(list);
    int cur = 0;
    int sum = distance(90, num[pos]);
    for (int i = 0; i < 14; i++)
        list[i] = MAX_POS;
    for (int i = 0; i < 14; i++) {
        change = true;
        for (int j = 0; j < 14; j++) {
            if (num[j] == MAX_POS)
                continue;
            if (flag == right) {
                if (num[j] > num[pos] && (i != 13 || j != pos)) {
                    list[j] = distance(num[j], num[pos]);
                    change = false;
                }
            } else {
                if (num[j] < num[pos] && (i != 13 || j != pos)) {
                    list[j] = distance(num[j], num[pos]);
                    change = false;
                }
            }
        }
        if (change && i != 13) {
            flag = flag ? right : left;
            i--;
            continue;
        }
        cur = pos;
        pos = min(list);
        sum += distance(num[cur], num[pos]);
        num[cur] = MAX_POS;
        printf("%c ", name[cur]);
        for (int j = 0; j < 14; j++)
            list[j] = MAX_POS;
    }
    printf("\n");
    printf("平均移动道数为：%f", (float)sum/14.0);
}
int main() {
    printf("请选择调度算法\n");
    printf("1.先来先服务\n");
    printf("2.最短寻道优先\n");
    printf("3.电梯调度算法\n");
    char choice;
    char name[14];
    int num[14];

    FILE *fp = fopen("read.txt","r");

    for (int i=0; i<14; i++) {
        fscanf(fp, "%c", &name[i]);
        fgetc(fp);
    }

    for (int i=0; i<14; i++)
        fscanf(fp, "%d", &num[i]);

    scanf("%c", &choice);
    switch (choice) {
        case '1': f1(name, num); break;
        case '2': f2(name, num); break;
        case '3': f3(name, num); break;
        default:
            printf("输入错误");
    }
    return 0;
}