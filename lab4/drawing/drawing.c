#include "graph-parts.c"
#include "coords.c"

void drawGraph(HDC handle, HWND hWnd, PAINTSTRUCT ps, int isDirect, double k){
    int **coords = getCoords(100);
    double **matrix = isDirect ? direct(k) : indirect(k);
    handle = BeginPaint(hWnd, &ps);
    HPEN BPen = CreatePen(PS_SOLID, 2, RGB(50, 0, 255));
    HPEN KPen = CreatePen(PS_SOLID, 1, RGB(20, 20, 5));

    SelectObject(handle, KPen);
    drawEdges(handle, coords, matrix, isDirect, k);

    SelectObject(handle, BPen);
    drawVertexes(handle, coords);
    freeCoords(coords);
}

void drawCondensationGraph(HDC handle, HWND hWnd, PAINTSTRUCT ps) {
    int **coords = getCoords(100);
    handle = BeginPaint(hWnd, &ps);
    HPEN BPen = CreatePen(PS_SOLID, 2, RGB(50, 0, 255));
    HPEN KPen = CreatePen(PS_SOLID, 1, RGB(20, 20, 5));

    SelectObject(handle, KPen);
    drawEdge(handle);

    SelectObject(handle, BPen);
    for (int i = 0; i < 2; i++) {
        int x = coords[0][i];
        int y = coords[1][i];
        char number[2];
        itoa(i + 1, number, 10);
        Ellipse(handle, x - RADIUS, y - RADIUS, x + RADIUS, y + RADIUS);
        TextOut(handle, x - DTX, y - RADIUS / 2, number, 2);
    }
}