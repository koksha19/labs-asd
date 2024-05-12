#ifndef MST
#define MST

#include <stdio.h>
#include <stdlib.h>

#include "matrix.c"

typedef struct Vertex {
    int dest;
    int weight;
    struct Vertex *next;
} vertex;

typedef struct AdjacencyList {
    vertex *head;
} list;

typedef struct Graph {
    list *numVertex;
} graph;

typedef struct HeapVertex {
    int vert;
    int value;
} heapVertex;

typedef struct Heap {
    int size;
    int *positions;
    heapVertex  **nodes;
} heap;

vertex *newListNode(int dest, int weight) {
    vertex *newNode = (vertex*)malloc(sizeof(vertex));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

graph *newGraph() {
    graph *indirGraph = (graph*)malloc(sizeof(graph));
    indirGraph->numVertex = (list*)malloc(vertices * sizeof(list));

    for (int i = 0; i < vertices; i++) {
        indirGraph->numVertex[i].head = NULL;
    }

    return indirGraph;
}

void addEdge(graph *indirGraph, int from, int to, int weight) {
    vertex *newNode = newListNode(to, weight);
    newNode->next = indirGraph->numVertex[from].head;
    indirGraph->numVertex[from].head = newNode;

    newNode = newListNode(from, weight);
    newNode->next = indirGraph->numVertex[to].head;
    indirGraph->numVertex[to].head = newNode;
}

heapVertex *newMinHeapNode(int vertex, int value) {
    heapVertex *minHeapNode = (heapVertex*)malloc(sizeof(heapVertex));
    minHeapNode->vert = vertex;
    minHeapNode->value = value;
    return minHeapNode;
}

heap *newMinHeap(int capacity) {
    heap *minHeap = (heap*)malloc(sizeof(heap));
    minHeap->size = 0;
    minHeap->positions = (int*)malloc(capacity * sizeof(int));
    minHeap->nodes = (heapVertex**)malloc(capacity * sizeof(heapVertex*));
    return minHeap;
}

void swapMinHeapNode(heapVertex **first, heapVertex  **second) {
    heapVertex *temp = *first;
    *first = *second;
    *second = temp;
}

void heapify(heap *heap, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < heap->size && heap->nodes[left]->value < heap->nodes[smallest]->value)
        smallest = left;
    if (right < heap->size && heap->nodes[right]->value < heap->nodes[smallest]->value)
        smallest = right;
    if (smallest != index) {
        heapVertex *smallestNode = heap->nodes[smallest];
        heapVertex *idxNode = heap->nodes[index];

        heap->positions[smallestNode->vert] = index;
        heap->positions[idxNode->vert] = smallest;

        swapMinHeapNode(&heap->nodes[smallest], &heap->nodes[index]);

        heapify(heap, smallest);
    }
}

heapVertex *removeMinimal(heap *heap) {
    if (heap->size == 0) return NULL;

    heapVertex *root = heap->nodes[0];
    heapVertex *lastNode = heap->nodes[heap->size - 1];
    heap->nodes[0] = lastNode;
    heap->positions[root->vert] = heap->size - 1;
    heap->positions[lastNode->vert] = 0;
    heap->size--;
    heapify(heap, 0);

    return root;
}

