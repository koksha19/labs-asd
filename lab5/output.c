#include "matrix/matrix.c"
#include "matrix/bfsAndDfs.c"


void printAdj() {
    double **matrix = direct();
    printf("\nGraph Matrix:\n");
    printMatrix(matrix);
    freem(matrix);
}

void printBfs() {
    double **matrix = direct();
    matrices traverseMatrices = bfs(matrix);

    printf("\nBreadth-First Search:\n");
    printf("\nTree Matrix:\n");
    printMatrix(traverseMatrices.treeMatrix);
    printf("\nOutput order:\n");
    printMatrix(traverseMatrices.orderMatrix);

    freem(matrix);
    freem(traverseMatrices.treeMatrix);
    freem(traverseMatrices.orderMatrix);
}

void printDfs() {
    double **matrix = direct();
    matrices traverseMatrices = dfs(matrix);

    printf("\nDepth-First Search\n");
    printf("\nSearch Tree Matrix\n");
    printMatrix(traverseMatrices.treeMatrix);
    printf("\nOutput order\n");
    printMatrix(traverseMatrices.orderMatrix);

    freem(matrix);
    freem(traverseMatrices.treeMatrix);
    freem(traverseMatrices.orderMatrix);
}

int main() {
    printAdj();
    printBfs();
    printDfs();
}