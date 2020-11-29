//
//  main.c
//  BSTree_nonrecur
//
//  Created by 박건영 on 2020/11/29.
//
#include <stdio.h>
#include <stdlib.h>

int idk=-1;

int B_serach(int *p, int n, int key)
{
    int pl=0;
    int pr=n-1;
    int pc;
    do{
        pc=(pl+pr)/2;
        if(p[pc]==key)
            return pc;
        else if(p[pc]<key)
        {
            pl=pc+1;
        }
        else{//key<p[pc]
            if(idk==-1)
                idk=pc;
            else if(p[idk]>p[pc])
                idk=pc;
            pr=pc-1;
        }
    }while(pl<=pr);//check
    return -1;
}
int main()
{
    int N, M, *p;
    int i, idx;
    scanf("%d", &N);//array_size
    scanf("%d", &M);//key
    p=(int *)malloc(sizeof(int)*N);
    for(i=0;i<N;i++)
        scanf("%d", &p[i]);
    idx=B_serach(p, N, M);
    if(idx==-1){
        if (idk == -1)
            printf("%d", N);
        else
            printf(" %d\n", idk);
    }
          
    else{
        printf(" %d", idx);
    }
    
    free(p);
}


