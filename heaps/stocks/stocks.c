#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_STOCKS 10

typedef struct Stock {
    int id;
    float potential_gain;
} Stock;

typedef struct MaxHeap {
    Stock *data[MAX_STOCKS];
    int size;
} MaxHeap;

MaxHeap *create_max_heap();
void swap(Stock **a, Stock **b);
void insert(MaxHeap *heap, Stock *stock);
Stock *extract_max(MaxHeap *heap);
void heapify(MaxHeap *heap, int i);
void print_stocks(const MaxHeap *heap);

int main() {
    MaxHeap *stock_heap = create_max_heap();
    srand(time(NULL));

    printf("Simulating stocks with random potential gains...\n");
    for (int i = 1; i <= 20; i++) {
        Stock *new_stock = (Stock *)malloc(sizeof(Stock));
        new_stock->id = i;
        new_stock->potential_gain = (rand() % 10000) / 100.0;

        printf("Stock %d has a potential gain of %.2f%%\n", new_stock->id, new_stock->potential_gain);
        insert(stock_heap, new_stock);
    }

    printf("\nTop 10 stocks:\n");
    print_stocks(stock_heap);

    return 0;
}

MaxHeap *create_max_heap() {
    MaxHeap *heap = (MaxHeap *)malloc(sizeof(MaxHeap));
    heap->size = 0;
    return heap;
}

void swap(Stock **a, Stock **b) {
    Stock *temp = *a;
    *a = *b;
    *b = temp;
}

void insert(MaxHeap *heap, Stock *stock) {
    if (heap->size < MAX_STOCKS) {
        heap->data[heap->size] = stock;
        int i = heap->size;
        heap->size++;

        while (i != 0 && heap->data[(i - 1) / 2]->potential_gain < heap->data[i]->potential_gain) {
            swap(&heap->data[i], &heap->data[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    } else {
        if (stock->potential_gain > heap->data[0]->potential_gain) {
            heap->data[0] = stock;
            heapify(heap, 0);
        } else {
            free(stock);
        }
    }
}

Stock *extract_max(MaxHeap *heap) {
    if (heap->size == 0) {
        return NULL;
    }

    Stock *root = heap->data[0];
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;

    heapify(heap, 0);

    return root;
}

void heapify(MaxHeap *heap, int i) {
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int largest = i;

    if (left < heap->size && heap->data[left]->potential_gain > heap->data[largest]->potential_gain) {
        largest = left;
    }

    if (right < heap->size && heap->data[right]->potential_gain > heap->data[largest]->potential_gain) {
        largest = right;
    }

    if (largest != i) {
        swap(&heap->data[i], &heap->data[largest]);
        heapify(heap, largest);
    }
}

void print_stocks(const MaxHeap *heap) {
    Stock *temp[MAX_STOCKS];
    int temp_size = 0;

    MaxHeap *heap_copy = create_max_heap();
    heap_copy->size = heap->size;
    for (int i = 0; i < heap->size; i++) {
        heap_copy->data[i] = heap->data[i];
    }

    printf("Rank\tStock ID\tPotential Gain\n");
    for (int i = 0; i < MAX_STOCKS; i++) {
        Stock *stock = extract_max(heap_copy);
        if (stock) {
            temp[temp_size++] = stock;
        }
    }

    for (int i = 0; i < temp_size; i++) {
        printf("%d\t%d\t\t%.2f%%\n", i + 1, temp[i]->id, temp[i]->potential_gain);
        free(temp[i]);
    }

    free(heap_copy);
}
