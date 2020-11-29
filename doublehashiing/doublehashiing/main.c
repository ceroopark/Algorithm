//
//  main.c
//  doublehashiing
//
//  Created by 박건영 on 2020/11/29.
//

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int M, n, q, *hash_table;
/*1st_hash*/
int h(int x) {
    return x % M;
}
/*2nd_hash*/
int h2(int x) {
    return q - (x % q);
}
/*get next*/
int getNextBucket(int v, int i, int k) {
    return(v + i * h2(k) % M) % M;
}
/*insert*/
void insertkey(int k) {
    int v = h(k);
    int i = 0, b;
    while (i < M) {
        b = getNextBucket(v, i, k);
        if (hash_table[b] == 0) {
            hash_table[b] = k;
            for (int j = 0; j < i; j++) {
                printf("C");
            }
            printf("%d\n", b);
            return;
        }
        else {
            i = i + 1;
        }
    }
}
/*seartch*/
void search(int k) {
    int v = h(k);
    int i = 0, b;
    while (i < M) {
        b = getNextBucket(v, i, k);
        if (hash_table[b] == 0) {
            printf("-1\n");
            return;
        }
        else if (hash_table[b] == k) {
            printf("%d %d\n", b, hash_table[b]);
            return;
        }
        else {
            i = i + 1;
        }
    }
    printf("-1\n");
}

void print() {
    for (int i = 0; i < M; i++) {
        printf(" %d", hash_table[i]);
    }
    printf("\n");
}

int main() {
    int key, i;
    char sel;
    scanf("%d", &M);
    hash_table = (int*)malloc(sizeof(int)*M);
    for (i = 0; i < M; i++) {
        *(hash_table + i) = 0;
    }
    scanf("%d", &n);
    scanf("%d", &q);
    while (1) {
        scanf("%c", &sel);
        if (sel == 'i') {
            scanf("%d", &key);
            getchar();
            insertkey(key);
        }
        else if (sel == 's') {
            scanf("%d", &key);
            getchar();
            search(key);
        }
        else if (sel == 'p') {
            print();
            getchar();//!
        }
        else if (sel == 'e') {
            print();
            break;
        }
    }
    free(hash_table);
}

