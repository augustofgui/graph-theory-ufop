#ifndef FORD_FULKERSON_H
#define FORD_FULKERSON_H

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
    Node** adjLists;
} Graph;

Node* createNode(int vId);

Graph *createGraph(int numVertices, int isDir);

void addEdge(Graph *graph, int s, int d, int peso);

void printGraph(Graph *graph);

void doDFS(Graph *graph, int vertex);

void dfs(Graph *graph, int vertex, bool * marked);

void visit(int vId, bool * marked);

#endif // FORD_FULKERSON_H