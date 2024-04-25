#include <windows.h>
#include <math.h>

#include "../matrix/matrix.c"
#define START 100
#define DTX 5
#define RADIUS 16

void drawArrow(HDC, double, int, int);
void drawLoop(HDC, int**, double**, int);
void drawMultiple(HDC, int, int, int, int);
void drawUpper(HDC, int, int, int, int, int);
void drawStraight(HDC, int, int, int, int, int);
void drawEdge(HDC, int**, int, int, int, double**);

void drawEdges(HDC handle, int **coords, int isDirect, double **matrix) {
    //double **matrix = isDirect ? direct() : indirect();
    drawLoop(handle, coords, matrix, isDirect);
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            if(matrix[i][j] && i != j){
                drawEdge(handle, coords, i, j, isDirect, matrix);
            }
        }
    }
}

void drawEdge(HDC handle, int **coords, int i, int j, int isDirect, double **matrix) {
    //double **matrix = isDirect ? direct() : indirect();
    int x1 = coords[0][i];
    int y1 = coords[1][i];
    int x2 = coords[0][j];
    int y2 = coords[1][j];
    if(matrix[j][i] && isDirect){
        drawMultiple(handle, x1, y1, x2, y2);
    } else if(y1 == y2 && abs(x1 - x2) > 150 && (y1 == START || y1 == START * 4)) {
        drawUpper(handle, x1, y1, x2, y2, isDirect);
    } else {
        drawStraight(handle, x1, y1, x2, y2, isDirect);
    }
}

