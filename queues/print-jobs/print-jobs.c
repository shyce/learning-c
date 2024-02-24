#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int jobId;
    struct Node* next;
} Node;

typedef struct Queue {
    Node* front;
    Node* rear;
} Queue;

Queue* create_queue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = queue->rear = NULL;
    return queue;
}

Node* create_node(int jobId) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->jobId = jobId;
    new_node->next = NULL;
    return new_node;
}

void enqueue(Queue* queue, int jobId) {
    Node* new_node = create_node(jobId);
    if (queue->rear == NULL) {
        queue->front = queue->rear = new_node;
        return;
    }
    queue->rear->next = new_node;
    queue->rear = new_node;
}

int dequeue(Queue* queue) {
    if (queue->front == NULL) {
        return -1;
    }
    int jobId = queue->front->jobId;
    Node* temp = queue->front;
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    free(temp);
    return jobId;
}

int main() {
    Queue* queue = create_queue();
    enqueue(queue, 1);
    enqueue(queue, 2);
    printf("Job %d is being printed\n", dequeue(queue));
    printf("Job %d is being printed\n", dequeue(queue));

    return 0;
}
