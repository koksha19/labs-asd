#include "matrix/matrix.c"

#define k1 0.67
#define k2 0.715

void printDegrees(int *degrees) {
    printf("[ ");
    for (int i = 0; i < vertices; i++) {
        printf(" %d ", degrees[i]);
    }
    printf("]");
}

void printIsolatedIndir(int *isolated) {
    printf("[ ");
    for (int i = 0; i < vertices; i++) {
        if(isolated[i])printf("%d ", isolated[i]);
    }
    printf("]");
}

void printIsolatedDir(int *isolated1, int *isolated2) {
    printf("[ ");
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; ++j) {
            if(isolated1[i] && isolated2[j] && isolated1[i] == isolated2[j]){
                printf("%d ", isolated1[i]);
            }
        }

    }
    printf("]");
}

void printPendantDir(int *out, int *in) {
    printf("[ ");
    for (int i = 0; i < vertices; ++i) {
        if(out[i] == 1 && in[i] == 0){
            printf("%d ", i+1);
        } else if(in[i] == 1 && out[i] == 0) {
            printf("%d ", i+1);
        }
    }
    printf("]");
}

void printPendant(int *degrees) {
    printf("[ ");
    for (int i = 0; i < vertices; ++i) {
        if(degrees[i] == 1) {
            printf("%d ", i+1);
        }
    }
    printf("]");
}

void printPaths2(double **squaredMatrix, double **matrix) {
    for (int i = 0; i < vertices; i++) {
        printf("Paths from vertex number %d\n", i+1);
        for (int j = 0; j < vertices; ++j) {
            if(squaredMatrix[i][j]) {
                for (int k = 0; k < vertices; ++k) {
                    if(matrix[i][k] && matrix[k][j]){
                        printf("[%d-%d-%d] ", i + 1, k + 1, j + 1);
                    }
                }
                printf("\n");
            }
        }
    }
}

void printPaths3(double **cubedMatrix, double **squaredMatrix, double **matrix) {
    for (int i = 0; i < vertices; i++) {
        printf("Paths from vertex number %d\n", i+1);
        for (int j = 0; j < vertices; j++) {
            if(cubedMatrix[i][j]){
                for (int k = 0; k < vertices; k++) {
                    for (int l = 0; l < vertices; l++) {
                        if(matrix[i][l] && matrix[l][k] && matrix[k][j]) {
                            printf("[%d-%d-%d-%d] ", i + 1, l + 1, k + 1, j + 1);
                        }
                    }
                }
                printf("\n");
            }
        }
    }
}

int printComponents(double **matrix) {
    int counter = 1;
    for (int i = 0; i < vertices; i++) {
        int isNew = 1;
        for (int j = 0; j < vertices; j++) {
            if(matrix[i][j]) {
                if (isNew) printf("Component %d: {  ", counter);
                printf("%d  ", j + 1);
                isNew = 0;
            }
        }
        if (!isNew) {
            counter++;
            printf("}\n");
        }
    }
    printf("Number of components: %d", counter - 1);
    return counter - 1;
}

void directGraph() {
    double **matrix = direct(k1);
    int *outDegrees = getDegrees(matrix, 1);
    int *inDegrees = getDegrees(matrix, 0);

    printf("\nDirect matrix:\n");
    printMatrix(direct(k1),vertices);

    printf("Out degrees: ");
    printDegrees(outDegrees);
    printf("\nIn degrees: ");
    printDegrees(inDegrees);

    int regular = isRegular(getDegrees(matrix, 1));
    if(regular == 1){
        printf("\nGraph is regular\n");
    } else {
        printf("\nGraph is irregular");
    }

    int *outIsolated = getIsolated(getDegrees(matrix, 1));
    int *inIsolated = getIsolated(getDegrees(matrix, 0));
    printf("\nIsolated vertices: ");
    printIsolatedDir(outIsolated, inIsolated);

    printf("\nPendant vertices: ");
    printPendantDir(outDegrees, inDegrees);
}

void indirectGraph() {
    double **matrix = indirect(k1);

    int *degrees = getDegrees(matrix, 1);

    printf("\n\nIndirect matrix:\n");
    printMatrix(indirect(k1), vertices);

    printf("Degrees: ");
    printDegrees(degrees);

    int regular = isRegular(getDegrees(matrix, 1));
    if(regular == 1){
        printf("\nGraph is regular\n");
    } else {
        printf("\nGraph is irregular");
    }

   int *isolated = getIsolated(getDegrees(matrix, 1));
    printf("\nIsolated vertices: ");
    printIsolatedIndir(isolated);

    printf("\nPendant vertices: ");
    printPendant(degrees);
}

void newGraph() {
    double **matrix = direct(k2);
    double **squaredMatrix = multiplyMatrix(matrix, matrix);
    double **cubeMatrix = multiplyMatrix(squaredMatrix, matrix);

    int *outDegrees = getDegrees(matrix, 1);
    int *inDegrees = getDegrees(matrix, 0);

    printf("\n\nNew direct matrix:\n");
    printMatrix(direct(k2), vertices);

    printf("Out degrees: ");
    printDegrees(outDegrees);
    printf("\nIn degrees: ");
    printDegrees(inDegrees);


    printf("\nNew matrix to square:\n");
    printMatrix(squaredMatrix, vertices);

    printf("Paths of length 2:\n");
    printPaths2(squaredMatrix, matrix);

    printf("\nNew matrix to cube:\n");
    printMatrix(cubeMatrix, vertices);

    printf("Paths of length 3:\n");
    printPaths3(cubeMatrix, squaredMatrix, matrix);

    printf("\nReachability matrix:\n");
    printMatrix(reachabilityMatrix(matrix), vertices);

    printf("\nStrong connectivity matrix:\n");
    printMatrix(conMatrix(reachabilityMatrix(matrix)), vertices);

    double **components = getComponents(conMatrix(reachabilityMatrix(matrix)));
    printf("\nStrong connectivity components:\n");
    printComponents(components);

    printf("\nCondensation matrix:\n");
    printMatrix(condensationMatrix(components), getNumVertices(components));
}

int main() {
    directGraph();
    indirectGraph();
    newGraph();
    return 0;
}