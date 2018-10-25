#include <stdio.h>

#define MAX_TIME 999

int min(float list[10]) {
    float m=9999;
    int pos=0;
    for (int i=0; i<10; i++) {
        if (m > list[i]) {
            m = list[i];
            pos = i;
        }
    }
    return pos;
}

//先来先服务
void f1(char work_name[10],
        float arrive_time[10],
        float work_time[10]) {
    float t_time = 0; //总周转时间
    float tr_time = 0; //总带权周转时间
    float time_now = 0;

    printf("作业调度顺序为：\n");
    for (int i=0; i<10; i++) {
        int pos = min(arrive_time);
        if (time_now < arrive_time[pos])
            time_now = arrive_time[pos];
        printf("%c ", work_name[pos]);

        time_now += work_time[pos];

        t_time += time_now - arrive_time[pos];
        tr_time += (time_now - arrive_time[pos])/work_time[pos];

        arrive_time[pos] = MAX_TIME;
    }
    printf("\n");
    printf("平均周转时间为: %f\n", t_time/10);
    printf("平均带权周转时间为: %f\n", tr_time/10);
}
//短作业优先
void f2(char work_name[10],
        float arrive_time[10],
        float work_time[10]) {
    float wait_list[10];
    for (int i=0; i<10; i++)
        wait_list[i] = MAX_TIME;
    float t_time = 0; //总周转时间
    float tr_time = 0; //总带权周转时间
    float time_now = 0;

    int pos = 0;

    //保证可能出现的作业完成没有作业等待的情况
    int waiting = 0;

    printf("作业调度顺序为：\n");
    for (int i=0; i<10; i++) {
        for (int j=0; j<10; j++) {
            if (arrive_time[j]<=time_now) {
                wait_list[j] = work_time[j];
                waiting = 1;
            }
        }
        if (waiting == 0) {
            pos = min(arrive_time);
        } else {
            pos = min(wait_list);
            waiting = 0;
        }
        printf("%c ", work_name[pos]);
        time_now += work_time[pos];

        t_time += time_now - arrive_time[pos];
        tr_time += (time_now - arrive_time[pos])/work_time[pos];

        arrive_time[pos] = MAX_TIME;
        for (int j=0; j<10; j++)
            wait_list[j] = MAX_TIME;
    }
    printf("\n");
    printf("平均周转时间为: %f\n", t_time/10);
    printf("平均带权周转时间为: %f\n", tr_time/10);
}
//响应比高优先
void f3(char work_name[10],
        float arrive_time[10],
        float work_time[10]) {
    float p_list[10];
    for (int i=0; i<10; i++)
        p_list[i] = MAX_TIME;
    float t_time = 0; //总周转时间
    float tr_time = 0; //总带权周转时间
    float time_now = 0;

    int pos = 0;

    //保证可能出现的作业完成没有作业等待的情况
    int waiting = 0;

    printf("作业调度顺序为：\n");
    for (int i=0; i<10; i++) {
        for (int j=0; j<10; j++) {
            if (arrive_time[j]<=time_now) {
                p_list[j] = 1+(time_now-arrive_time[j])/work_time[j];
                //只写了min函数，响应比低用负数表示
                p_list[j] = -p_list[j];
                waiting = 1;
            }
        }
        if (waiting == 0) {
            pos = min(arrive_time);
        } else {
            pos = min(p_list);
            waiting = 0;
        }
        printf("%c ", work_name[pos]);
        time_now += work_time[pos];

        t_time += time_now - arrive_time[pos];
        tr_time += (time_now - arrive_time[pos])/work_time[pos];

        arrive_time[pos] = MAX_TIME;
        for (int j=0; j<10; j++)
            p_list[j] = MAX_TIME;
    }
    printf("\n");
    printf("平均周转时间为: %f\n", t_time/10);
    printf("平均带权周转时间为: %f\n", tr_time/10);
}

int main() {
    printf("请选择调度算法\n");
    printf("1.先来先服务\n");
    printf("2.短作业优先\n");
    printf("3.响应比高优先\n");
    char choice;
    char work_name[10];
    float arrive_time[10];
    float work_time[10];

    FILE *fp = fopen("work.txt","r");

    for (int i=0; i<10; i++) {
        fscanf(fp, "%c", &work_name[i]);
        fgetc(fp);
    }

    for (int i=0; i<10; i++)
        fscanf(fp, "%f", &arrive_time[i]);

    for (int i=0; i<10; i++)
        fscanf(fp, "%f", &work_time[i]);

    scanf("%c", &choice);
    switch (choice) {
        case '1': f1(work_name, arrive_time, work_time); break;
        case '2': f2(work_name, arrive_time, work_time); break;
        case '3': f3(work_name, arrive_time, work_time); break;
        default:
            printf("输入错误");
    }
    return 0;
}