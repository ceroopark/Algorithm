//
//  main.c
//  linear_probinig_hashtable
//
//  Created by 박건영 on 2020/11/29.
//
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int getNextBucket(int v, int i, int M) {
    return (v + i) % M;
}

void insert_key(int *H, int x, int M) {
    int i;
    if (H[x%M] == 0) {//빈 버켓일 경우
        H[x%M] = x;
        printf("%d\n", x%M);
        return;
    }
    for (i = 1; ;i++) {
        printf("C");
        if (H[(x%M+i)%M] == 0) {
            H[(x%M + i) % M] = x;
            printf("%d\n", (x%M + i) % M);
            return;
        }
    }
}

void search(int *H, int x, int M) {
    int v=x%M;
    int i=0, b;
    while(i<M)
    {
        b=getNextBucket(v, i, M);
        if(H[b]==0)
        {
            printf("-1\n");
            return;
        }
        else if(H[b]==x)
        {
            printf("%d %d\n", b, H[b]);
            return;
        }
        else{
            i+=1;
        }
    }
    printf("-1\n");
    /*
    for (int i = 0; i < M; i++) {
        if (H[i] == x) {
            printf("%d %d\n", i, x);
            return;
        }
    }
    printf("-1\n");*/
}

int main() {
    int M, N;
    scanf("%d%d", &M,&N);
    getchar();
    char c;
    int *hash_Table = (int*)malloc(sizeof(int)*M);
    int i;
    for (i = 0; i < M; i++) {
        hash_Table[i] = 0;
    }
    while (1) {
        int cnt = 0;
        int x;
        scanf("%c", &c);
        switch (c)
        {
        case 'i':
            scanf("%d", &x);
            insert_key(hash_Table, x, M);
            cnt++;
            if (cnt > N)
                continue;
            break;
        case 's':
            scanf("%d", &x);
            search(hash_Table,x, M);
            break;
        default:
            break;
        }
        getchar();
        if (c == 'e')
            break;
    }
}
