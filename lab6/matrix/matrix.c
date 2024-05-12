#ifndef MATRIX
#define MATRIX

#include <stdlib.h>
#include <stdio.h>

#define SEED 3203
#define k 0.935 // 1 - 0*0.01 - 3*0.005 - 0.05
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

double **getC(){
    double **matrix = indirect();
    double **B = randm();
    double **C = B;
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            C[i][j] = ceil(C[i][j] * 100 * matrix[i][j]);
        }
    }
    return C;
}

double **getD() {
    double **matrix = getC();
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            if(matrix[i][j] != 0) {
                matrix[i][j] = 1;
            }
        }
    }
    return matrix;
}

double **getH() {
    double **H;
    H = malloc(vertices * sizeof(size_t*));
    double **matrix = getD();
    for (int i = 0; i < vertices; i++) {
        H[i] = malloc(vertices * sizeof (double));
        for (int j = 0; j < vertices; j++) {
            if(matrix[i][j] != matrix[j][i]) {
                H[i][j] = 1;
            } else {
                H[i][j] = 0;
            }
        }
    }
    return H;
}

double **getTr() {
    double **Tr;
    int counter = 1;
    Tr = malloc(vertices * sizeof(size_t*));
    for (int i = 0; i < vertices; i++) {
        Tr[i] = malloc(vertices * sizeof (double));
        for (int j = counter; j < vertices; j++) {
            Tr[i][j] = 1;
        }
        counter++;
    }
    return Tr;
}

double **getW() {
    double **C = getC();
    double **D = getD();
    double **H = getH();
    double **Tr = getTr();
    double **W;
    int counter = 1;

    W = malloc(vertices * sizeof(size_t*));
    for (int i = 0; i < vertices; i++) {
        W[i] = malloc(vertices * sizeof (double));
    }

    for (int i = 0; i < vertices; i++) {
        for (int j = counter; j < vertices; j++) {
            W[i][j] = (D[i][j] + H[i][j] * Tr[i][j]) * C[i][j];
            W[j][i] = W[i][j];
        }
        counter++;
    }
    return W;
}

int vertexFrom(double **matrix, int step) {
    for (int i = 0; i < vertices; i++) {
        if (matrix[i][step]) return i;
    }
    return -1;
}
int VertexTo(double **matrix, int step) {
    for (int i = 0; i < vertices; i++) {
        if (matrix[step][i]) return i;
    }
    return -1;
}

void freem(double **matrix) {
    for (int i = 0; i < vertices; i++) free(matrix[i]);
    free(matrix);
}

void printMatrix(double **matrix) {
    for (int i = 0; i < vertices; i++) {
        printf("[ ");
        for (int j = 0; j < vertices; j++) {
            printf("%d   ", (int)matrix[i][j]);
        }
        printf("]");
        printf("\n");
    }
    printf("\n");
    freem(matrix);
}

#endif