#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LABEL_SIZE 64

typedef struct Node {
    char vertex[MAX_LABEL_SIZE];
    struct Node* next;
} Node;

typedef struct Graph {
    int num_vertices;
    int max_vertices;
    Node** adj_lists;
    bool* visited;
} Graph;

Node* create_node(const char* vertex) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    strncpy(newNode->vertex, vertex, MAX_LABEL_SIZE);
    newNode->next = NULL;
    return newNode;
}

Graph* create_graph(int max_vertices) {
    Graph* graph = (Graph*) malloc(sizeof(Graph));
    graph->num_vertices = 0;
    graph->max_vertices = max_vertices;
    graph->adj_lists = (Node**) malloc(max_vertices * sizeof(Node*));
    graph->visited = (bool*) malloc(max_vertices * sizeof(bool));
    for (int i = 0; i < max_vertices; i++) {
        graph->adj_lists[i] = NULL;
        graph->visited[i] = false;
    }
    return graph;
}

int get_vertex_index(Graph* graph, const char* vertex) {
    for (int i = 0; i < graph->num_vertices; i++) {
        if (graph->adj_lists[i] && strcmp(graph->adj_lists[i]->vertex, vertex) == 0) {
            return i;
        }
    }
    return -1;
}

void add_edge(Graph* graph, const char* src, const char* dest) {
    int src_index = get_vertex_index(graph, src);
    if (src_index == -1) {
        src_index = graph->num_vertices++;
        graph->adj_lists[src_index] = create_node(src);
    }
    int dest_index = get_vertex_index(graph, dest);
    if (dest_index == -1) {
        dest_index = graph->num_vertices++;
        graph->adj_lists[dest_index] = create_node(dest);
    }

    Node* newNode = create_node(dest);
    newNode->next = graph->adj_lists[src_index]->next;
    graph->adj_lists[src_index]->next = newNode;

    newNode = create_node(src);
    newNode->next = graph->adj_lists[dest_index]->next;
    graph->adj_lists[dest_index]->next = newNode;
}

void print_ascii_tree(Graph* graph, const char* vertex, int depth) {
    int index = get_vertex_index(graph, vertex);
    if (graph->visited[index]) {
        return;
    }
    graph->visited[index] = true;

    for (int i = 0; i < depth; i++) {
        printf("  ");
    }
    printf("|-%s\n", vertex);

    Node* temp = graph->adj_lists[index]->next;
    while (temp) {
        print_ascii_tree(graph, temp->vertex, depth + 1);
        temp = temp->next;
    }
}

int main() {
    Graph* graph = create_graph(40);

    add_edge(graph, "New York", "Boston");
    add_edge(graph, "New York", "Philadelphia");
    add_edge(graph, "Philadelphia", "Washington");
    add_edge(graph, "Washington", "Atlanta");
    add_edge(graph, "Atlanta", "New Orleans");
    add_edge(graph, "New York", "Chicago");
    add_edge(graph, "Chicago", "Denver");
    add_edge(graph, "Denver", "Los Angeles");
    add_edge(graph, "Los Angeles", "San Francisco");
    add_edge(graph, "San Francisco", "Portland");
    add_edge(graph, "Portland", "Seattle");
    add_edge(graph, "Seattle", "Vancouver");
    add_edge(graph, "Los Angeles", "San Diego");
    add_edge(graph, "San Diego", "Phoenix");
    add_edge(graph, "Phoenix", "Tucson");
    add_edge(graph, "Tucson", "El Paso");
    add_edge(graph, "El Paso", "San Antonio");
    add_edge(graph, "San Antonio", "Austin");
    add_edge(graph, "Austin", "Houston");
    add_edge(graph, "Houston", "Dallas");
    add_edge(graph, "Dallas", "Oklahoma City");
    add_edge(graph, "Oklahoma City", "Kansas City");
    add_edge(graph, "Kansas City", "St. Louis");
    add_edge(graph, "St. Louis", "Chicago");
    add_edge(graph, "Chicago", "Detroit");
    add_edge(graph, "Detroit", "Toronto");
    add_edge(graph, "Toronto", "Montreal");
    add_edge(graph, "Montreal", "Quebec City");
    add_edge(graph, "Quebec City", "Halifax");
    add_edge(graph, "Halifax", "St. John's");
    add_edge(graph, "Detroit", "Grand Rapids");
    add_edge(graph, "Detroit", "Toledo");
    add_edge(graph, "Grand Rapids", "Lansing");
    add_edge(graph, "Grand Rapids", "Kalamazoo");
    add_edge(graph, "Kalamazoo", "South Bend");
    add_edge(graph, "South Bend", "Chicago");
    add_edge(graph, "Lansing", "Flint");
    add_edge(graph, "Flint", "Saginaw");
    add_edge(graph, "Saginaw", "Midland");
    add_edge(graph, "Midland", "Bay City");
    add_edge(graph, "Kalamazoo", "Chicago");
    add_edge(graph, "Kalamazoo", "Columbus");
    add_edge(graph, "Kalamazoo", "Detroit");

    print_ascii_tree(graph, "Kalamazoo", 0);

    return 0;
}

