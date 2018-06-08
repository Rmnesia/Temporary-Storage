#include <stdio.h>
#include <malloc.h>

typedef struct RD {
    int flag;
    int size;
    struct RD *next;
} rd;

int maxsize=512;

int First(){
    int choice;
    rd *head = (rd*)malloc(sizeof(rd));
    head->flag=0;
    head->size=maxsize;
    rd *curr, *tmp;
    int addr=0;
    while(1){
        printf("1.Request 2.Release 3.Finished\n");
        scanf("%d",&choice);
        switch (choice) {
            case 1:
                printf("Input your size\n");
                scanf("%d",&choice);
                for (curr=head; curr; curr=curr->next) {
                    if (((curr->flag)==0)&&(curr->size>=choice)) {
                        if (curr->size==choice) {
                            curr->flag=1;
                            printf("Success! Addr: %d\n", addr);
                            break;
                        }
                        curr->size-=(choice+1);
                        if (curr->next!=NULL) {
                            tmp=curr->next;
                            curr->next = (rd *) malloc(sizeof(rd));
                            curr->next->flag = 1;
                            curr->next->size = choice+1;
                            curr->next->next = tmp;
                        } else {
                            curr->next = (rd *) malloc(sizeof(rd));
                            curr->next->flag = 1;
                            curr->next->size = choice + 1;
                        }
                        addr+=(curr->size+1);
                        printf("Success ! Addr: %d\n", addr);
                        break;
                    }
                    addr+=(curr->size+1);
                }
                if(!curr)printf("Failed!\n");
                addr=0;
                break;
            case 2:
                printf("Input your Addr:");
                scanf("%d", &choice);
                addr=1;
                for(curr=head,tmp=head; curr; curr=curr->next){
                    if (choice==addr) {
                        if (curr->next!=NULL && curr->next->flag==0){
                            curr->size+=curr->next->size;
                            curr->next=curr->next->next;
                        }
                        if (tmp->flag==0) {
                            tmp->size+=curr->size;
                            tmp->next=curr->next;
                        }
                        curr->flag=0;
                        printf("Success Free!\n");
                        break;
                    }
                    addr+=curr->size;
                    tmp=curr;
                }
                if (curr==NULL) printf("Failed Free!\n");
                addr=0;
                break;
            case 3:
                return 0;
            default:
                return 1;
        }
    }
}

int Best(){
    int choice;
    rd *head = (rd*)malloc(sizeof(rd));
    head->flag=0;
    head->size=maxsize;
    rd *curr, *tmp;
    int addr=0;
    typedef struct Minsize {
        int size;
        struct Minsize *next;
    } minsize;
    minsize *first=(minsize*)malloc(sizeof(minsize));
    minsize *p, *prev;
    while(1){
        printf("1.Request 2.Release 3.Finished\n");
        scanf("%d",&choice);
        switch (choice) {
            case 1:
                printf("Input your size\n");
                scanf("%d",&choice);
                for (p=first,prev=p; p->size<choice; p=p->next)prev=p;

                for (curr=head; curr; curr=curr->next) {
                    if (((curr->flag)==0)&&(curr->size>=choice)&&(curr->size==p->size)) {
                        if (curr->size==choice) {
                            curr->flag=1;
                            printf("Success! Addr: %d\n", addr);
                            prev->next=p->next;
                            break;
                        }
                        curr->size-=(choice+1);
                        if (curr->next!=NULL) {
                            tmp=curr->next;
                            curr->next = (rd *) malloc(sizeof(rd));
                            curr->next->flag = 1;
                            curr->next->size = choice+1;
                            curr->next->next = tmp;
                        } else {
                            curr->next = (rd *) malloc(sizeof(rd));
                            curr->next->flag = 1;
                            curr->next->size = choice + 1;
                        }
                        addr+=(curr->size+1);
                        p->size=curr->size;
                        printf("Success ! Addr: %d\n", addr);
                        break;
                    }
                    addr+=(curr->size+1);
                }
                if(!curr)printf("Failed!\n");
                addr=0;
                break;
            case 2:
                printf("Input your Addr:");
                scanf("%d", &choice);
                addr=1;
                for(curr=head,tmp=head; curr; curr=curr->next){
                    if (choice==addr) {
                        if (curr->next!=NULL && curr->next->flag==0){
                            curr->size+=curr->next->size;
                            curr->next=curr->next->next;
                        }
                        if (tmp->flag==0) {
                            tmp->size+=curr->size;
                            tmp->next=curr->next;
                        }
                        curr->flag=0;
                        for (p=first,prev=p; p; prev=p,p=p->next){
                            if (curr->size<p->size) {
                                prev->next=(minsize*)malloc(sizeof(minsize));
                                prev->size=curr->size;
                                prev->next->next=p;
                            }
                        }
                        printf("Success Free!\n");
                        break;
                    }
                    addr+=curr->size;
                    tmp=curr;
                }
                if (curr==NULL) printf("Failed Free!\n");
                addr=0;
                break;
            case 3:
                return 0;
            default:
                return 1;
        }
    }
}

