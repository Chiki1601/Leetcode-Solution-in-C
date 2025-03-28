/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Structure for coordinates (first, second) equivalent to pair<int, int>
typedef struct {
    int first;
    int second;
} Pair;

// Structure for heap entry (val, (x, y)) equivalent to pair<int, pair<int, int>>
typedef struct {
    int value;
    Pair coord;
} HeapEntry;

// Min-heap structure
typedef struct {
    HeapEntry* data;
    int size;
    int capacity;
} MinHeap;

// Directions array (up, down, left, right)
int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

// Heap functions
MinHeap* createHeap(int capacity) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->data = (HeapEntry*)malloc(capacity * sizeof(HeapEntry));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void swap(HeapEntry* a, HeapEntry* b) {
    HeapEntry temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyUp(MinHeap* heap, int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap->data[parent].value > heap->data[index].value) {
            swap(&heap->data[parent], &heap->data[index]);
            index = parent;
        } else
            break;
    }
}

void heapifyDown(MinHeap* heap, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < heap->size && heap->data[left].value < heap->data[smallest].value)
        smallest = left;
    if (right < heap->size && heap->data[right].value < heap->data[smallest].value)
        smallest = right;

    if (smallest != index) {
        swap(&heap->data[index], &heap->data[smallest]);
        heapifyDown(heap, smallest);
    }
}

void push(MinHeap* heap, int value, int r, int c) {
    if (heap->size == heap->capacity) return;
    heap->data[heap->size].value = value;
    heap->data[heap->size].coord.first = r;
    heap->data[heap->size].coord.second = c;
    heapifyUp(heap, heap->size);
    heap->size++;
}

HeapEntry pop(MinHeap* heap) {
    HeapEntry top = heap->data[0];
    heap->size--;
    heap->data[0] = heap->data[heap->size];
    heapifyDown(heap, 0);
    return top;
}

bool isEmpty(MinHeap* heap) {
    return heap->size == 0;
}

void freeHeap(MinHeap* heap) {
    free(heap->data);
    free(heap);
}

// Comparison function for qsort
int compare(const void* a, const void* b) {
    return ((Pair*)a)->first - ((Pair*)b)->first;
}


int* maxPoints(int** grid, int gridSize, int* gridColSize, int* queries, int queriesSize, int* returnSize) {
    int n = gridSize;
    int m = gridColSize[0];
    int k = queriesSize;

    int* ans = (int*)calloc(k, sizeof(int));
    *returnSize = k;

    bool** vis = (bool**)malloc(n * sizeof(bool*));

    for (int i = 0; i < n; i++)
        vis[i] = (bool*)calloc(m, sizeof(bool));

    MinHeap* pq = createHeap(n * m);

    Pair* helpful = (Pair*)malloc(k * sizeof(Pair));

    for (int i = 0; i < k; i++) {
        helpful[i].first = queries[i];
        helpful[i].second = i;
    }
    qsort(helpful, k, sizeof(Pair), compare);

    push(pq, grid[0][0], 0, 0);
    vis[0][0] = true;
    int cnt = 0;

    for (int i = 0; i < k; i++) {
        int thresh = helpful[i].first;
        int idx = helpful[i].second;

        while (!isEmpty(pq) && pq->data[0].value < thresh) {
            HeapEntry top = pop(pq);
            cnt++;
            int val = top.value;
            int r = top.coord.first;
            int c = top.coord.second;

            for (int d = 0; d < 4; d++) {
                int nr = r + dirs[d][0];
                int nc = c + dirs[d][1];
                if (nr >= 0 && nr < n && nc >= 0 && nc < m && !vis[nr][nc]) {
                    vis[nr][nc] = true;
                    push(pq, grid[nr][nc], nr, nc);
                }
            }
        }
        ans[idx] = cnt;
    }

    for (int i = 0; i < n; i++)
        free(vis[i]);
        
    free(vis);
    free(helpful);
    freeHeap(pq);

    return ans;
}

    
