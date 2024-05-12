#include <windows.h>

#include "../matrix/matrix.c"

#define START 100
#define DTX 5
#define RADIUS 16

void drawEdge(HDC, int**, int, int, double**, int);
void drawLoop(HDC, int**, double**, double**, int);
void drawStraight(HDC, int, int, int, int, int, int);
void drawUpper(HDC, int, int, int, int, int, int);

void drawEdges(HDC handle, int **coords, double **W, double **matrix) {
    int flag = 1;
    int counter = 0;
    drawLoop(handle, coords, matrix, W, flag);
    for (int i = 0; i < vertices; i++) {
        for (int j = counter; j < vertices; j++) {
            if((int)matrix[i][j] && i != j){
                drawEdge(handle, coords, i, j, W, flag);
            }
        }
        counter++;
    }
}

void drawEdge(HDC handle, int **coords, int i, int j, double **W, int flag) {
    int x1 = coords[0][i];
    int y1 = coords[1][i];
    int x2 = coords[0][j];
    int y2 = coords[1][j];
    if(y1 == y2 && abs(x1 - x2) > 150 && (y1 == START || y1 == 400)) {
        drawUpper(handle, x1, y1, x2, y2, (int)W[i][j], flag);
    } else {
        drawStraight(handle, x1, y1, x2, y2, (int)W[i][j], flag);
    }
}

void drawVertexes(HDC handle, int **coords) {
    for (int i = 0; i < vertices; i++) {
        int x = coords[0][i];
        int y = coords[1][i];
        char number[3];
        itoa(i + 1, number, 10);
        Ellipse(handle, x - RADIUS, y - RADIUS, x + RADIUS, y + RADIUS);
        TextOut(handle, x - DTX, y - RADIUS / 2, number, 2);
    }
}

void drawVertex(HDC handle, int num, int x, int y) {
    char number[3];
    itoa(num + 1, number, 10);
    Ellipse(handle, x - RADIUS, y - RADIUS, x + RADIUS, y + RADIUS);
    TextOut(handle, x - DTX, y - RADIUS / 2, number, 2);
}

void drawStraight(HDC handle, int x1, int y1, int x2, int y2, int weight, int flag) {
    int c = 2;
    int midx = (x1 + x2)/2;
    int midy = (y1 + y2)/2;
    int lenx = abs(x1 - x2);
    int leny = abs(y1 - y2);

    if(x1 == x2 || y1 == y2) {
        midx -= 5;
    } else if(lenx > leny) {
        if(lenx != 2*leny) {
            if(y1 < y2) {
                if(x1 < x2) {
                    midx -= 25;
                    midy -= 15;
                } else if (x1 > x2) {
                    midx += 20;
                    midy -= 15;
                }
            } else {
                midx -= 25;
                midy -= 15;
            }
        }
    } else if(lenx < leny) {
        if(x1 < x2) {
            midx += 10;
            midy += 30;
        } else if (x1 > x2) {
            midx -= 25;
            midy += 30;
        }
    } else if(lenx == leny){
        if(lenx != 150) {
            if(x1 < x2) {
                midx += 10;
                midy += 15;
            } else if (x1 > x2) {
                midx -= 25;
                midy += 15;
            }
        } else if(x1 > x2) {
            midx -= 20;
        }
    }

    if(flag) {
        char result[50];
        sprintf(result, "%d", weight);
        if(weight > 10) {
            c = 3;
        }
        TextOut(handle, midx, midy, result, c);
    }

    MoveToEx(handle, x1, y1, NULL);
    LineTo(handle, x2, y2);
}

void drawUpper(HDC handle, int x1, int y1, int x2, int y2, int weight, int flag) {
    int midx, midy;
    int c;
    int indent = 40;

    midx = (x1 + x2)/2;
    midy = (y1 + y2)/2 - indent;

    if(flag){
        char result[50];
        sprintf(result, "%d", weight);
        if(weight < 10) {
            c = 2;
        } else c = 3;
        TextOut(handle, midx - 5, midy , result, c);
    }

    MoveToEx(handle, x1, y1, NULL);
    LineTo(handle, midx, midy);
    MoveToEx(handle, midx, midy, NULL);
    LineTo(handle, x2, y2);
}

void drawLoop(HDC handle, int **coords, double **matrix, double **W, int flag) {
    for (int i = 0; i < vertices; i++) {
        if(matrix[i][i]) {
            int x = coords[0][i];
            int y = coords[1][i];
            Ellipse(handle, x, y - RADIUS*2, x + RADIUS*3, y + RADIUS*2);
            if(flag) {
                char result[50];
                sprintf(result, "%d", (int)W[i][i]);
                TextOut(handle, x + 3*RADIUS, y , result, 2);
            }
        }
    }
}