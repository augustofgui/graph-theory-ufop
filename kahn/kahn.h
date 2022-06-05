#ifndef KAHN_H
#define KAHN_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

typedef struct node
{
    int value;
    struct node *next;
} Node;

typedef struct graph
{
    int numVertices;
    bool *marked;
    Node **adjLists;
    Node **tailNodes;
} Graph;

typedef struct queue {
    int front, rear, size;
    unsigned capacity;
    int* array;
} Queue;

Queue *createQueue(unsigned capacity);

int isFull(Queue* queue);

int isEmpty(Queue* queue);

void enqueue(Queue* queue, int item);
 
int dequeue(Queue* queue);

int front(Queue* queue);

int rear(Queue* queue);

void bubbleSort(Node *start);

void swap(Node *a, Node *b);

Node *createNode(int vertex);

Graph *createGraph(int numVertices);

Graph *createCopyGraph(Graph * sourceGraph);

void addEdge(Graph *graph, int s, int d);

void addEdgeArray(Node **list, int value);

void printGraph(Graph *graph);

void kahnSort(Graph *graph);

#endif // KAHN_H