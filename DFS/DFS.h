#ifndef DFS_H
#define DFS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    int vertex;
    struct node* next;
} Node;

typedef struct graph {
    int numVertices;
    bool isDir;
    bool * marked;
    Node** adjLists;
} Graph;

Node* createNode(int vId);

Graph *createGraph(int numVertices, int isDir);

void addEdge(Graph *graph, int s, int d, int peso);

void printGraph(Graph *graph);

void dfs(Graph *graph, int vertex);

#endif // DFS_H