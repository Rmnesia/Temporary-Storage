#include <stdio.h>
#include <malloc.h>
#include <string.h>
typedef struct pcb {
    char name[3];
    int need;
    int waited;
    int turn;
    struct pcb *next;
} PCB;

PCB *Finish;
int clock=0;
const int q=7;

void Simple(PCB *queue){
    PCB *tmp=queue;
}

int main() {
    Finish = (PCB*)malloc(sizeof(PCB));
    PCB *RQ1=(PCB*)malloc(sizeof(PCB));
    PCB *RQ2=(PCB*)malloc(sizeof(PCB));
    FILE *fp=freopen("/home/nicolus/CLionProjects/untitled2/RQ","r",stdin);
    if (fp==NULL) return 0;

    PCB *tmp=RQ1;
    for(int i=0; i<5; i++) {
        scanf("%s",tmp->name);
        if (i==4) break;
        tmp->next=(PCB*)malloc(sizeof(PCB));
        tmp=tmp->next;
    }

    tmp = RQ2;
    for(int i=0; i<5; i++) {
        scanf("%s",tmp->name);
        if (i==4) break;
        tmp->next=(PCB*)malloc(sizeof(PCB));
        tmp=tmp->next;
    }

    tmp=RQ1;
    for(int i=0;i<5; i++) {
        scanf("%d ",&tmp->need);
        tmp=tmp->next;
    }

    tmp=RQ2;
    for(int i=0;i<5; i++) {
        scanf("%d ",&tmp->need);
        tmp = tmp->next;
    }

    tmp=RQ1;
    for(int i=0;i<5; i++) {
        scanf("%d ",&tmp->waited);
        tmp = tmp->next;
    }

    tmp=RQ2;
    for(int i=0;i<5; i++) {
        scanf("%d ",&tmp->waited);
        tmp = tmp->next;
    }

    tmp = RQ1;
    PCB *tail = tmp;

    PCB *curr = Finish;
    while (tail->next!=NULL)
        tail=tail->next;
    while (tmp!=NULL) {
        if(tmp->need>q) {
            clock += q;
            tmp->need-=q;
            tail->next=tmp;
            tmp=tmp->next;
            RQ1=tmp;
            tail=tail->next;
            tail->next=NULL;
        }
        else {
            clock += tmp->need;
            tmp->turn=tmp->waited+clock;
            curr->next=(PCB*)malloc(sizeof(PCB));
            curr->turn=tmp->turn;
            strcpy(curr->name,tmp->name);
            curr=curr->next;
            free(tmp);
            tmp=tmp->next;
        }
    }

    tmp=RQ2;
    while(tmp!=NULL){
        clock += tmp->need;
        tmp->turn=tmp->waited+clock;
        curr->next=(PCB*)malloc(sizeof(PCB));
        curr->turn=tmp->turn;
        strcpy(curr->name,tmp->name);
        curr=curr->next;
        free(tmp);
        tmp=tmp->next;
    }

    tmp=Finish;
    for(int i=0;i<10; i++){
        printf("%s:%d ",tmp->name,tmp->turn);
        tmp=tmp->next;
    }
    printf("\n");

    return 0;
}