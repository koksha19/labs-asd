#ifndef MATRIX
#define MATRIX

#include <stdlib.h>
#include <stdio.h>

#define SEED 3203
#define k 0.835 // 1 - 0*0.01 - 3*0.005 - 0.15
#define vertices 10

double **randm(){
    srand(SEED);
    double **T;
    T = malloc(vertices * sizeof(size_t*));
    for(int i = 0; i < vertices; i++){
        T[i] = malloc(vertices * sizeof (double));
        for (int j = 0; j < vertices; ++j) {
            int num = rand();
            T[i][j] = (double)num/RAND_MAX*2;
        }
    }
    return T;
}

double **mulmr(double **matrix) {
    for (int i = 0; i < vertices; ++i) {
        for (int j = 0; j < vertices; ++j) {
            if(matrix[i][j]*k > 1){
                matrix[i][j] = 1;
            } else {
                matrix[i][j] = 0;
            }
        }
    }
    return matrix;
}

double **direct() {
    double **temp = randm();
    double **matrix = mulmr(temp);
    return matrix;
}

double **indirect() {
    double **matrix = direct();
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            if (matrix[i][j]) matrix[j][i] = 1;
        }
    }
    return matrix;
}

void printMatrix(double **matrix) {
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            printf("%d   ", (int)matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int numberVertex(int step, double **matrix) {
    for (int i = 0; i < vertices; i++) {
        if (matrix[i][step]) return i;
    }
    return -1;
}

void freem(double **matrix) {
    for (int i = 0; i < vertices; i++) free(matrix[i]);
    free(matrix);
}
#endif