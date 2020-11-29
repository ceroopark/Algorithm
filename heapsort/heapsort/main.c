//
//  main.c
//  heapsort
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
void heapSort();

int main()
{
    scanf("%d", &n);
    for(int i=1;i<n+1;i++)
        scanf("%d", &H[i]);
    
    rBuildHeap(1);
   // printHeap();
    heapSort();
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
    int tmp, chm;
    while(2*i<=n){
        chm=2*i;
        if(2*i+1<=n){
            if(H[chm]<H[2*i+1]){
                chm=2*i+1;
            }
        }
        if(H[i]<H[chm])
        {
            tmp=H[i];
            H[i]=H[chm];
            H[chm]=tmp;
        }
        i=chm;
    }
}
void printHeap()
{
    for(int i=1;i<n+1;i++){
        printf(" %d", H[i]);
    }
    printf("\n");
}
void heapSort()
{
    for(int i=n;i>1;i--)//error
    {
        int tmp=H[1];
        H[1]=H[i];
        H[i]=tmp;
       // printHeap();
        int root=1;
        int c;
        do{
            c=2*root;//자식
            if(H[c]<H[c+1]&&c<i-1){
                c++;
            }
            if(H[root]<H[c]&&c<i){
                int tmp=H[root];
                H[root]=H[c];
                H[c]=tmp;
            }
            root=c;
        }while(c<i);
        //printHeap();
    }
}
