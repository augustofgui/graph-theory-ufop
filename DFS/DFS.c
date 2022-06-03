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

void doDFS(Graph *graph, int vertex)
{
    bool *marked = calloc(graph->numVertices, sizeof(bool));

    dfs(graph, vertex - 1, marked);
}

void dfs(Graph *graph, int vertex, bool *marked)
{
    int v;
    if (marked[vertex] == true)
        return;

    Node *temp = graph->adjLists[vertex];
    visit(vertex, marked);

    while (temp != NULL)
    {
        // printf("%d:%d:%s\n", v+1, temp->vertex+1, marked[temp->vertex] ? "true" : "false");
        if (marked[temp->vertex] != true)
            dfs(graph, temp->vertex, marked);

        temp = temp->next;
    }
}

void visit(int vId, bool *marked)
{
    printf("%d\n", vId + 1);
    marked[vId] = true;
}