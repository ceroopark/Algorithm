//
//  main.c
//  BSTree_recur
//
//  Created by 박건영 on 2020/11/29.
//

#include <stdio.h>
#include <stdlib.h>

int idk=-1;

int rB_serach(int *p, int l, int r, int s)
{
    int mid;
    if(l>r)
        return -1;//no key
    
    mid=(l+r)/2;
    
    if(p[mid]==s){
        return mid;
    }
    else if(s<p[mid]){
        return rB_serach(p, l, mid-1, s);
    }
    else{//s>p[mid]
        if(idk==-1){
            idk=mid;
        }
        else if(p[idk]<p[mid])
        {
            idk=mid;
        }
        return rB_serach(p, mid+1, r, s);
    }
    
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
    idx=rB_serach(p, 0, N-1, M);
    
    if(idx==-1){
        if (idk == -1)
            printf("%d", idx);
        else
            printf(" %d\n", idk);
    }
        
    else{
        printf(" %d", idx);
    }
    
    
    free(p);
}


