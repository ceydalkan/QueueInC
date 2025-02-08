/*- Write a Priority Queue class that inserts the customers into queue according to their bank account amounts.
- Read 4 customer information from the user. 
- Print the content of the priority queue. 
*/
#include<stdio.h>
#include<stdlib.h>

struct Node {
    void* data1;
    void* data2;
    struct Node* next;
    struct Node* previous;
};

struct LinkedList {
    struct Node* head;
    struct Node* tail;
};

struct Node* createNode(void* data1, void* data2) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data1 = data1;
    newNode->data2 = data2;
    newNode->next = NULL;
    return newNode;
}

struct LinkedList* createList() {
    struct LinkedList* newList = (struct LinkedList*)malloc(sizeof(struct LinkedList));
    newList->head = NULL;
    newList->tail = NULL;
    return newList;
}

void enqueue(struct LinkedList* linkedList, struct Node* addedNode) { 
   if (linkedList->head == NULL) {
        linkedList->head = addedNode;
        linkedList->tail = addedNode;
        return;
   } 

   struct Node* prev = NULL;
   struct Node* current = linkedList->head;

   while (current != NULL) {
    if (*(int*)current->data2 < *(int*)addedNode->data2) {
        if (current == linkedList->head) {
            addedNode->next = current;
            current->previous = addedNode;
            addedNode->previous = NULL;
            linkedList->head = addedNode;
            return;
        }

        prev->next = addedNode;
        addedNode->previous = prev;
        addedNode->next = current;
        current->previous = addedNode;
        return;
    }

    prev = current;
    current = current->next;
   }

    prev->next = addedNode;
    addedNode->previous = prev;
    linkedList->tail = addedNode;
}

struct Node* dequeue(struct LinkedList* linkedList) {
    if (linkedList->head == NULL) {
        return NULL;
    }

    struct Node* deletedNode = linkedList->head;
    linkedList->head = deletedNode->next;
    
    if (linkedList->head != NULL) {
        linkedList->head->previous = NULL;
    } else {
        linkedList->tail = NULL;
    }

    deletedNode->next = NULL;
    return deletedNode;
}

void printQueue(struct LinkedList* linkedList) {
    if (linkedList->head == NULL) {
        printf("Queue is empty\n");
        return;
    }

    struct Node* current = linkedList->head;
    while (current != NULL) {
        if (current->data1 != NULL && current->data2 != NULL) {
            printf("name: %c  account balance: %d\n", *(char*)(current->data1), *(int*)(current->data2));
        } else {
            printf("Error: data1 or data2 is NULL!\n");
        }
            current = current->next;
    }
}

void freeList(struct LinkedList* linkedList) {
    struct Node* current = linkedList->head;
    while (current != NULL) {
        struct Node* temp = current;
        current = current->next;
        free(temp->data1); 
        free(temp->data2); 
        free(temp);         
    }
    free(linkedList);  
}

int main() {
    struct LinkedList* list = createList();

    for (int i = 0; i < 4; ++i) {
        printf("Welcome, please enter your name and account balance: ");
        
        char* name = (char*)malloc(20 * sizeof(char));
        int* balance = (int*)malloc(sizeof(int));
        
        if (scanf("%s %d", name, balance) != 2) {
            printf("Invalid input.\n");
            free(name);
            free(balance);
            return 1;
        }
        struct Node* newNode = createNode(name, balance);
        enqueue(list, newNode);
    }

    printf("Queue: \n");
    printQueue(list);

    freeList(list);
    return 0;
}