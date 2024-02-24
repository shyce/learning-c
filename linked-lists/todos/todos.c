#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char task[50];
    struct Node* next;
} Node;

Node* create_node(const char* task) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    strcpy(new_node->task, task);
    new_node->next = NULL;
    return new_node;
}

int main() {
    Node* head = create_node("Buy groceries");
    head->next = create_node("Do laundry");
    printf("First task: %s\n", head->next->task);

    return 0;
}
