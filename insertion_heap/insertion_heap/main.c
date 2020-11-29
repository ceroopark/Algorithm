//
//  main.c
//  insertion_heap
//
//  Created by 박건영 on 2020/11/29.
//

#include <stdio.h>
#include <stdlib.h>

int H[100];
int n=0;
//함수 선언
void insertItem(int key);
int removeMax();
void upHeap(int i);
void downHeap(int i);
void printHeap();

int main()
{
    int key;
    char ch;
    while(1){
        scanf("%c", &ch);
        if(ch=='i'){
            scanf("%d", &key);
            insertItem(key);
        }
        else if(ch=='d'){
            printf("%d\n", removeMax());
        }
        else if(ch=='p')
            printHeap();
        else if(ch=='q')
            return 0;
    }
}
void insertItem(int key)
{
    n++; //1부터 채우기
    H[n]=key;
    upHeap(n);
    printf("0\n");
}
int removeMax()
{
    int key;
    key=H[1];
    H[1]=H[n];
    n--;
    downHeap(1);
    return key;
}
void upHeap(int i)
{
    int tmp;
    while(i>1)
    {
        if(H[i]>H[i/2]){
            tmp=H[i];
            H[i]=H[i/2];
            H[i/2]=tmp;
        }
        i/=2;
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
