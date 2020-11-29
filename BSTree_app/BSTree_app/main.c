//
//  main.c
//  BSTree_app
//
//  Created by 박건영 on 2020/11/29.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
int main()
{
    
    int A, B, cnt, M;
    int idx, K;

    srand(time(NULL));
    scanf("%d %d %d", &A, &B, &cnt);
    getchar();
    K=A+rand()%(B-A+1); //정답 생성
   
    char ch[cnt];
    gets(ch);
    for(int i=0;i<cnt;i++){
        
        M=(A+B)/2;
        
        if(ch[i]=='Y')//K>M
        {
            A=M+1;
        }
        else{
            B=M;
        }
    }
    printf("%d", A);
     
    
    
}



