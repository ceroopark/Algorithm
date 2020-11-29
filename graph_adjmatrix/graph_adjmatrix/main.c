//
//  main.c
//  graph_adjmatrix
//
//  Created by 박건영 on 2020/11/29.
//

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef struct{
    int vn;//the number of vertex
    int **matrix;
}Graph;

Graph* NewGraph(int max_vertex);
void AddEdge(Graph *graph, int start, int goal, int weight);
Graph * MakeGraph();
void ViewNieghbors(Graph* graph);
void DeleteGraph(Graph* graph);
void ViewNieghbor(Graph* graph, int vt);
void aExecutation(Graph* graph, int vt);
void mExecutation(Graph* graph, int v1, int v2, int Weight);
int main()
{
    Graph* graph;
    graph=MakeGraph();
//    for(int i=1;i<=6;i++){
//        for(int j=1;j<=6;j++){
//            printf("%d ", graph->matrix[i][j]);
//        }
//        printf("\n");
//    }
//    ViewNieghbors(graph);

    char ch;
    int id, v1, v2, w;
    do
    {
        scanf("%c", &ch);
        switch (ch)
        {
            case 'a':
                scanf("%d", &id);
                aExecutation(graph, id);
                break;
            case 'm':
                scanf("%d %d %d", &v1,&v2,&w);
                mExecutation(graph,v1,v2,w);
//                for(int i=1;i<=6;i++){
//                    for(int j=1;j<=6;j++){
//                        printf("%d ", graph->matrix[i][j]);
//                    }
//                    printf("\n");
//                }
                break;
            default:
                break;
        }
    }while (ch!='q');
    
    DeleteGraph(graph);
    return 0;
}


Graph * MakeGraph()
{
    Graph* graph;
    graph=NewGraph(6);
    AddEdge(graph, 1, 2, 1);
    AddEdge(graph, 1, 3, 1);
    AddEdge(graph, 2, 3, 1);
    AddEdge(graph, 1, 4, 1);
    AddEdge(graph, 1, 6, 2);
    AddEdge(graph, 3, 5, 4);
    AddEdge(graph, 5, 5, 4);
    AddEdge(graph, 5, 6, 3);
    
    return graph;
    
}
Graph* NewGraph(int max_vertex)
{
    int i, j;
    Graph* graph=(Graph *)malloc(sizeof(Graph));
    graph->vn=max_vertex;
    graph->matrix=(int **)malloc(sizeof(int *)*(max_vertex+1));
    for(i=1;i<=max_vertex;i++)
    {
        graph->matrix[i]=(int *)malloc(sizeof(int)*(max_vertex+1));
        for(j=1;j<=max_vertex;j++)
            graph->matrix[i][j]=-1;
   //         memset(graph->matrix[i], 0, sizeof(int)*max_vertex);
    }
//    for(int i=1;i<=6;i++){
//        for(int j=1;j<=6;j++){
//            printf("%d ", graph->matrix[i][j]);
//        }
//        printf("\n");
//    }
    return graph;
}
void AddEdge(Graph *graph, int start, int goal, int weight)
{
    graph->matrix[start][goal]=weight;
    graph->matrix[goal][start]=weight;
}
void ViewNieghbors(Graph* graph)
{
    int i;
    for(i=1;i<=graph->vn;i++)
    {
        printf("%d의 이웃:", i);
        ViewNieghbor(graph, i);
        printf("\n");
    }
}
void ViewNieghbor(Graph* graph, int vt)
{
    int i;
    for(i=1;i<=graph->vn;i++)
    {
        if(graph->matrix[vt][i]!=0)
            printf("%d ", i);
    }
}
void DeleteGraph(Graph* graph)
{
    int i=1;
    for(i=1;i<=graph->vn;i++)
    free(graph->matrix[i]);
    
    free(graph->matrix);
    free(graph);
}
void aExecutation(Graph* graph, int vt)
{
    int i;
    if(vt<1||vt>graph->vn){
        printf("-1\n");
    }
    else{
        for(i=1;i<=graph->vn;i++)
        {
            if(graph->matrix[vt][i]>0)
                printf(" %d %d", i, graph->matrix[vt][i]);
        }
        printf("\n");
    }
}
void mExecutation(Graph* graph, int v1, int v2, int Weight)
{
    if((v1<1||v1>graph->vn)||(v2<1||v2>graph->vn))
    {
        printf("-1\n");
        return;
    }
    
    if(graph->matrix[v1][v2]!=-1){
        if(Weight==0){
            graph->matrix[v1][v2]=-1;
            graph->matrix[v2][v1]=-1;
        }
        else{
            graph->matrix[v1][v2]=Weight;
            graph->matrix[v2][v1]=Weight;
        }
    }
        
    else{
        AddEdge(graph, v1, v2, Weight);
        
    }
}
