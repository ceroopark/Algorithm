//
//  main.c
//  AVL_TREE
//
//  Created by 박건영 on 2020/11/29.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*treenode declartion*/
typedef struct node {
    int key;
    int height;
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
void expandExternal(TreeNode* w) {
    TreeNode *L = NULL, *R = NULL;
    L=(TreeNode *)malloc(sizeof(TreeNode)*1);
    R=(TreeNode *)malloc(sizeof(TreeNode)*1);
    L->lchild = NULL;
    L->rchild = NULL;
    L->height=0;
    L->parent = w;
    R->lchild = NULL;
    R->rchild = NULL;
    R->height = 0;
    R->parent = w;
    w->lchild = L;
    w->rchild = R;
    w->height = 1;
    return;
}
int updateHeight(TreeNode *w) {

    int height;
    if (w->lchild->height > w->rchild->height) {
        height = w->lchild->height + 1;
    }
    else {
        height = w->rchild->height + 1;
    }
    if (height != w->height) {
        w->height = height;
        return 1;
    }
    else {
        return 0;
    }
}
int isBalanced(TreeNode *w) {

    if ((-1 <= (w->lchild->height - w->rchild->height)) && ((w->lchild->height - w->rchild->height) <= 1))
        return 1;
    else
        return 0;
}
TreeNode* restructure(TreeNode *x, TreeNode *y, TreeNode *z) {

    TreeNode *a, *b, *c;
    TreeNode *T0, *T1, *T2, *T3;
    if ((z->key < y->key) && (y->key < x->key)) {
        a = z;
        b = y;
        c = x;
        T0 = a->lchild;
        T1 = b->lchild;
        T2 = c->lchild;
        T3 = c->rchild;
    }
    else if ((x->key < y->key) && (y->key < z->key)) {
        a = x;
        b = y;
        c = z;
        T0 = a->lchild;
        T1 = a->rchild;
        T2 = b->rchild;
        T3 = c->rchild;
    }
    else if ((z->key < x->key) && (x->key < y->key)) {
        a = z;
        b = x;
        c = y;
        T0 = a->lchild;
        T1 = b->lchild;
        T2 = b->rchild;
        T3 = c->rchild;
    }
    else {
        a = y;
        b = x;
        c = z;
        T0 = a->lchild;
        T1 = b->lchild;
        T2 = b->rchild;
        T3 = c->rchild;
    }
    if (z->parent == NULL) {
        BST = b;
        b->parent = NULL;
    }
    else if (z->parent->lchild == z) {
        z->parent->lchild = b;
        b->parent = z->parent;
    }
    else if (z->parent->rchild == z) {
        z->parent->rchild = b;
        b->parent = z->parent;
    }
    a->lchild = T0;
    T0->parent = a;
    a->rchild = T1;
    T1->parent = a;
    updateHeight(a);
    c->lchild = T2;
    T2->parent = c;
    c->rchild = T3;
    T3->parent = c;
    updateHeight(c);
    b->lchild = a;
    a->parent = b;
    b->rchild = c;
    c->parent = b;
    updateHeight(b);
    return b;
}
void searchAndFixAfterInsertion(TreeNode *w) {
    TreeNode *x, *y, *z;
    w->lchild->height = 0;
    w->rchild->height = 0;
    w->height = 1;
    if (w->parent == NULL)
        return;
    z = w->parent;
    while (updateHeight(z) && isBalanced(z)) {
        if (z->parent == NULL) {
            return;
        }
        z = z->parent;
    }
    if (isBalanced(z))
        return;
    if (z->lchild->height > z->rchild->height)
        y = z->lchild;
    else
        y = z->rchild;
    if (y->lchild->height > y->rchild->height)
        x = y->lchild;
    else
        x = y->rchild;
    restructure(x, y, z);
    return;
}

void insertItem(int k) {
    TreeNode* w=treeSearch(BST, k);
    if (isInternal(w))
        return;
    else{
       w->key = k;
       expandExternal(w);
       searchAndFixAfterInsertion(w);
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
void searchAndFixAfterRemoval(TreeNode *w) {
    TreeNode *x, *y, *z, *b;
    if (w == NULL)
        return;
    z = w;
    while (updateHeight(z) && isBalanced(z)) {
        if (z->parent == NULL)
            return;
        z = z->parent;
    }
    if (isBalanced(z))
        return;

    if (z->lchild->height > z->rchild->height)
        y = z->lchild;
    else
        y = z->rchild;

    if (y->lchild->height > y->rchild->height)
        x = y->lchild;

    else if (y->lchild->height < y->rchild->height)
        x = y->rchild;

    else {

        if (z->lchild == y)
            x = y->lchild;
        else if (z->rchild == y)
            x = y->rchild;
    }
    b = restructure(x, y, z);
    searchAndFixAfterRemoval(b->parent);
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
   TreeNode* w = NULL, *z = NULL, *y = NULL, *zs=NULL;
   int e;

   w = treeSearch(BST, k);
   if (isExternal(w))
      return -1; //NoSuchTree
   e = w->key;
   z = w->lchild;
   if (!isExternal(z))
      z = w->rchild;
   if (isExternal(z))
      zs=reduceExternal(z);
   else {
      y = inOrderSucc(w);
      z = y->lchild;
      w->key = y->key;
      zs= reduceExternal(z);
   }
   searchAndFixAfterRemoval(zs->parent);
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

