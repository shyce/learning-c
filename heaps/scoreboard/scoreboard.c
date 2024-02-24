#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <time.h>

#define MAX_PLAYERS 10

typedef struct Player
{
    int id;
    int score;
} Player;

typedef struct MinHeap
{
    Player *data[MAX_PLAYERS];
    int size;
} MinHeap;

MinHeap *create_min_heap();
void swap(Player **a, Player **b);
void insert(MinHeap *heap, Player *player);
Player *extract_min(MinHeap *heap);
void heapify(MinHeap *heap, int i);
void print_leaderboard(MinHeap *heap);

int main()
{
    MinHeap *leaderboard = create_min_heap();
    srand(time(NULL));

    printf("Simulating game with random scores...\n");
    for (int i = 1; i <= 30; i++)
    {
        Player *new_player = (Player *)malloc(sizeof(Player));
        new_player->id = i;
        new_player->score = rand() % 1000;

        printf("Player %d scored %d points\n", new_player->id, new_player->score);
        insert(leaderboard, new_player);
    }

    printf("\nTop 10 scores:\n");
    print_leaderboard(leaderboard);

    return 0;
}

MinHeap *create_min_heap()
{
    MinHeap *heap = (MinHeap *)malloc(sizeof(MinHeap));
    heap->size = 0;
    return heap;
}

void swap(Player **a, Player **b)
{
    Player *temp = *a;
    *a = *b;
    *b = temp;
}

void insert(MinHeap *heap, Player *player)
{
    if (heap->size < MAX_PLAYERS)
    {
        heap->data[heap->size] = player;
        int i = heap->size;
        heap->size++;

        while (i != 0 && heap->data[(i - 1) / 2]->score > heap->data[i]->score)
        {
            swap(&heap->data[i], &heap->data[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }
    else
    {
        if (player->score > heap->data[0]->score)
        {
            heap->data[0] = player;
            heapify(heap, 0);
        }
        else
        {
            free(player);
        }
    }
}

Player *extract_min(MinHeap *heap)
{
    if (heap->size == 0)
    {
        return NULL;
    }

    Player *root = heap->data[0];
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;

    heapify(heap, 0);

    return root;
}

void heapify(MinHeap *heap, int i)
{
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int smallest = i;

    if (left < heap->size && heap->data[left]->score < heap->data[smallest]->score)
    {
        smallest = left;
    }

    if (right < heap->size && heap->data[right]->score < heap->data[smallest]->score)
    {
        smallest = right;
    }

    if (smallest != i)
    {
        swap(&heap->data[i], &heap->data[smallest]);
        heapify(heap, smallest);
    }
}

void print_leaderboard(MinHeap *heap)
{
    Player *temp[MAX_PLAYERS];
    int temp_size = 0;

    printf("Rank\tPlayer ID\tScore\n");
    for (int i = 0; i < MAX_PLAYERS; i++)
    {
        Player *player = extract_min(heap);
        if (player)
        {
            temp[temp_size++] = player;
        }
    }

    for (int i = temp_size - 1; i >= 0; i--)
    {
        printf("%d\t%d\t\t%d\n", temp_size - i, temp[i]->id, temp[i]->score);
        free(temp[i]);
    }
}

