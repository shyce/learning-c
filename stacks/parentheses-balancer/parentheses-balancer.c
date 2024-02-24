#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char data;
    struct Node* next;
} Node;

Node* create_node(char data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void push(Node** top, char data) {
    Node* new_node = create_node(data);
    new_node->next = *top;
    *top = new_node;
}

char pop(Node** top) {
    if (*top == NULL) {
        return '\0';
    }
    char data = (*top)->data;
    Node* temp = *top;
    *top = (*top)->next;
    free(temp);
    return data;
}

int is_balanced(const char* expression) {
    Node* stack = NULL;
    for (int i = 0; expression[i] != '\0'; i++) {
        if (expression[i] == '(') {
            push(&stack, '(');
        } else if (expression[i] == ')') {
            if (pop(&stack) != '(') {
                return 0;
            }
        }
    }
    return stack == NULL;
}

int main() {
    const char* expression = "((5+3)*(2-1))";
    printf("Is the expression balanced? %s\n", is_balanced(expression) ? "Yes" : "No");

    return 0;
}
