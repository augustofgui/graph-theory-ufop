#include "FordFulkerson.h"

void bubbleSort(Node *start)
{      
    int swapped, i;
    Node *ptr1;
    Node *lptr = NULL;
  
    /* Checking for empty list */
    if (start == NULL)
        return;
  
    do
    {   
        swapped = 0;
        ptr1 = start;
  
        while (ptr1->next != lptr)
        {
            if (ptr1->vertex > ptr1->next->vertex)
            { 
                swap(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
    while (swapped);
}

Node * copyNode(Node * cpy){
    Node * new = createNode(cpy->vertex, cpy->flowCap, cpy->isRes);
    new->next = cpy->next;

    return new;
}

/* function to swap data of two nodes a and b*/
void swap(Node *a, Node *b)
{       
    int vertex, flow;
    bool isRes;

    vertex = a->vertex;
    flow = a->flowCap;
    isRes = a->isRes;
   
    a->vertex = b->vertex;
    a->flowCap = b->flowCap;
    a->isRes = b->isRes;

    b->vertex = vertex;
    b->flowCap = flow;
    b->isRes = isRes;
}

Node *createNode(int vId, int flowCap, bool isRes)
{
    Node *newNode = malloc(sizeof(Node));
    newNode->vertex = vId;
    newNode->flowCap = flowCap;
    newNode->next = NULL;
    newNode->isRes = isRes;

    return newNode;
}

Graph *createGraph(int numVertices)
{
    Graph *newGraph = malloc(sizeof(Graph));
    newGraph->numVertices = numVertices;

    newGraph->marked = calloc(numVertices, sizeof(bool));
    newGraph->anwserList = NULL;

    newGraph->adjLists = calloc(numVertices, sizeof(Node *));
    newGraph->tailNodes = calloc(numVertices, sizeof(Node *));

    int i;
    for (i = 0; i < numVertices; i++)
    {
        newGraph->marked[i] = false;
        newGraph->adjLists[i] = NULL;
        newGraph->tailNodes[i] = NULL;
    }

    return newGraph;
}

Graph *createCopyGraph(Graph *sourceGraph)
{
    Graph *graphCopy = createGraph(sourceGraph->numVertices);
    Node *temp;

    int i;
    for (i = 0; i < graphCopy->numVertices; i++)
    {
        graphCopy->marked[i] = sourceGraph->marked[i];

        temp = sourceGraph->adjLists[i];
        while (temp != NULL)
        {
            addEdge(graphCopy, i, temp->vertex, temp->flowCap, false);
            addEdge(graphCopy, temp->vertex, i, 0, true);
            temp = temp->next;
        }
    }

    return graphCopy;
}

void addEdge(Graph *graph, int s, int d, int mf, bool isRes)
{
    Node *newNode = createNode(d, mf, isRes);

    if (graph->adjLists[s] == NULL)
    {
        graph->adjLists[s] = newNode;
        graph->tailNodes[s] = newNode;

        return;
    }

    if(d < graph->adjLists[s]->vertex) {
        newNode->next = graph->adjLists[s];

        graph->adjLists[s] = newNode;

        return;
    }

    if(d == graph->adjLists[s]->vertex || newNode->flowCap < graph->adjLists[s]->flowCap) {
        newNode->next = graph->adjLists[s];

        graph->adjLists[s] = newNode;

        return;
    }

    graph->tailNodes[s]->next = newNode;
    graph->tailNodes[s] = newNode;
}

void addAnwser(Graph *graph, int s, int mf, bool isRes)
{
    Node *newNode = createNode(s, mf, isRes);

    newNode->next = graph->anwserList;
    graph->anwserList = newNode;

    return;
}

void clearAnwser(Graph *graph) {
    Node *temp = graph->anwserList;
    Node *ant = graph->anwserList;;

    while (temp)
    {   
        temp = temp->next;
        free(ant);   
        ant = temp;
    }

    free(ant);

    graph->anwserList = NULL;
}

int fordFulkerson(Graph *graph, int source, int sink)
{
    int i, n = graph->numVertices;

    Graph *residualGraph = createCopyGraph(graph);
    for (i = 0; i < n; i++)
        bubbleSort(residualGraph->adjLists[i]);

    int maxFlow;
    for (maxFlow = 0;;)
    {
        for (i = 0; i < n; i++)
            residualGraph->marked[i] = false;

        printGraph(residualGraph);

        int flow = dfs(residualGraph, source, sink, INT_MAX);

        printAnwser(residualGraph);
        clearAnwser(residualGraph);

        maxFlow += flow;
        if (flow == 0)
            return maxFlow;
    }
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
            printf("%d:%d:%c -> ", temp->vertex + 1, temp->flowCap, (graph->marked[v]) ? 't' : 'f');
            temp = temp->next;
        }
        printf("\n");
    }

    printf("\n");
}

void printAnwser(Graph *graph)
{
    Node *temp = graph->anwserList;
    if(temp == NULL)
        return;
    while (temp)
    {   
        printf("[%d, %c, %d] ", temp->vertex+1, (temp->isRes) ? '-' : '+', temp->flowCap);
        temp = temp->next;
    }
    printf("\n");
}

int dfs(Graph *graph, int vertex, int sink, int flow)
{
    if (vertex == sink)
        return flow;

    int oldFlow = flow;

    Node *nodeFlows = graph->adjLists[vertex];
    graph->marked[vertex] = true;
    
    while (nodeFlows != NULL)
    {
        if (graph->marked[nodeFlows->vertex] != true && nodeFlows->flowCap > 0)
        {   
            if (nodeFlows->flowCap < flow) {
                oldFlow = flow;
                flow = nodeFlows->flowCap;
            }    

            Node *temp = graph->adjLists[nodeFlows->vertex];

            int dfsFlow = dfs(graph, nodeFlows->vertex, sink, flow);

            if (dfsFlow > 0)
            {
                Node *residual = graph->adjLists[nodeFlows->vertex];
                while (residual->vertex != vertex)
                {
                    residual = residual->next;
                }
                addAnwser(graph, vertex, flow, nodeFlows->isRes);
                
                nodeFlows->flowCap -= dfsFlow;
                residual->flowCap += dfsFlow;

                return dfsFlow;
            }
        }
        flow = oldFlow;
        nodeFlows = nodeFlows->next;
    }

    return 0;
}