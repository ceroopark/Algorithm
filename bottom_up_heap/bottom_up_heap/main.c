//
//  main.c
//  bottom_up_heap
//
//  Created by 박건영 on 2020/11/29.
//

#include <stdio.h>
#include <stdlib.h>

int H[100];
int n=0;
//함수 선언

void rBuildHeap(int i);
void buildHeap();
void downHeap(int i);
void printHeap();
void inPlaceHeapSort();

int main()
{
    scanf("%d", &n);
    for(int i=1;i<n+1;i++)
        scanf("%d", &H[i]);
    
    rBuildHeap(1);
    //inPlaceHeapSort();
    printHeap();
}
void rBuildHeap(int i)
{
    if(i>n)
        return;
    rBuildHeap(2*i);
    rBuildHeap(2*i+1);
    downHeap(i);
}
void buildHeap()
{
    for(int i=n/2;i>=1;i--)
    {
        downHeap(i);
    }
}
void downHeap(int i)
{
    int left, right;
    int greater, tmp;
    left=2*i;
    right=2*i+1;
    if(left>n)
        return;
    greater=left;
    if(right<=n)
    {
        if(H[right]>H[left])
            greater=right;
    }
    if(H[i]>=H[greater])
        return;
    tmp=H[i];
    H[i]=H[greater];
    H[greater]=tmp;
    downHeap(greater);
}
void printHeap()
{
    for(int i=1;i<n+1;i++){
        printf(" %d", H[i]);
    }
    printf("\n");
}
void inPlaceHeapSort()
{
    int tmp;
   
    for(int i=n;i>1;i--)
    {
        printHeap();
        printf("\n");
        tmp=H[1];
        H[1]=H[i];
        H[i]=tmp;
        downHeap(i-1);
        printHeap();
        printf("\n");
    }
}
