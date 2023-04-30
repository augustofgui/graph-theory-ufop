#include "kahn.h"

Queue *createQueue(unsigned capacity)
{
    Queue *queue = malloc(sizeof(Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;

    queue->rear = capacity - 1;
    queue->array = malloc(queue->capacity * sizeof(int));

    return queue;
}

int isFull(Queue *queue)
{
    return (queue->size == queue->capacity);
}

int isEmpty(Queue *queue)
{
    return (queue->size == 0);
}

void enqueue(Queue *queue, int item)
{
    if (isFull(queue))
        return;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size = queue->size + 1;
}

int dequeue(Queue *queue)
{
    if (isEmpty(queue))
        return INT_MIN;
    int item = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size = queue->size - 1;
    return item;
}

// Function to get front of queue
int front(Queue *queue)
{
    if (isEmpty(queue))
        return INT_MIN;
    return queue->array[queue->front];
}

// Function to get rear of queue
int rear(Queue *queue)
{
    if (isEmpty(queue))
        return INT_MIN;
    return queue->array[queue->rear];
}

Node *createNode(int value)
{
    Node *newNode = malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = NULL;

    return newNode;
}

Graph *createGraph(int numVertices)
{
    Graph *newGraph = malloc(sizeof(Graph));
    newGraph->numVertices = numVertices;

    newGraph->marked = calloc(numVertices, sizeof(bool));

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

void addEdgeArray(Node **list, int value)
{
    Node *newNode = createNode(value);

    if ((*list) == NULL)
    {
        (*list) = newNode;

        return;
    }

    Node *temp = (*list);
    while (temp->next != NULL)
        temp = temp->next;

    temp->next = newNode;
}

void addEdge(Graph *graph, int s, int d)
{
    Node *newNode = createNode(d);

    if (graph->adjLists[s] == NULL)
    {
        graph->adjLists[s] = newNode;
        graph->tailNodes[s] = newNode;

        return;
    }

    if (d < graph->adjLists[s]->value)
    {
        newNode->next = graph->adjLists[s];

        graph->adjLists[s] = newNode;

        return;
    }

    graph->tailNodes[s]->next = newNode;
    graph->tailNodes[s] = newNode;
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
            printf("%d:%c -> ", temp->value + 1, (graph->marked[v]) ? 't' : 'f');
            temp = temp->next;
        }
        printf("\n");
    }

    printf("\n");
}

void kahnSort(Graph *graph)
{
    int i;
    int n = graph->numVertices;
    int *inDegree = calloc(n, sizeof(int));

    for (i = 0; i < n; i++)
        inDegree[i] = 0;

    for (i = 0; i < n; i++)
    {   
        Node *temp = graph->adjLists[i];

        while (temp != NULL)
        {
            inDegree[temp->value]++;
            temp = temp->next;
        }
    }

    Queue *queue = createQueue(n);
    for (i = 0; i < n; i++)
        if (inDegree[i] == 0)
            enqueue(queue, i);

    int cnt = 0;

    Node *order = NULL;
    while (!isEmpty(queue))
    {   
        int u = front(queue);
        dequeue(queue);

        addEdgeArray(&order, u);
        
        Node *temp = graph->adjLists[u];

        while (temp != NULL)
        {   
            inDegree[temp->value] = inDegree[temp->value]-1;
            if (inDegree[temp->value] == 0)
                enqueue(queue, temp->value);

            temp = temp->next;
        }

        cnt++;
    }

    if (cnt != n)
    {
        printf("Erro: ciclo detectado\n");
        return;
    }

    printf("L = {");

    Node *temp = order;
    while (temp->next != NULL)
    {   
        printf("%d, ", temp->value+1);
        temp = temp->next;
    }

    printf("%d}\n", temp->value+1);
    return;
}