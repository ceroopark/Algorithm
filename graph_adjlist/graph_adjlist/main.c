//
//  main.c
//  graph_adjlist
//
//  Created by 박건영 on 2020/11/29.
//

#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
   struct Node *next;
   int pc;
}Node;

typedef struct Vertex {
   int vname;
   struct Node* Toincidence;
}Vertex;

typedef struct Edge {
   int v1, v2;
   int edgename;
   int weight;
}Edge;

typedef struct Graph {
   struct Vertex *vertices;
   struct Edge *edges;
   int size;
   int egdesize;
   int cur;
}Graph;

Node *get_node(int e_id, Node*next) {
   Node *p = (Node*)malloc(sizeof(Node));
   p->pc = e_id;
   p->next = next;
   return p;
}

void set_vertices(Graph *graph) {
   int vsize = graph->size;
   int i;
   graph->vertices = (Vertex*)malloc(sizeof(Vertex)*vsize);
   for (i = 0; i < vsize; i++) {
      graph->vertices[i].vname = i;
      graph->vertices[i].Toincidence = get_node(-1, NULL);
   }
}

int opposite(Graph *G,Node *nodeNext, int v1) {
   Edge e = G->edges[nodeNext->pc];
   return (e.v1 != v1) ? e.v1 : e.v2;
}

void insert_node(Graph *G, int ename,int v1,int v2) {
   Node*node = G->vertices[v1].Toincidence;
   Node *new_node = NULL;

   while (node->next && opposite(G,node->next,v1)<v2) {
      node = node->next;
   }
   new_node = get_node(ename, node->next);
   node->next = new_node;
}
void adeEdge(Graph *graph, int edge_name, int v1, int v2, int weight) {
   graph->edges[edge_name].edgename = edge_name;
   graph->edges[edge_name].v1 = v1;
   graph->edges[edge_name].v2 = v2;
   graph->edges[edge_name].weight = weight;
   graph->cur++;
   insert_node(graph, edge_name,v1,v2);
   if (v1 != v2)
      insert_node(graph, edge_name, v2, v1);
}
void setEdge(Graph *G) {
   int esize = G->egdesize;
   int i;
   G->edges = (Edge*)malloc(sizeof(Edge)*esize);
   for (i = 0; i < esize; i++) {
      G->edges[i].edgename = -1;
      G->edges[i].v1 = -1;
      G->edges[i].v2 = -1;
      G->edges[i].weight = -1;
   }
   adeEdge(G, 0, 1, 2, 1);
   adeEdge(G, 1, 1, 3, 1);
   adeEdge(G, 2, 1, 4, 1);
   adeEdge(G, 3, 1, 6, 2);
   adeEdge(G, 4, 2, 3, 1);
   adeEdge(G, 5, 3, 5, 4);
   adeEdge(G, 6, 5, 5, 4);
   adeEdge(G, 7, 5, 6, 3);
}
void construct_G(Graph *G, int vsize, int esize) {
   G->egdesize = esize;
   G->size = vsize;
   set_vertices(G);
   setEdge(G);
}
void p(Graph *G, int vname) {
   if (G->size - 1 < vname || vname <= 0) {
      printf("-1\n");
      return;
   }
   Node *node = G->vertices[vname].Toincidence->next;
   int eindex = 0;
   while (node) {
      eindex = node->pc;
      if (G->edges[eindex].weight != -1) {
         if (G->edges[eindex].v1 == vname && G->edges[eindex].v2 == vname)
            printf(" %d %d", G->edges[eindex].v1, G->edges[eindex].weight);
         else if (G->edges[eindex].v1 != vname)
            printf(" %d %d", G->edges[eindex].v1, G->edges[eindex].weight);
         else if (G->edges[eindex].v2 != vname)
            printf(" %d %d", G->edges[eindex].v2, G->edges[eindex].weight);
      }
      node = node->next;
   }
   printf("\n");
   return;
}
void delete_edge(Graph *G, int index, int v1, int v2) {
   int i = 1;
   Node *node = NULL,*tmp=NULL;
   while (i<G->size) {
      node = G->vertices[i].Toincidence;
      if (node->next != NULL) {
         if (node->next->pc == index) {
            tmp = node->next;
            node->next = node->next->next;
            free(tmp);
         }
      }
      i++;
   }
   G->edges[index].edgename = -1;
   G->edges[index].v1 = -1;
   G->edges[index].v2 = -1;
   G->edges[index].weight = -1;

   return;
}
void m(Graph *G, int v1, int v2, int w) {
   int i = 0;
   if (G->size - 1 < v1 || v1 <= 0) {
      printf("-1\n");
      return;
   }
   else if (G->size - 1 < v2 || v2 <= 0) {
      printf("-1\n");
      return;
   }
  
   while (i<G->egdesize) {
      if (G->edges[i].v1 == v1 && G->edges[i].v2 == v2) {
         if (w != 0) {
            G->edges[i].weight = w;
            return;
         }
         else if (w == 0) {
            delete_edge(G, i, v1, v2);
            return;
         }
      }
      else if (G->edges[i].v1 == v2 && G->edges[i].v2 == v1) {
         if (w != 0) {
            G->edges[i].weight = w;
            return;
         }
         else if (w == 0) {
            delete_edge(G, i, v1, v2);
            return;
         }
      }
      i++;
   }
   
   if (w != 0) {
      i = 0;
      while (i < G->cur) {
         if (G->edges[i].edgename == -1)
            break;
         i++;
      }
      adeEdge(G, i, v1, v2, w);
   }
   return;
}
int main() {
   Graph graph = {NULL,NULL,0,0,0};
   construct_G(&graph, 7, 100);
   int id, v1, v2, weight;
   char ch;
   do
   {
       scanf("%c", &ch);
       switch (ch)
       {
           case 'a':
               scanf("%d", &id);
               p(&graph, id);
     break;
           case 'm':
               scanf("%d %d %d", &v1, &v2, &weight);
               m(&graph, v1, v2, weight);
               break;
           default:
               break;
       }
       getchar();
    } while (ch != 'q');

   return 0;
}
