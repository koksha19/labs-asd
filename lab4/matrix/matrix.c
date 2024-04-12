#ifndef MATRIX
#define MATRIX

#include <stdlib.h>
#include <stdio.h>

#define SEED 3203
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

double **mulmr(double **matrix, double k) {
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

double **direct(double k) {
    double **temp = randm();
    double **matrix = mulmr(temp, k);
    return matrix;
}

double **indirect(double k) {
    double **matrix = direct(k);
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            if (matrix[i][j]) matrix[j][i] = 1;
        }
    }
    return matrix;
}

void printMatrix(double **matrix, int v) {
    for (int i = 0; i < v; i++) {
        for (int j = 0; j < v; j++) {
            printf("%d   ", (int)matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int *getDegrees(double **matrix, int out) {
    int *degrees;
    degrees = malloc(vertices * sizeof(int));
    for (int i = 0; i < vertices; i++) {
        int num = 0;
        for (int j = 0; j < vertices; j++) {
            if(out) {
                if(matrix[i][j] == 1) num++;
            } else {
                if(matrix[j][i] == 1) num++;
            }
        }
        degrees[i] = num;
    }
    return degrees;
}

int isRegular(int *degrees) {
    int previous = degrees[0];
    for (int i = 1; i < vertices; i++) {
        if(degrees[i] != previous) return 0;
    }
    return 1;
}

int *getIsolated(int *degrees) {
    int *isolated;
    isolated = calloc(vertices, sizeof(int));
    int num = 0;
    isolated[num] = 0;
    for (int i = 0; i < vertices; i++) {
        if(degrees[i] == 0) {
            isolated[i] = i+1;
            num++;
        }
    }
    return isolated;
}

double **multiplyMatrix(double **matrix1, double **matrix2) {
    double **matrix = malloc(vertices * sizeof(double));
    for (int i = 0; i < vertices; i++) {
        matrix[i] = malloc(vertices * sizeof(double));
        for (int j = 0; j < vertices; j++) {
            matrix[i][j] = 0;
            for (int k = 0; k < vertices; k++) {
                matrix[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
    return matrix;
}

double **addMatrices(double **matrix1, double **matrix2) {
    double **matrix = malloc(vertices * sizeof(double));
    for (int i = 0; i < vertices; i++) {
        matrix[i] = malloc(vertices * sizeof(double));
        for (int j = 0; j < vertices; j++) {
            matrix[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }
    return matrix;
}

void boolConversion(double **matrix){
    for (int i = 0; i < vertices; ++i) {
        for (int j = 0; j < vertices; ++j) {
            if(matrix[i][j]) matrix[i][j] = 1;
        }
    }
}

double **reachabilityMatrix(double **matrix) {
    double **result = matrix;
    double **previous = matrix;

    for (int i = 1; i < vertices - 1; ++i) {
        previous = multiplyMatrix(previous, matrix);
        result = addMatrices(result, previous);
    }

    for (int i = 0; i < vertices; i++) {
        result[i][i] += 1;
    }

    boolConversion(result);
    return result;
}

double **transposeMatrix(double **matrix) {
    double **result = malloc(vertices * sizeof(double));
    for (int i = 0; i < vertices; i++) {
        result[i] = malloc(vertices * sizeof(double));
        for (int j = 0; j < vertices; j++) {
            result[i][j] = matrix[j][i];
        }
    }
    return result;
}

double **multiplyElements(double **matrix1, double **matrix2) {
    double **result = malloc(vertices * sizeof(double));
    for (int i = 0; i < vertices; i++) {
        result[i] = malloc(vertices * sizeof(double));
        for (int j = 0; j < vertices; j++) {
            result[i][j] = matrix1[i][j] * matrix2[i][j];
        }
    }
    return result;
}

double **conMatrix(double **matrix1) {
    double **transposed = transposeMatrix(matrix1);
    double **connectivityMatrix = multiplyElements(matrix1, transposed);
    return connectivityMatrix;
}

void dfs(double **matrix, int v, double *component, int *visited) {
    visited[v] = 1;
    component[v] = 1;
    for (int i = 0; i < vertices; i++) {
        if (!visited[i] && matrix[i][v]) {
            dfs(matrix, i, component, visited);
        }
    }
}

double **getComponents(double **matrix) {
    int *visited = calloc(vertices, sizeof(int));

    double **components = calloc(vertices, sizeof(size_t*));
    for (int i = 0; i < vertices; i++) {
        components[i] = calloc(vertices, sizeof(double));
    }

    for (int v = 0; v < vertices; v++) {
        if (!visited[v]) {
            dfs(matrix, v, components[v], visited);
        }
    }
    return components;
}

int getNumVertices(double **matrix) {
    int num = 0;
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            if (matrix[i][j]) {
                i++;
                num++;
            }
        }
    }
    return num;
}

double **condensationMatrix(double **components) {
    int numVertices = getNumVertices(components);
    double **matrix = calloc(numVertices, sizeof(double));
    for (int i = 0; i < numVertices; i++) {
        matrix[i] = calloc(numVertices, sizeof(double));
    }

    int row = 1;
    int column = 0;
    for (int i = 1; i < 6; i++) {
        for (int j = 1; j < vertices ; ++j) {
            if(components[i][i]) matrix[row][column] = 1;
        }
    }
    return matrix;
}

#endif