void updateKey(heap *minHeap, int vertex, int value) {
    int index = minHeap->positions[vertex];

    minHeap->nodes[index]->value = value;

    while (index && minHeap->nodes[index]->value < minHeap->nodes[(index - 1) / 2]->value) {
        minHeap->positions[minHeap->nodes[index]->vert] = (index - 1) / 2;
        minHeap->positions[minHeap->nodes[(index - 1) / 2]->vert] = index;
        swapMinHeapNode(&minHeap->nodes[index], &minHeap->nodes[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

int *PrimMST(graph *indirGraph) {
    int inf = 99999;
    int *mstArray = malloc(vertices * sizeof(int));
    int value[vertices];

    heap *minHeap = newMinHeap(vertices);

    for (int i = 1; i < vertices; i++) {
        mstArray[i] = -1;
        value[i] = inf;
        minHeap->nodes[i] = newMinHeapNode(i, value[i]);
        minHeap->positions[i] = i;
    }

    value[0] = 0;
    minHeap->size = vertices;
    minHeap->positions[0] = 0;
    minHeap->nodes[0] = newMinHeapNode(0, value[0]);

    while (minHeap->size != 0) {
        heapVertex *minHeapNode = removeMinimal(minHeap);
        int vert = minHeapNode->vert;
        vertex *adjacentVertex = indirGraph->numVertex[vert].head;
        while (adjacentVertex != NULL) {
            int dest = adjacentVertex->dest;
            if (minHeap->positions[dest] < minHeap->size && adjacentVertex->weight < value[dest]) {
                value[dest] = adjacentVertex->weight;
                mstArray[dest] = vert;
                updateKey(minHeap, dest, value[dest]);
            }
            adjacentVertex = adjacentVertex->next;
        }
    }
    return mstArray;
}

double **listToMatrix(int *arrayMST) {
    int counter = 1;
    double **matrixMST;

    matrixMST = malloc(vertices * sizeof(size_t*));
    for (int i = 0; i < vertices; i++) {
        matrixMST[i] = malloc(vertices * sizeof(double));
    }

    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            matrixMST[i][j] = 0;
        }
    }

    for (int i = 1; i < vertices; i++) {
        int vertex = arrayMST[counter];
        matrixMST[i][vertex] = 1;
        counter++;
    }
    return matrixMST;
}

int *getWeights(double **W, double **mstMatrix) {
    int counter = 0;
    int *weights = calloc(vertices-1,sizeof(int));

    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            if(mstMatrix[i][j]) {
                weights[counter] = (int)W[i][j];
                counter++;
            }
        }
    }
    return weights;
}

int *sortArray(int *weights) {
    int *sortedArray = calloc(vertices-1, sizeof(int));

    for (int i = 0; i < vertices - 1; i++) {
        sortedArray[i] = weights[i];
    }

    for (int i = 0; i < vertices - 1; i++) {
        for (int j = 0; j < vertices - i - 1; j++) {
            if(sortedArray[j+1] == 0) break;
            if (sortedArray[j] > sortedArray[j + 1]) {
                int temp = sortedArray[j];
                sortedArray[j] = sortedArray[j + 1];
                sortedArray[j + 1] = temp;
            }
        }
    }
    return sortedArray;
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

double **orderMatrix() {
    double **orderMatrix;
    int counter = 0;
    int order[9] = {5, 7, 2, 1, 8, 4, 3, 9, 6};

    orderMatrix = calloc(vertices, sizeof(size_t*));
    for (int i = 0; i < vertices; i++) {
        orderMatrix[i] = calloc(vertices, sizeof(double));
    }

    for (int i = 0; i < vertices; i++) {
        orderMatrix[i][order[counter]] = 1;
        counter++;
    }
    return transposeMatrix(orderMatrix);
}

void getSum() {
    int counter = 1;
    double **adjMatrix = indirect();
    double **weightMatrix = getW();
    struct Graph* graph = newGraph();

    for (int i = 0; i < vertices; i++) {
        for (int j = counter; j < vertices; j++) {
            if (adjMatrix[i][j] != 0) {
                addEdge(graph, i, j, (int)weightMatrix[i][j]);
            }
        }
        counter++;
    }

    double **mstMatrix = listToMatrix(PrimMST(graph));
    int *weights = getWeights(weightMatrix, mstMatrix);
    int *sortedWeights = sortArray(weights);
    int result = 0;

    printf("[");
    for (int i = 0; i < vertices - 1 ; i++) {
        printf("%d  ", sortedWeights[i]);
        result += sortedWeights[i];
    }
    printf("]");
    printf("\nSum of weights: %d", result);
}

#endif


