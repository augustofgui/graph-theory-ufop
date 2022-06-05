#include "DFS.h"

Node *createNode(int vId)
{
    Node *newNode = malloc(sizeof(Node));
    newNode->vertex = vId;
    newNode->next = NULL;
    return newNode;
}

Graph *createGraph(int numVertices)
{
    Graph *newGraph = malloc(sizeof(Graph));
    newGraph->numVertices = numVertices;

    newGraph->adjLists = malloc(numVertices * sizeof(Node *));

    int i;
    for (i = 0; i < numVertices; i++)
        newGraph->adjLists[i] = NULL;

    return newGraph;
}

void addEdge(Graph *graph, int s, int d)
{
    // Add edge from s to d
    Node *newNode = createNode(d);
    newNode->next = graph->adjLists[s];
    graph->adjLists[s] = newNode;

    // Add edge from d to s
    newNode = createNode(s);
    newNode->next = graph->adjLists[d];
    graph->adjLists[d] = newNode;
}

void printNodeAdjacency(Node *node)
{
    printf("\n Vertex %d\n: ", node->vertex);
    while (node != NULL)
    {
        printf("%d -> ", node->vertex);
        node = node->next;
    }
    printf("\n");
}

void printGraph(Graph *graph)
{
    int v;

    for (v = 0; v < graph->numVertices; v++)
    {
        Node *temp = graph->adjLists[v];
        printNodeAdjacency(temp);
    }
}

void dfs(Graph *graph, int vertex)
{
    int v;
    if (graph->marked[vertex] == true)
        return;

    Node *temp = graph->adjLists[vertex];
    
    printf("%d\n", vertex + 1);
    
    graph->marked[vertex] = true;

    while (temp != NULL)
    {
        // printf("%d:%d:%s\n", v+1, temp->vertex+1, marked[temp->vertex] ? "true" : "false");
        if (graph->marked[temp->vertex] != true)
            dfs(graph, temp->vertex);

        temp = temp->next;
    }
}