#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10

typedef struct User {
    char username[50];
    char password[50];
} User;

User* create_user(const char* username, const char* password) {
    User* new_user = (User*)malloc(sizeof(User));
    strcpy(new_user->username, username);
    strcpy(new_user->password, password);
    return new_user;
}

unsigned int hash(const char* key) {
    unsigned int hash_value = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        hash_value = 31 * hash_value + key[i];
    }
    return hash_value % TABLE_SIZE;
}

User* find_user(User** hash_table, const char* username) {
    unsigned int index = hash(username);
    User* current = hash_table[index];
    while (current != NULL) {
        if (strcmp(current->username, username) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void insert_user(User** hash_table, const char* username, const char* password) {
    unsigned int index = hash(username);
    User* new_user = create_user(username, password);
    new_user->next = hash_table[index];
    hash_table[index] = new_user;
}

int main() {
    User* hash_table[TABLE_SIZE] = {NULL};
    insert_user(hash_table, "Alice", "password1");
    insert_user(hash_table, "Bob", "password2");
    User* alice = find_user(hash_table, "Alice");
    User* bob = find_user(hash_table, "Bob");
    printf("Alice's password: %s\n", alice->password);
    printf("Bob's password: %s\n", bob->password);

    return 0;
}

