/*Add 8 random numbers between 6 and 20 into the queue. 
    Generate random numbers between -5 and 3 continuously. 
       - If the number is negative, remove elements as the number of times. 
       - If the number is positive, add new random elements as the number of times. 
    When the queue is empty, stop the program. 
*/
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

void printQueue(Queue* queue, void (*printFunc)(void*)) {
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
    Queue* queue = createQueue(8);

    for (int i = 0; i < 8; i++) {
        int num = (rand() % 15) + 6;
        int* numPtr = (int*)malloc(sizeof(int));
        *numPtr = num;
        enqueue(queue, numPtr);
    }
    printf("Initial Queue: ");
    printQueue(queue, printInt);
    printf("\n");
    
    while(!isEmpty(queue)) {
        int ref = (rand() % 9) - 5;
        printf("reference value: %d ", ref);

        if (ref > 0) {
            for (int i = 0; i < ref; i++) {
                int addedNum = (rand() % 15) + 6;
                int* addedNumPtr = (int*)malloc(sizeof(int));
                *addedNumPtr = addedNum;
                enqueue(queue, addedNumPtr);
            }
        } else if (ref < 0) {
            for (int i = 0; i < -ref && !isEmpty(queue); i++) {
                dequeue(queue);
            }
        }

        printf("Queue after operation: ");
        printQueue(queue, printInt);
        printf("\n");
    }

    for (int i = 0; i < queue->size; i++) {
    free(queue->elements[i]);
    }
    free(queue->elements);
    free(queue);

    return 0;
}