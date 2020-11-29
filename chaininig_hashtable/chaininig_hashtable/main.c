//
//  main.c
//  chaininig_hashtable
//
//  Created by 박건영 on 2020/11/29.
//

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node {
    struct node *next;
    int id;

}Node;

typedef struct Hash {
    int idx;
    struct node *next;
}Hash;

Node *getNode(int id, Node *next) {
    Node *p = (Node*)malloc(sizeof(Node));
    p->id = id;
    p->next = next;
    return p;
}

void insert(Hash *H, int id, int m) {
    int idx = id%m;
    Node *node = H[idx].next;
    Node *newNode;
    newNode = getNode(id, node->next);
    node->next=newNode;
}
void search(Hash *H, int id, int m) {
    Node *node = H[id%m].next->next;
    int out = 1;
    while (node) {
        if (node->id == id) {
            printf("%d\n", out);
            return;
        }
        node = node->next;
        out++;
    }
    printf("0\n");
}
void delete(Hash *H, int id, int m) {
    Node *node = H[id%m].next;
    Node *tmp;
    int output = 1;
    while (node->next) {
        if (node->next->id == id) {
            tmp = node->next;
            node->next = node->next->next;
            free(tmp);
            printf("%d\n", output);
            return;
        }
        node = node->next;
        output++;
    }
    printf("0\n");
}
void print_Hash(Hash *H, int m) {
    int i;
    Node *nd;
    for (i = 0; i < m; i++) {
        nd = H[i].next->next;
        while (nd) {
            printf(" %d", nd->id);
            nd = nd->next;
        }
    }
    printf("\n");

}
int main() {
    int M;
    scanf("%d", &M);
    Hash *H = (Hash*)malloc(sizeof(Hash)*M);//M size
    
    for(int i=0;i<M;i++)
    {
        H[i].idx=i;
        H[i].next=getNode(-1, NULL);
    }
    getchar();
    int id;
    char c;
    while(1) {
        scanf("%c", &c);//중복 x
        switch (c)
        {
        case 'i':
            scanf("%d", &id);
            insert(H,id, M);
            break;
        case 's':
            scanf("%d", &id);
            search(H, id, M);
            break;
        case 'd':
            scanf("%d", &id);
            delete(H, id, M);
            break;
        case 'p':
            print_Hash(H, M);
            break;
        default:
            break;
        }
        if (c == 'e')
            break;
        getchar();
    }
    return 0;
}
