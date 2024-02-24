#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

typedef struct TrieNode {
    int is_word;
    struct TrieNode* children[ALPHABET_SIZE];
} TrieNode;

typedef struct Trie {
    TrieNode* root;
    int size;
} Trie;

TrieNode* create_node() {
    TrieNode* node = (TrieNode*) malloc(sizeof(TrieNode));
    node->is_word = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        node->children[i] = NULL;
    }
    return node;
}

void insert(Trie* trie, char* word) {
    TrieNode* current_node = trie->root;
    int len = strlen(word);
    for (int i = 0; i < len; i++) {
        int index = tolower(word[i]) - 'a';
        if (!current_node->children[index]) {
            current_node->children[index] = create_node();
        }
        current_node = current_node->children[index];
    }
    current_node->is_word = 1;
    trie->size++;
}

void print_trie(TrieNode* node, char* buffer, int depth) {
    if (node->is_word) {
        buffer[depth] = '\0';
        printf("%s\n", buffer);
    }
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (node->children[i]) {
            buffer[depth] = i + 'a';
            print_trie(node->children[i], buffer, depth + 1);
        }
    }
}

void search(TrieNode* node, char* query, char* buffer, int depth) {
    int len = strlen(query);
    for (int i = 0; i < len; i++) {
        int index = tolower(query[i]) - 'a';
        if (!node->children[index]) {
            printf("No match found for \"%s\".\n", query);
            return;
        }
        buffer[depth] = index + 'a';
        node = node->children[index];
        depth++;
    }
    printf("Results for \"%s\":\n", query);
    print_trie(node, buffer, depth);
}

int main() {
    Trie* trie = (Trie*) malloc(sizeof(Trie));
    trie->root = create_node();
    trie->size = 0;

    insert(trie, "apple");
    insert(trie, "apricot");
    insert(trie, "banana");
    insert(trie, "cherry");
    insert(trie, "grape");
    insert(trie, "lemon");
    insert(trie, "lime");
    insert(trie, "mango");
    insert(trie, "orange");
    insert(trie, "peach");
    insert(trie, "pear");
    insert(trie, "pineapple");
    insert(trie, "plum");
    insert(trie, "pomegranate");
    insert(trie, "raspberry");
    insert(trie, "strawberry");
    insert(trie, "watermelon");

    printf("Dataset contains %d entries.\n", trie->size);

    char query[100];
    char buffer[100];
    printf("Enter a fruit name to search for: ");
    scanf("%s", query);

    search(trie->root, query, buffer, 0);

    return 0;
}
