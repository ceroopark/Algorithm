//
//  main.c
//  tree_structure
//
//  Created by 박건영 on 2020/11/29.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
    int data;
    struct node *left;
    struct node *right;
}Tree;
Tree* AllocTree(void)
{
    Tree *nd=(Tree *)malloc(sizeof(Tree));
    return nd;
}
void Setdata(Tree *bt, int data)
{
    bt->data=data;
}

void CreatNode(Tree *L){
 
    int parent,left_child,right_child;
    scanf("%d %d %d",&parent,&left_child,&right_child);
    getchar();
   
     
    Tree *leftson;
    leftson=AllocTree();
    Setdata(leftson, left_child);
    L->left=leftson;
 
     
    Tree *rightson;
    rightson=AllocTree();
    Setdata(rightson, right_child);
    L->right=rightson;
  
    if(left_child!=0){
        CreatNode(L->left);
    }
    if(right_child!=0){
        CreatNode(L->right);
    }
    return;
}

int main()
{
    Tree *tree;
    int cmdnum, N;
    
    scanf("%d",&cmdnum);
    getchar();
  
    int left_child,right_child,parent;
    scanf("%d %d %d",&parent,&left_child,&right_child);
    getchar();
    
    Tree *rootnode;
    rootnode=AllocTree();
    Setdata(rootnode,parent);
    tree = rootnode;
    
    Tree *leftson;
    leftson=AllocTree();
    Setdata(leftson, left_child);
    rootnode->left=leftson;
    if(left_child!=0)
        CreatNode(tree->left);
    
    Tree *rightson;
    rightson=AllocTree();
    Setdata(rightson, right_child);
    rootnode->right=rightson;
    if(right_child!=0)
        CreatNode(tree->right);
    
    scanf("%d",&N);
    getchar();
    Tree *temp;
    char str[100];
    int length;
    
    for(int i=0; i<N;i++){
        temp=tree;
        scanf("%s", str);
        getchar();
        length=strlen(str);
        printf(" %d", tree->data);
        for(int j=0;j<length;j++)
        {
            if(str[j]=='L'){
                temp=temp->left;
                printf(" %d",temp->data );
            }
                
            if(str[j]=='R'){
                temp=temp->right;
                printf(" %d",temp->data );
        }
        
        }
        printf("\n");
    }
        
    
    return 0;
    
}
