// randomly generating 10 numbers between -8 and 8, then inserting positive and negative numbers into different queues then prints them
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {   
    void** elements;
    int front, rear, capacity, size;
}Queue;

Queue* createQueue(int capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));  //creating a pointer that points to the queue
    queue->capacity = capacity;
    queue->front = 0;
    queue->rear = -1;
    queue->size = 0;
    queue->elements = (void**)malloc(capacity * sizeof(void*));
    return queue;
}

void printQueue(Queue* queue, void (*printFunc)(void*)) {  //the second parameter is a function pointer: return_type (*pointer_name)(parameter_types);
    if (isEmpty(queue)) {
        printf("Queue is empty!\n");
        return;
    }

    int index = queue->front;
    int count = 0;
    while (count < queue->size) {
        printFunc(queue->elements[index]);
        index = (index + 1) % queue->capacity;
        count++;
    }
}

void printInt(void *data) {
    printf("%d ", *(int*)data);
}

void printString(void *data) {
    printf("%s ", (char*)data);
}

void enqueue(Queue* queue, void* object) {
    if (isFull(queue)) {
        printf("Queue is full!\n");
        return;
    }

    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->elements[queue->rear] = object;
    queue->size = queue->size + 1;
}

void* dequeue(Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty!\n");
        return;
    }

    void* deletedItem = queue->elements[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size = queue->size - 1;
    return deletedItem;
}

void* peek(Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty!\n");
        return;
    }
    return (queue->elements[queue->front]);
}

int isEmpty(Queue* queue) {
    return (queue->size == 0);
}

int isFull(Queue* queue) {
    return (queue->size == queue->capacity);
}

int main() {
    srand(time(NULL));

    Queue* QueuePositive = createQueue(10);
    Queue* QueueNegative = createQueue(10);

    for (int i = 0; i < 10; i++) {
        int num = (rand() % 17) - 8;
        int* numPtr = (int*)malloc(sizeof(int));
        *numPtr = num;

        if (num >= 0) {
            enqueue(QueuePositive, numPtr);
        } else {
            enqueue(QueueNegative, numPtr);
        }
    }

    printf("Positive Queue: ");
    printQueue(QueuePositive, printInt);
    printf("\n");
    printf("Negative Queue: ");
    printQueue(QueueNegative, printInt);
    printf("\n");

    for (int i = 0; i < QueuePositive->size; i++) {
        free(QueuePositive->elements[i]);
    }
    for (int i = 0; i < QueueNegative->size; i++) {
        free(QueueNegative->elements[i]);
    }

    free(QueuePositive->elements);
    free(QueueNegative->elements);
    free(QueuePositive);
    free(QueueNegative);

    return 0;
}