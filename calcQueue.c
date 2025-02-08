/*- Create two circular queues with size 10.
- At each step, two integers (number1 and number2) are taken from the first queue and one operation is taken from the second queue. 
  The result of the statement (number1 operation number2) is placed to the first queue
  keep going until there are no operators
*/
#include<stdio.h>
#include<stdlib.h>

typedef struct {
    void** elements;
    int front, rear, capacity, size;
}Queue;

Queue* createQueue(int capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->capacity = capacity;
    queue->front = 0;
    queue->rear = -1;
    queue->size = 0;
    queue->elements = (void**)malloc(capacity * sizeof(void*));
    return queue;
};

void printQueue(Queue* queue, void (*printFunc)(void*)) {  //return_type (*pointer_name)(parameter_types)
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

void printChar(void *data) {
    printf("%c ", (char*)data);
}

void enqueue(Queue* queue, void* object) {
    if (isFull(queue)) {
        printf("Queue is full!\n");
        return;
    }

    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->elements[queue->rear] = object;
    queue->size++;
}

void* dequeue(Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty\n");
        return;
    }

    void* deletedItem = queue->elements[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size = queue->size - 1;
    return deletedItem;
}

void* peek(Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty\n");
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

int operate(Queue* numQueue, Queue* opQueue) {
    char* operator = (char*)dequeue(opQueue);
    int* numOne = (int*)dequeue(numQueue);
    int* numTwo = (int*)dequeue(numQueue);
    int result;

    switch (*operator) {
    case '+':
        result = *numOne + *numTwo;
        break;
    case '-':
        result = *numOne - *numTwo;
        break;
    case '*':
        result = *numOne * *numTwo;
        break;
    default:
        printf("Invalid operator: %c\n", *operator);
        return 0;
    }

    free(numOne);
    free(numTwo);
    free(operator);
    return result;
}

void freeQueue(Queue* queue) {
    while (!isEmpty(queue)) {
        free(dequeue(queue));
    }
    free(queue->elements);
    free(queue);
}

int main() {
    Queue* numberQueue = createQueue(10);
    Queue* operatorQueue = createQueue(10);

    int values[] = {14, 20, 13, 7, 8, 6, 11, 9, 3, 5};
    for (int i = 0; i < 10; i++) {
        int* num = (int*)malloc(sizeof(int));
        *num = values[i];
        enqueue(numberQueue, num);
    }

    char ops[] = {'+', '+', '-', '*', '+', '-', '*', '+', '+', '+'};  
    for (int i = 0; i < 10; i++) {
        char* op = (char*)malloc(sizeof(char)); 
        *op = ops[i];  
        enqueue(operatorQueue, op);
    }

   while (!isEmpty(operatorQueue)) {
        int result = operate(numberQueue,operatorQueue);
        int* resultPtr = (int*)malloc(sizeof(int));
        *resultPtr = result;
        enqueue(numberQueue,resultPtr);
        printQueue(numberQueue,printInt);
        printf("\n");
    }

    freeQueue(numberQueue);
    freeQueue(operatorQueue);
    return 1;
}