//
//  main.c
//  mergesort
//
//  Created by 박건영 on 2020/11/29.
//
//
#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node *next;
}node;

/*for list*/
void addList(node **L, int data);
void printList(node *L);

/*for merge sort*/
void partition(node *L, node **L1, node **L2, int n)
{
    node *p=L;
    *L1=L;
    for(int i=0;i<n/2-1;i++)
    {
        p=p->next;
    }
    *L2=p->next;
    p->next=NULL;
}
node* merge(node **L1, node **L2)
{
    node *p, *L, *A, *B;
    A=*L1;
    B=*L2;
    if(A->data<=B->data)
    {
        L=A;
        A=A->next;
        p=L;
    }
    else{
        L=B;
        B=B->next;
        p=L;
    }
    while((A!=NULL)&&(B!=NULL))
    {
        if(A->data<=B->data)
        {
            p->next=A;
            A=A->next;
            p=p->next;
        }
        else
        {
            p->next=B;
            B=B->next;
            p=p->next;
        }
    }
    while(A!=NULL)
    {
        p->next=A;
        A=A->next;
        p=p->next;
    }
    while(B!=NULL)
    {
        p->next=B;
        B=B->next;
        p=p->next;
    }
    return L;
}
void mergeSort(node **L, int n)
{
    node *L1, *L2, *p = *L;
    if (n > 1){
        partition(p, &L1, &L2, n);
        if ((n%2)==0){
            mergeSort(&L1, n/2);
            mergeSort(&L2, n/2);
        }
        else{
            mergeSort(&L1, n/2);
            mergeSort(&L2, (n/2)+1);
        }
        *L = merge(&L1, &L2);
    }
}
int main() {
    int N, i, data;
    node *L=NULL;
    scanf("%d", &N);
    for(i=0;i<N;i++)
    {
        scanf("%d", &data);
        addList(&L, data);
    }
    mergeSort(&L, N);
    printList(L);
    
}
void addList(node **L, int data)
{
    node *p=*L, *newNode;
    newNode=(node *)malloc(sizeof(node));
    newNode->data=data;
    newNode->next=NULL;
    if(*L==NULL)
        *L=newNode;
    else{
        while(p->next!=NULL)
        {
            p=p->next;
        }
        p->next=newNode;//Find Empty Space
    }
}
void printList(node *L)
{
    node *p=L;
    while(p!=NULL){
        printf(" %d", p->data);
        p=p->next;
    }
    printf("\n");
}
