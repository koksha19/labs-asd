#include <stdlib.h>

#define vertices 10
#define COORDS 2

const int firstSideVertices = vertices / 2.5;
const int secondSideVertices = vertices / 1.6;
const int thirdSideVertices = vertices / 1.1;

int **getCoords(int first) {
    int **coords;
    coords = malloc(COORDS * sizeof(size_t*)); //allocating memory for arrays of x and y coordinates

    for (int i = 0; i < 2; i++) {
        coords[i] = malloc(vertices * sizeof(int)); //allocating memory for every coordinate
    }

    int start = first;
    for (int i = 0; i < firstSideVertices; i++) { //getting coordinates for the first of the rectangle
        coords[0][i] = start;
        coords[1][i] = first;
        start += 150;
    }
    for (int i = firstSideVertices; i < secondSideVertices; i++) { //getting coordinates for the second side;
        coords[0][i] = coords[0][i - 1];
        coords[1][i] = coords[1][i - 1] + 150;
    }
    for (int i = secondSideVertices; i < thirdSideVertices; i++) { //getting coordinates for the third side
        coords[0][i] = coords[0][i - 1] - 150;
        coords[1][i] = coords[1][i - 1];
    }
    for (int i = thirdSideVertices; i < vertices; i++) { //getting coordinates for the last side
        coords[0][i] = coords[0][i - 1];
        coords[1][i] = coords[1][i - 1] - 150;
    }
    return coords;
}

void freeCoords(int **coords) {
    for (int i = 0; i < 2; i++) free(coords[i]);
    free(coords);
}