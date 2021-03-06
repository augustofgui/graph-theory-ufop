#include "FordFulkerson.h"

int main()
{      
    int numVert;
    int numArcs;
    int initialVert = 0;

    int i, s, d, mf;

    scanf("%d %d", &numVert, &numArcs);

    Graph* graph = createGraph(numVert);

    for( i=0; i < numArcs; i++) {
        scanf("%d %d %d", &s, &d, &mf);
        addEdge(graph, s-1, d-1, mf, false);
    }
    
    fordFulkerson(graph, 0, numVert-1);
    
    return 0;
}