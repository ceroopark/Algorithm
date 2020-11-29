//
//  main.c
//  quicksort
//
//  Created by 박건영 on 2020/11/29.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/*pivot 찾는 함수*/
int findPivotIndex(int *p, int pl, int pr){
    int a, b, c;
    if (pr - pl <= 1){
        return pl;
    }
    srand(time(NULL));
    a = (rand()% (pr-pl+1))+pl;
    b = (rand()% (pr-pl+1))+pl;
    c = (rand()% (pr-pl+1))+pl;
    if ((p[a]>=p[b]&&p[a]<=p[c])||(p[a]<=p[b]&&p[a]>=p[c]))
        return a;
    else if (((p[b]>=p[a])&&(p[b]<=p[c]))||((p[b]<=p[a])&&(p[b]>=p[c])))
        return b;
    else
        return c;
}
int inPlacePartition(int *p, int pl, int pr, int k){
    int temp, pivot;
    int i, j;
    i = pl;
    j = pr - 1;
    pivot = p[k];
    /*pivot 숨기기*/
    temp=p[k];
    p[k]=p[pr];
    p[pr]=temp;
    while(i<=j){
        while(i<=j&&p[i]<pivot) {
            i=i+1;
        }
        while(j>=i&&p[j]>=pivot) {
            j=j-1;
        }
        if(i<j){
            temp=p[i];
            p[i]=p[j];
            p[j]=temp;
        }
    }
    temp=p[i];
    p[i]=p[pr];
    p[pr]=temp;
    /*pivot 제위치 찾기*/
    
    j=pr-1;
    while(i<=j){
        while(i<=j&&p[i]==pivot) {
            j=j-1;
        }
        if (i<j&&p[i]==pivot){
            temp=p[i];
            p[i++]=p[j];
            p[j]=temp;
        }
    }
    return i;
}
void inPlaceQuickSort(int *p, int pl, int pr){
    if (pl >= pr)
        return;
    int k, a, b, c;
    k = findPivotIndex(p, pl, pr);
    c = b = inPlacePartition(p, pl, pr, k);
    while (1){
        if (p[c]!=p[b]){
            a=c+1;
            break;
        }
        c--;
    }
    inPlaceQuickSort(p, pl, a - 1);
    inPlaceQuickSort(p, b + 1, pr);
}
void printList(int *p, int N) {
    int i;
    for(i=0;i<N;i++) {
        printf(" %d", p[i]);
    }
}
int main(){
    int *p, N, i;
    scanf("%d", &N);
    p = (int*)malloc(sizeof(int)*N);
    for(i=0;i<N;i++){
        scanf("%d", &p[i]);
    }
    inPlaceQuickSort(p, 0, N-1);
    printList(p, N);
    free(p);
}

