#include "DFS.h"

Node *createNode(int vId)
{
    Node *newNode = malloc(sizeof(Node));
    newNode->vertex = vId;
    newNode->next = NULL;
    return newNode;
}

Graph *createGraph(int numVertices, int isDir)
{
    Graph *newGraph = malloc(sizeof(Graph));
    newGraph->numVertices = numVertices;
    newGraph->isDir = (isDir == 0) ? false : true;

    newGraph->marked = calloc(numVertices, sizeof(bool));

    newGraph->adjLists = malloc(numVertices * sizeof(Node *));

    int i;
    for (i = 0; i < numVertices; i++)
        newGraph->adjLists[i] = NULL;

    return newGraph;
}

void addEdge(Graph *graph, int s, int d, int peso)
{
    // Add edge from s to d
    Node *newNode = createNode(d);


    if(graph->isDir == false) {

        Node *secondNode = createNode(s);

        if (graph->adjLists[d] == NULL)
        {
            secondNode->next = graph->adjLists[d];
            graph->adjLists[d] = secondNode;
        } else {
            Node *temp2 = graph->adjLists[d];
            while (temp2->next != NULL)
                temp2 = temp2->next;

            temp2->next = secondNode;
        }
    }

    if (graph->adjLists[s] == NULL)
    {
        newNode->next = graph->adjLists[s];
        graph->adjLists[s] = newNode;

        return;
    }

    Node *temp = graph->adjLists[s];
    while (temp->next != NULL)
        temp = temp->next;

    temp->next = newNode;
}

void printGraph(Graph *graph)
{
    int v;

    for (v = 0; v < graph->numVertices; v++)
    {
        Node *temp = graph->adjLists[v];
        printf("\n Vertex %d\n: ", v + 1);
        while (temp)
        {
            printf("%d -> ", temp->vertex + 1);
            temp = temp->next;
        }
        printf("\n");
    }

    printf("\n");
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
