#include "graph-parts.c"
#include "coords.c"
#include "../matrix/matrixToList.c"

void drawGraph(HDC handle){
    int **coords = getCoords(100);
    HPEN BPen = CreatePen(PS_SOLID, 2, RGB(50, 0, 255));
    HPEN KPen = CreatePen(PS_SOLID, 1, RGB(20, 20, 5));

    SelectObject(handle, KPen);
    drawEdges(handle, coords, getW(), indirect());
    getSum();

    SelectObject(handle, BPen);
    drawVertexes(handle, coords);
    freeCoords(coords);
    freem(indirect());
}

void drawComponents(HDC handle, int step) {
    int **coords = getCoords(100);

    int counter = 1;
    double **adjMatrix = indirect();
    double **weightMatrix = getW();
    struct Graph* graph = newGraph();
    for (int i = 0; i < vertices; i++) {
        for (int j = counter; j < vertices; j++) {
            if (adjMatrix[i][j]) {
                addEdge(graph, i, j, (int)weightMatrix[i][j]);
            }
        }
        counter++;
    }

    double **mstMatrix = listToMatrix(PrimMST(graph));
    double **order = orderMatrix();

    int from = vertexFrom(order, step);
    int to = VertexTo(mstMatrix, from);

    HPEN OPen = CreatePen(PS_SOLID, 2, RGB(255, 120, 0));

    SelectObject(handle, OPen);
    if (step < vertices) {
        drawEdge(handle, coords, from, to, weightMatrix, 0);
        drawVertex(handle, from, coords[0][from], coords[1][from]);
        drawVertex(handle, to, coords[0][to], coords[1][to]);
    }

    freeCoords(coords);
    freem(adjMatrix);
    freem(weightMatrix);
    freem(mstMatrix);
}