void drawVertices(HDC handle, int **coords) {
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

void drawArrow(HDC handle, double fi, int px, int py) {
    fi = 3.1416 * (180.0 - fi) / 180.0;
    int lx, ly, rx, ry;
    lx = px + 15 * cos(fi + 0.25);
    rx = px + 15 * cos(fi - 0.25);
    ly = py + 15 * sin(fi + 0.25);
    ry = py + 15 * sin(fi - 0.25);
    MoveToEx(handle, lx, ly, NULL);
    LineTo(handle, px, py);
    LineTo(handle, rx, ry);
}

void drawStraight(HDC handle, int x1, int y1, int x2, int y2, int isDirect) {
    double angle, tg;
    int xx, yy;
    int lenx = abs(x1 - x2);
    int leny = abs(y1 - y2);

    if(y1 == y2) {
        if (x1 > x2) {
            xx = x2 + RADIUS;
            angle = 180;
        } else {
            xx = x2 - RADIUS;
            angle = 0;
        }
        if (isDirect) drawArrow(handle, angle, xx, y2);
    } else if (x2 > x1) {
        if (lenx > leny) {
            tg = lenx / leny;
            angle = 90 - atan(tg) * 180 / 3.1416;
            yy = RADIUS / sqrt(1 + tg * tg);
            xx = yy * tg;
        } else {
            tg = leny / lenx;
            angle = atan(tg) * 180 / 3.1416;
            xx = RADIUS / sqrt(1 + tg * tg);
            yy = xx * tg;
        }

        angle = y1 > y2 ? angle : -angle;
        yy = y1 > y2 ? yy : -yy;

        if (isDirect) drawArrow(handle, angle, x2 - xx, y2 + yy);
    } else if (x1 > x2) {
        if (lenx > leny) {
            tg = lenx / leny;
            angle = 90 - atan(tg) * 180 / 3.1416;
            yy = RADIUS / sqrt(1 + tg * tg);
            xx = yy * tg;
            if (isDirect && x2 == 100 && y2 == 100) drawArrow(handle, 145, START + 13, START + 9);
            if (isDirect && x2 == 100 && y2 == 400) drawArrow(handle, -145, START + 13, 4*START - 9);
        } else {
            tg = leny / lenx;
            angle = atan(tg) * 180 / 3.1416;
            xx = RADIUS / sqrt(1 + tg * tg);
            yy = xx * tg;
        }

        angle = y1 > y2 ? -angle : angle;
        yy = y2 > y1 ? -yy : yy;

        if (isDirect && (x2 + y2 != 500)) drawArrow(handle, angle + 180, x2 + xx, y2 + yy);
    } else if(x1 == x2){
        if(y1 > y2) {
            yy = y2 + RADIUS;
            angle = 90;
        } else {
            yy = y2 - RADIUS;
            angle = - 90;
        }
        if(isDirect) drawArrow(handle, angle, x2, yy);
    }
    MoveToEx(handle, x1, y1, NULL);
    LineTo(handle, x2, y2);
}

void drawMultiple(HDC handle, int x1, int y1, int x2, int y2) {
    int midx = (x1 + x2)/2;
    int midy = (y1 + y2)/2;
    const int indent = 12;
    double lenx, leny, tg, angle;
    int xx, yy;

    if(x1 == x2) {
        midx = y2 > y1 ? midx + indent : midx - indent;
        lenx = abs(midx - x2);
        leny = abs(midy - y2);

        tg = lenx / leny;
        angle = atan(tg) * 180 / 3.1416;
        angle = y2 > y1 ? -90 + angle : 90 + angle;

        yy = RADIUS / sqrt(1 + tg * tg);
        xx = yy * tg;

        xx = y2 > y1 ? -xx : xx;
        yy = y2 > y1 ? -yy : yy;

        drawArrow(handle, angle, x2 + xx, y2 + yy);
    } else if(y1 == y2) {
        midy = x2 > x1 ? midy - indent : midy + indent;
        lenx = abs(midx - x2);
        leny = abs(midy - y2);

        tg = leny / lenx;
        angle = atan(tg) * 180 / 3.1416;
        angle = x2 > x1 ? -angle : 180 - angle;

        xx = RADIUS / sqrt(1 + tg * tg);
        yy = xx * tg;

        xx = x2 > x1 ? -xx : xx;
        yy = x2 > x1 ? -yy : yy;

        drawArrow(handle, angle, x2 + xx, y2 + yy);
    } else if(x1 < x2){
        midx = y1 < y2 ? midx + indent : midx - indent;
        midy = midy - indent;
        lenx = abs(midx - x2);
        leny = abs(midy - y2);

        tg = leny / lenx;
        angle = atan(tg) * 180 / 3.1416;
        xx = RADIUS / sqrt(1 + tg * tg);
        yy = xx * tg;

        angle = y1 < y2 ? -angle : angle + 5;
        yy = y1 < y2 ? -yy : yy;

        drawArrow(handle, angle, x2 - xx, y2 + yy);
    } else if(x1 > x2) {
        midx = y1 < y2 ? midx + indent : midx - indent;
        midy = midy + indent;
        lenx = abs(midx - x2);
        leny = abs(midy - y2);

        if(y1 > y2) {
            tg = lenx / leny;
            angle = 90 + atan(tg) * 180 / 3.1416;
            yy = RADIUS / sqrt(1 + tg * tg);
            xx = yy * tg;
        } else {
            tg = leny / lenx;
            angle = 180 + atan(tg) * 180 / 3.1416;
            xx = RADIUS / sqrt(1 + tg * tg);
            yy = xx * tg;
        }
        yy = y1 > y2 ? yy : -yy;
        drawArrow(handle, angle, x2 + xx, y2 + yy);
    }
    MoveToEx(handle, x1, y1, NULL);
    LineTo(handle, midx, midy);
    MoveToEx(handle, midx, midy, NULL);
    LineTo(handle, x2, y2);
}

void drawUpper(HDC handle, int x1, int y1, int x2, int y2, int isDirect) {
    int midx, midy, xx, yy;
    double lenx, leny, tg, angle;
    int indent = 40;

    midx = (x1 + x2)/2;
    midy = (y1 + y2)/2 - indent;
    lenx = abs(midx - x2);
    leny = abs(midy - y2);

    tg = leny/lenx;
    angle = -atan(tg) * 180 / 3.1416;
    xx = RADIUS * cos(angle);
    yy = xx * tg;

    xx = x2 > x1 ? xx : -xx;
    yy = x2 > x1 ? yy : -yy;

    if (isDirect) drawArrow(handle, angle, x2 + xx, y2 + yy);
    MoveToEx(handle, x1, y1, NULL);
    LineTo(handle, midx, midy);
    MoveToEx(handle, midx, midy, NULL);
    LineTo(handle, x2, y2);
}

void drawLoop(HDC handle, int **coords, double **matrix, int isDirect) {
    for (int i = 0; i < vertices; i++) {
        if(matrix[i][i]) {
            int x = coords[0][i];
            int y = coords[1][i];
            Ellipse(handle, x, y - RADIUS*2, x + RADIUS*3, y + RADIUS*2);
            if (isDirect) drawArrow(handle, 115, x + 0.75* DTX, y + 2.5*DTX);
        }
    }
}