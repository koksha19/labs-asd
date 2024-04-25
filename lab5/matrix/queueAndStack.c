#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} node;

typedef struct Queue {
    node *head;
    node *tail;
} queue;

typedef struct Stack {
    node *top;
} stack;

queue *initQueue() {
    queue *queue = malloc(sizeof(queue));
    queue->head = NULL;
    queue->tail = NULL;
    return queue;
}

void enqueue(queue *q, int value) {
    node *newNode = malloc(sizeof(node));
    newNode->value = value;
    newNode->next = NULL;

    if (q->tail != NULL) {
        q->tail->next = newNode;
        q->tail = newNode;
    } else {
        q->head = newNode;
        q->tail = newNode;
    }
}

void dequeue(queue *q) {
    node *temp = q->head;
    if (q->head == NULL) {
        q->tail = NULL;
    } else {
        q->head = q->head->next;
    }
    free(temp);
}

stack *initStack() {
    stack *s = malloc(sizeof(stack));
    s->top = NULL;
    return s;
}

void push(stack *s, int value) {
    node *newNode = malloc(sizeof(node));
    newNode->value = value;
    newNode->next = s->top;
    s->top = newNode;
}

void pop(stack *s) {
    node *tmp = s->top;
    s->top = s->top->next;
    free(tmp);
}

