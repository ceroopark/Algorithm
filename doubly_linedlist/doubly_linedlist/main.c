//
//  main.c
//  doubly_linedlist
//
//  Created by 박건영 on 2020/11/29.
//

#include <stdio.h>
#include <stdlib.h>


typedef struct node {
    struct node* prev;
    struct node* next;
    char data;
}node;

typedef struct List {
    node* head;
    int posi;
    node* tail;
}list;

void init(list* List) {
    node *Head, *Tail;
    Head = (node*)malloc(sizeof(node));
    Tail = (node*)malloc(sizeof(node));
 
    List->head = Head;
    Head->prev = NULL;
    Head->next = Tail;
 
 
    List->tail = Tail;
    Tail->next = NULL;
    Tail->prev = Head;
 
    List->posi = 2;
}

void add(list* List) {
    int chk;
    char new;
    int find;
    scanf("%d %c",&find,&new);
    getchar();
    
    if ((List->posi)-1 < find) {
        printf("invalid position\n");
        return;
        }
 
    node *temp, *newnode;
    temp = List->head;
   
    
    newnode = (node*)malloc(sizeof(node));
    newnode->data = new;
   
    for (int i = 0; i<find; i++)
        temp=temp->next;
    newnode->next = temp;
    newnode->prev = temp->prev;
    temp->prev = newnode;
    temp = newnode->prev;
    temp->next = newnode;
    chk = (List->posi);
    chk++;
    List->posi = chk;
 
}

void delete(list* List) {
    int chk;
    int find;
    scanf("%d",&find);
    getchar();
    //위치가 정확하지 않을 때
    if ((List->posi)-2 < find) {
        printf("invalid position\n");
        return;
        }
 
    node *temp, *atemp, *btemp;
 
    temp = List->head;
    
    for (int i = 0; i<find; i++)
        temp=temp->next;
    atemp = temp->prev;
    btemp = temp->next;
    atemp->next = btemp;
    btemp->prev = atemp;
    free(temp);//없애기
    chk = (List->posi);
    chk--;
    List->posi = chk;
}

void get(list* List) {
    node *temp;
    temp = List->head;
    int getnum;
    scanf("%d",&getnum);
    getchar();
   
    if ((List->posi)-2 < getnum) {
            printf("invalid position\n");
            return;
        }
 
    for (int i = 0; i<getnum; i++)
        temp=temp->next;
   
    printf("%c\n", temp->data);
}

void print(list* List) {
    node *temp;
    temp = List->head;

    for (int i = 0; i<(List->posi)-2; i++) {
        temp = temp->next;
        printf("%c", temp->data);
    }
    printf("\n");
}
 
 
int main(void)
{
    int N;
    char s;
 
    list* List;
    List = (list*)malloc(sizeof(list));
    init(List);
  
 
    scanf("%d", &N);
    getchar();
    for (int i = 0; i < N; i++) {
        scanf("%c", &s);
        getchar();
         
        if (s == 'A') {
            add(List);
            continue;
        }
        else if (s == 'D') {
            delete(List);
            continue;
        }
        else if (s == 'G') {
            get(List);
            continue;
        }
        else if (s == 'P') {
            print(List);
            continue;
        }
    }
 
    return 0;
}
