#include <stdio.h>

#define n 5
#define m 3

int* read_request(int num){
    int a[4];
    switch(num){
        case 1: a[0]=2;a[1]=0;a[2]=3;a[3]=4;return a;
        case 2: a[0]=4;a[1]=1;a[2]=0;a[3]=1;return a;
        case 3: a[0]=1;a[1]=2;a[2]=0;a[3]=1;return a;
        case 4: a[0]=3;a[1]=0;a[2]=0;a[3]=1;return a;
        default: return NULL;
    }
}

int main() {
    FILE *fp = freopen("/home/nicolus/CLionProjects/untitled3/Resource","r",stdin);
    int Available[]={2, 3, 3};
    int Alloc[n][m];
    int Need[n][m];
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++)
            scanf("%d", &Alloc[i][j]);
        for(int j=0; j<m; j++)
            scanf("%d", &Need[i][j]);
    }
    fclose(fp);

    int safe=0;

    for(int i=0; i<4;i++){
        int *request;
        request = read_request(i+1);
        int pid=request[0]-1;
        if(Need[pid][0]<request[1]||
           Need[pid][1]<request[2]||
           Need[pid][2]<request[3]) {
            printf("P%d Illegal !\n", pid+1);
            continue;
        }
        if(Available[0]<request[1]||
           Available[1]<request[2]||
           Available[2]<request[3]) {
            printf("P%d Unavailable !\n", pid+1);
            continue;
        }
        for(int j=0; j<m; j++){
            Available[j]-=request[j+1];
            Alloc[pid][j]+=request[j+1];
            Need[pid][j]-=request[j+1];
        }

        for(int p=0; p<n; p++){
            if(Available[0]>Need[p][0]&&
               Available[1]>Need[p][1]&&
               Available[2]>Need[p][2])
                safe=1;
        }

        if(safe){
            safe=0;
            printf("P%d Success!!!\n",pid+1);
        } else {
            for(int j=0; j<3; j++){
                Available[j]+=request[j+1];
                Alloc[pid][j]-=request[j+1];
                Need[pid][j]+=request[j+1];
            }
            printf("P%d Unavailable !\n",pid+1);
        }
    }

    return 0;
}