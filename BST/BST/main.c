//
//  main.c
//  BST
//
//  Created by 박건영 on 2020/11/29.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*treenode declartion*/
typedef struct node {
    int key;
   struct node* parent;
   struct node* lchild;
   struct node* rchild;
}TreeNode;

/*tree root!*/
TreeNode* BST = NULL;

void getnode(TreeNode** p) {
   (*p) = (TreeNode*)malloc(1 * sizeof(TreeNode));
}

/*external node*/
int isExternal(TreeNode* w) {
   if (w->lchild == NULL && w->rchild == NULL)
      return 1;
   else
      return 0;
}

/*internal node*/
int isInternal(TreeNode* w) {
   if (w->lchild != NULL && w->rchild != NULL)
      return 1;
   else
      return 0;
}

TreeNode* treeSearch(TreeNode* v, int k) {
   if (isExternal(v))
      return v;
   if (k == v->key)
      return v;
   else if (k < v->key)
      return treeSearch(v->lchild, k);
   else
      return treeSearch(v->rchild, k);
}

int findElement(int k) {
   TreeNode* w = NULL;

   w = treeSearch(BST, k);
   if (isExternal(w))
      return -1; //NoSuchKey
   else
      return w->key;
}
void expandExternal(TreeNode* z) {
    TreeNode *L = NULL, *R = NULL;
    L=(TreeNode *)malloc(sizeof(TreeNode)*1);
    R=(TreeNode *)malloc(sizeof(TreeNode)*1);
    L->lchild = NULL;
    L->rchild = NULL;
    L->parent = z;
    R->lchild = NULL;
    R->rchild = NULL;
    R->parent = z;
    z->lchild = L;
    z->rchild = R;
    return;
}

void insertItem(int k) {
   TreeNode* w = NULL;

   w = treeSearch(BST, k);
   if (isInternal(w))
      return;
   else {
      w->key = k;
      expandExternal(w);
      return;
   }
}

TreeNode* sibling(TreeNode* w) {
   if (w->parent == NULL)
      return NULL;
   if ((w->parent)->lchild == w)
      return w->parent->rchild;
   else
      return w->parent->lchild;
}

TreeNode* reduceExternal(TreeNode* z) {
   TreeNode* w = NULL, *zs = NULL, *g = NULL;

   w = z->parent;
   zs = sibling(z);
   if (w->parent == NULL) {
      BST = zs;
      zs->parent = NULL;
   }
   else {
      g = w->parent;
      zs->parent = g;
      if (w == g->lchild)
         g->lchild = zs;
      else
         g->rchild = zs;
   }
   free(z);
   free(w);
   return zs;
}

TreeNode* inOrderSucc(TreeNode* w) {
   w = w->rchild;
   if (isExternal(w))
      return NULL;
   while (isInternal(w->lchild))
      w = w->lchild;
   return w;
}

int removeElement(int k) {
   TreeNode* w = NULL, *z = NULL, *y = NULL;
   int e;

   w = treeSearch(BST, k);
   if (isExternal(w))
      return -1; //NoSuchTree
   e = w->key;
   z = w->lchild;
   if (!isExternal(z))
      z = w->rchild;
   if (isExternal(z))
      reduceExternal(z);
   else {
      y = inOrderSucc(w);
      z = y->lchild;
      w->key = y->key;
      reduceExternal(z);
   }
   return e;
}

void preOrder(TreeNode* node) {
   if (isInternal(node)) {
      printf(" %d", node->key);
      preOrder(node->lchild);
      preOrder(node->rchild);
   }
}

int main()
{
    char order;
    int key, val;
    /*root initialize*/
    BST=(TreeNode *)malloc(sizeof(TreeNode)*1);
    BST->parent = NULL;
    BST->lchild = NULL;
    BST->rchild = NULL;

    while (1) {
        scanf("%c", &order);
        if (order=='i'){
            scanf("%d", &key);
            getchar();
            insertItem(key);
        }
        else if(order=='d') {
            scanf("%d", &key);
            getchar();
            val = removeElement(key);
            if (val==-1)
                printf("X\n");
            else
                printf("%d\n", val);
        }
        else if(order=='s') {
            scanf("%d", &key);
            getchar();
            key=findElement(key);
            if(key==-1)
                printf("X\n");
            else
                printf("%d\n", key);
        }
        else if(order=='p') {
            preOrder(BST);
            printf("\n");
        }
        else if (order == 'q')
            break;
    }
}
