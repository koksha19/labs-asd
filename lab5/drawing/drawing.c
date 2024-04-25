#include "graph-parts.c"
#include "coords.c"
#include "../matrix/bfsAndDfs.c"

int prev = -1;

void drawGraph(HDC handle, int isDirect){
    int **coords = getCoords(100);
    double **matrix = direct();
    HPEN BPen = CreatePen(PS_SOLID, 2, RGB(50, 0, 255));
    HPEN KPen = CreatePen(PS_SOLID, 1, RGB(20, 20, 5));

    SelectObject(handle, KPen);
    drawEdges(handle, coords, isDirect, matrix);

    SelectObject(handle, BPen);
    for (int i = 0; i < vertices; i++) {
        int x = coords[0][i];
        int y = coords[1][i];
        drawVertex(handle, i, x, y);
    }
    freeCoords(coords);

}

void drawTraverseComponent(HDC handle, int isBfs, int *step) {
    int **coords = getCoords(100);
    matrices traverseMatrices = isBfs ? bfs(direct()) : dfs(direct());

    double **treeMatrix = traverseMatrices.treeMatrix;
    double **orderMatrix = traverseMatrices.orderMatrix;
    int current = numberVertex(*step, orderMatrix);
    int edge = numberVertex(current, treeMatrix);

    HPEN OPen = CreatePen(PS_SOLID, 2, RGB(255, 120, 0));
    HPEN GPen = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));

    SelectObject(handle, OPen);
    if (*step != vertices && prev != -1) {
        drawEdge(handle, coords, edge, current, 1, treeMatrix);
        drawVertex(handle, edge, coords[0][edge], coords[1][edge]);
    }

    drawVertex(handle, prev, coords[0][prev], coords[1][prev]);

    SelectObject(handle, GPen);
    if (*step != vertices) {
        drawVertex(handle, current, coords[0][current], coords[1][current]);
    }

    prev = current;

    freeCoords(coords);
    freem(direct());
    freem(treeMatrix);
    freem(orderMatrix);
}