int Worst(){
    int choice;
    rd *head = (rd*)malloc(sizeof(rd));
    head->flag=0;
    head->size=maxsize;
    rd *curr, *tmp;
    int addr=0;
    typedef struct Maxsize {
        int size;
        struct Maxsize *next;
    } maxsize;
    maxsize *first=(maxsize*)malloc(sizeof(maxsize));
    maxsize *p, *prev;
    while(1){
        printf("1.Request 2.Release 3.Finished\n");
        scanf("%d",&choice);
        switch (choice) {
            case 1:
                printf("Input your size\n");
                scanf("%d",&choice);
                for (p=first,prev=p; p->size<choice; p=p->next)prev=p;

                for (curr=head; curr; curr=curr->next) {
                    if (((curr->flag)==0)&&(curr->size>=choice)&&(curr->size==p->size)) {
                        if (curr->size==choice) {
                            curr->flag=1;
                            printf("Success! Addr: %d\n", addr);
                            prev->next=p->next;
                            break;
                        }
                        curr->size-=(choice+1);
                        if (curr->next!=NULL) {
                            tmp=curr->next;
                            curr->next = (rd *) malloc(sizeof(rd));
                            curr->next->flag = 1;
                            curr->next->size = choice+1;
                            curr->next->next = tmp;
                        } else {
                            curr->next = (rd *) malloc(sizeof(rd));
                            curr->next->flag = 1;
                            curr->next->size = choice + 1;
                        }
                        addr+=(curr->size+1);
                        p->size=curr->size;
                        printf("Success ! Addr: %d\n", addr);
                        break;
                    }
                    addr+=(curr->size+1);
                }
                if(!curr)printf("Failed!\n");
                addr=0;
                break;
            case 2:
                printf("Input your Addr:");
                scanf("%d", &choice);
                addr=1;
                for(curr=head,tmp=head; curr; curr=curr->next){
                    if (choice==addr) {
                        if (curr->next!=NULL && curr->next->flag==0){
                            curr->size+=curr->next->size;
                            curr->next=curr->next->next;
                        }
                        if (tmp->flag==0) {
                            tmp->size+=curr->size;
                            tmp->next=curr->next;
                        }
                        curr->flag=0;
                        for (p=first,prev=p; p; prev=p,p=p->next){
                            if (curr->size>p->size) {
                                prev->next=(maxsize*)malloc(sizeof(maxsize));
                                prev->size=curr->size;
                                prev->next->next=p;
                            }
                        }
                        printf("Success Free!\n");
                        break;
                    }
                    addr+=curr->size;
                    tmp=curr;
                }
                if (curr==NULL) printf("Failed Free!\n");
                addr=0;
                break;
            case 3:
                return 0;
            default:
                return 1;
        }
    }
}

int main() {
    printf("Input 1.First 2.Best Worst\n");
    int choice;
    scanf("%d",&choice);
    switch (choice) {
        case 1: while (First()) {}
            break;
        case 2: while (Best()) {}
            break;
        case 3: while (Worst()) {}
            break;
        default:
            return 0;
    }
    return 0;
}