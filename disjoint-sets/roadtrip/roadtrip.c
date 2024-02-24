#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_EMPLOYEES 100
#define NUM_PROJECTS 5

int parent[MAX_EMPLOYEES];
int size[MAX_EMPLOYEES];

void init(int n) {
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        size[i] = 1;
    }
}

int find(int x) {
    if (parent[x] == x) {
        return x;
    } else {
        return parent[x] = find(parent[x]);
    }
}

void merge(int x, int y) {
    x = find(x);
    y = find(y);
    if (x != y) {
        if (size[x] < size[y]) {
            int tmp = x;
            x = y;
            y = tmp;
        }
        parent[y] = x;
        size[x] += size[y];
    }
}

void print_project_groups(int n) {
    printf("Employees grouped by project:\n");
    for (int i = 1; i <= NUM_PROJECTS; i++) {
        printf("Project %d:", i);
        for (int j = 0; j < n; j++) {
            if (find(j) == find(i-1)) {
                printf(" %d", j);
            }
        }
        printf("\n");
    }
}

int main() {
    srand(time(NULL));

    int n = 10;
    int projects[MAX_EMPLOYEES];

    // randomly assign projects to employees
    for (int i = 0; i < n; i++) {
        projects[i] = rand() % NUM_PROJECTS + 1;
    }

    printf("Project assignments:\n");
    for (int i = 0; i < n; i++) {
        printf("Employee %d is working on Project %d\n", i, projects[i]);
    }

    init(n);
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            if (projects[i] == projects[j]) {
                merge(i, j);
            }
        }
    }

    print_project_groups(n);

    return 0;
}
