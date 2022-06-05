#ifndef FORD_FULKERSON_H
#define FORD_FULKERSON_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

typedef struct node
{
    int vertex;
    int flowCap;
    bool isRes;
    struct node *next;
} Node;

typedef struct graph
{
    int numVertices;
    bool *marked;
    Node **adjLists;
    Node *anwserList;
    Node **tailNodes;
} Graph;

void bubbleSort(Node *start);

Node * copyNode(Node * cpy);

void swap(Node *a, Node *b);

Node *createNode(int vId, int flowCap, bool isRes);

Graph *createGraph(int numVertices);

Graph *createCopyGraph(Graph * sourceGraph);

void addEdge(Graph *graph, int s, int d, int mf, bool isRes);

void addAnwser(Graph *graph, int s, int mf, bool isRes);

void clearAnwser(Graph *graph);

void printGraph(Graph *graph);

void printAnwser(Graph *graph);

int fordFulkerson(Graph *graph, int source, int sink);

int dfs(Graph *graph, int vertex, int sink, int flow);

#endif // FORD_FULKERSON_H