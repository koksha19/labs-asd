#ifndef TRAVERSAL
#define TRAVERSAL

#include <stdlib.h>

#include "matrix.c"
#include "queueAndStack.c"

typedef struct traverseMatrices {
    double **treeMatrix;
    double **orderMatrix;
} matrices;

matrices bfs(double **matrix) {
    int counter = 0;
    double **treeMatrix = malloc(vertices * sizeof(size_t*));
    double **orderMatrix = malloc(vertices * sizeof(size_t*));
    for (int i = 0; i < vertices; i++) {
        treeMatrix[i] = calloc(vertices, sizeof(double ));
        orderMatrix[i] = calloc(vertices, sizeof(double ));
    }

    int *visited = calloc(vertices, sizeof(int));
    queue *q = initQueue();
    enqueue(q, 0);
    visited[0] = 1;

    while (q->head) {
        int vertex = q->head->value;
        orderMatrix[vertex][counter] = 1;
        for (int i = 0; i <vertices; i++) {
            if (!visited[i] && matrix[vertex][i]) {
                visited[i] = 1;
                treeMatrix[vertex][i] = 1;
                enqueue(q, i);
            }
        }
        counter++;
        dequeue(q);
    }
    free(visited);
    free(q);

    matrices traverseMatrices = {treeMatrix, orderMatrix};

    return traverseMatrices;
}

matrices dfs(double **matrix) {
    int counter = 0;
    double **treeMatrix = malloc(vertices * sizeof(size_t*));
    double **orderMatrix = malloc(vertices * sizeof(size_t*));
    for (int i = 0; i < vertices; i++) {
        treeMatrix[i] = calloc(vertices, sizeof(double));
        orderMatrix[i] = calloc(vertices, sizeof(double));
    }

    int *visited = calloc(vertices, sizeof(int));
    stack *s = initStack();
    push(s, 0);
    visited[0] = 1;
    orderMatrix[0][counter] = 1;
    counter++;

    while (s->top) {
        int value = s->top->value;
        for (int i = 0; i < vertices; i++) {
            if (matrix[value][i] && !visited[i]) {
                treeMatrix[value][i] = 1;
                orderMatrix[i][counter] = 1;
                visited[i] = 1;
                push(s, i);
                counter++;
                break;
            } else if (i == vertices - 1) {
                pop(s);
            }
        }
    }
    free(visited);
    free(s);

    matrices searchMatrices = {treeMatrix, orderMatrix};
    return searchMatrices;
}
#endif
