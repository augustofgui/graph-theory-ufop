#include "kahn.h"

int main()
{      
    int numVert;
    int numArcs;
    int initialVert = 0;

    int i, s, d, mf;

    scanf("%d %d", &numVert, &numArcs);

    Graph* graph = createGraph(numVert);

    for( i=0; i < numArcs; i++) {
        scanf("%d %d", &s, &d);
        addEdge(graph, s-1, d-1);
    }

    kahnSort(graph);
    
    return 0;
}