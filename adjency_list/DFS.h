#ifndef DFS_H
#define DFS_H

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int vertex;
    struct node* next;
} Node;

typedef struct graph {
    int numVertices;
    Node** adjLists;
} Graph;

Node* createNode(int vId);

Graph* createGraph(int numVertices);

void addEdge(Graph *graph, int s, int d);

void printNodeAdjacency(Node *node);

void printGraph(Graph *graph);

#endif // DFS_H