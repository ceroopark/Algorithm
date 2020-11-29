//
//  main.c
//  insert_selection_sort
//
//  Created by 박건영 on 2020/11/29.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void Swap(int *a, int *b);
void selection(int a[], int N);
void insert(int a[], int N);
void reversebubble(int *a, int n);
int main()
{
    
    int N, i, tmp;
    int *a, *b;
    clock_t start_1, end_1, start_2, end_2;
    scanf("%d", &N);
    
    a=(int *)malloc(sizeof(int)*N);
    b=(int *)malloc(sizeof(int)*N);//메모리 동적할당
    
    
    //A - 정렬이 안된 데이터가 주어지는 경우
    srand(time(NULL));
    for(i=0;i<N;i++){
        tmp=rand()%10;
        a[i]=tmp;
        b[i]=tmp;
    }
    
   
    
    //B - 정렬된 데이터가 입력되는 경우
    /*
    selection(a, N);
    selection(b, N);
    */
    
    //C - 역순으로 정렬된 데이터가 주어지는 경우
    /*
    reversebubble(a, N);
    reversebubble(b, N);
    */
    
    start_1=clock();
    selection(a, N);
    end_1=clock();
    start_2=clock();
    insert(b, N);
    end_2=clock();
    
    printf("%.9fms\n", ((double)(end_1-start_1)/CLOCKS_PER_SEC));
    printf("%.9fms\n", ((double)(end_2-start_2)/CLOCKS_PER_SEC));
   
    free(a);
    free(b);
    
}


void insert(int a[], int N)
{
    int i, j, save;
    
    for(i=1;i<=N-1;i++)
      {
          save=a[i];
          j=i-1;
          while(j>=0 && a[j]>save){
              a[j+1]=a[j];
              j-=1;
          }
          a[j+1]=save;
      }
}
void selection(int a[], int N){
    int i, j, max;
    for(i=N-1;i>=0;i--)
    {
        max=i;
        for(j=i-1;j>=0;j--){
            if(a[max]<a[j])
                max=j;
        }
        Swap(&a[i], &a[max]);
    }
    
}
void Swap(int *a, int *b)
{
    int tmp;
    tmp=*a;
    *a=*b;
    *b=tmp;
}
void reversebubble(int *a, int n)
{
    int i, j;
    for(i=0;i<n-1;i++)
    {
        for(j=0;j<n-i-1;j++)
        {
            if(a[j]<a[j+1])
                Swap(&a[j], &a[j+1]);
        }
    }
}
