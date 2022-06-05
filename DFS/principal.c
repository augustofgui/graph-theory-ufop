#include "DFS.h"

int main()
{      
    int numVert;
    int numArcs;
    int isDir;
    int initialVert;

    int i, s, d, w;

    scanf("%d %d %d %d", &numVert, &numArcs, &isDir, &initialVert);

    Graph* graph = createGraph(numVert, isDir);

    for( i=0; i < numArcs; i++) {
        scanf("%d %d %d", &s, &d, &w);
        addEdge(graph, s-1, d-1, w);
    }

    printGraph(graph);
    
    dfs(graph, --initialVert);
    
    return 0;
}