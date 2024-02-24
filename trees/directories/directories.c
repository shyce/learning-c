#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char name[50];
    struct Node* left;
    struct Node* right;
    int height; // Only for AVL trees
    int color; // Only for Red-Black trees
} Node;

Node* create_node(const char* name) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    strcpy(new_node->name, name);
    new_node->left = new_node->right = NULL;
    new_node->height = 1; // Only for AVL trees
    new_node->color = 0; // Only for Red-Black trees
    return new_node;
}

Node* insert(Node* root, const char* name) {
    if (root == NULL) {
        return create_node(name);
    }
    if (strcmp(name, root->name) < 0) {
        root->left = insert(root->left, name);
    } else {
        root->right = insert(root->right, name);
    }
    return root;
}

void inorder_traversal(Node* root) {
    if (root == NULL) {
        return;
    }
    inorder_traversal(root->left);
    printf("%s\n", root->name);
    inorder_traversal(root->right);
}

int main() {
    Node* root = NULL;
    root = insert(root, "Documents");
    root = insert(root, "Downloads");
    root = insert(root, "Pictures");
    inorder_traversal(root);

    return 0;
}
