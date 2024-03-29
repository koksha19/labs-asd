#include "graph-parts.c"
#include "coords.c"

void drawGraph(HDC handle, HWND hWnd, PAINTSTRUCT ps, int isDirect){
    int **coords = getCoords(100);
    handle = BeginPaint(hWnd, &ps);
    HPEN BPen = CreatePen(PS_SOLID, 2, RGB(50, 0, 255));
    HPEN KPen = CreatePen(PS_SOLID, 1, RGB(20, 20, 5));

    SelectObject(handle, KPen);
    drawEdges(handle, coords, isDirect);

    SelectObject(handle, BPen);
    drawVertexes(handle, coords);
    freeCoords(coords);
}