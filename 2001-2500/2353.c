#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FOOD 20000

typedef struct {
    char *food;
    char *cuisine;
    int rating;
} FoodInfo;

typedef struct HeapNode {
    int rating;       // Store rating positively here for easier comparison
    char *food;
} HeapNode;

typedef struct Heap {
    HeapNode *nodes;
    int size;
    int capacity;
} Heap;

typedef struct {
    FoodInfo *foodMap;   // food index to food info
    int foodCount;
    
    // Map food string to index
    // We'll use a simple hash map for food name -> index
    // Using a custom hash map for strings
    struct HashNode {
        char *key;
        int val;
        struct HashNode *next;
    } **foodHash;
    
    int hashSize;
    
    // For each cuisine, maintain a max heap of foods
    struct CuisineHeap {
        char *cuisine;
        Heap *heap;
        struct CuisineHeap *next;
    } *cuisineList;
} FoodRatings;

unsigned int hashFunc(char *str, int size) {
    unsigned int hash = 5381;
    while (*str) {
        hash = ((hash << 5) + hash) + (*str);
        str++;
    }
    return hash % size;
}

// Insert into foodHash map
void insertFoodHash(FoodRatings *obj, char *key, int val) {
    unsigned int h = hashFunc(key, obj->hashSize);
    struct HashNode *node = (struct HashNode*)malloc(sizeof(struct HashNode));
    node->key = key;
    node->val = val;
    node->next = obj->foodHash[h];
    obj->foodHash[h] = node;
}

// Search foodHash map
int searchFoodHash(FoodRatings *obj, char *key) {
    unsigned int h = hashFunc(key, obj->hashSize);
    struct HashNode *cur = obj->foodHash[h];
    while (cur) {
        if (strcmp(cur->key, key) == 0)
            return cur->val;
        cur = cur->next;
    }
    return -1;
}

// Free foodHash map
void freeFoodHash(FoodRatings *obj) {
    for (int i = 0; i < obj->hashSize; i++) {
        struct HashNode *cur = obj->foodHash[i];
        while (cur) {
            struct HashNode *tmp = cur;
            cur = cur->next;
            free(tmp);
        }
    }
    free(obj->foodHash);
}

// Create a heap
Heap* createHeap(int capacity) {
    Heap *heap = (Heap*)malloc(sizeof(Heap));
    heap->nodes = (HeapNode*)malloc(sizeof(HeapNode)*capacity);
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void freeHeap(Heap *heap) {
    free(heap->nodes);
    free(heap);
}

// Compare function for heap ordering
// We want max rating, if tie lex smaller food.
// So order by rating descending, then food ascending.
int cmpHeapNode(HeapNode *a, HeapNode *b) {
    if (a->rating != b->rating)
        return a->rating - b->rating; // max rating => bigger rating is "larger"
    return strcmp(b->food, a->food); // lex smaller => a->food < b->food => positive if b->food > a->food
}

// Heapify up
void heapifyUp(Heap *heap, int idx) {
    while (idx > 0) {
        int parent = (idx - 1) / 2;
        if (cmpHeapNode(&heap->nodes[idx], &heap->nodes[parent]) > 0) {
            // Swap
            HeapNode tmp = heap->nodes[idx];
            heap->nodes[idx] = heap->nodes[parent];
            heap->nodes[parent] = tmp;
            idx = parent;
        } else {
            break;
        }
    }
}

// Heapify down
void heapifyDown(Heap *heap, int idx) {
    int left, right, largest;
    while (1) {
        left = idx * 2 + 1;
        right = idx * 2 + 2;
        largest = idx;

        if (left < heap->size && cmpHeapNode(&heap->nodes[left], &heap->nodes[largest]) > 0)
            largest = left;
        if (right < heap->size && cmpHeapNode(&heap->nodes[right], &heap->nodes[largest]) > 0)
            largest = right;

        if (largest == idx)
            break;

        HeapNode tmp = heap->nodes[idx];
        heap->nodes[idx] = heap->nodes[largest];
        heap->nodes[largest] = tmp;
        idx = largest;
    }
}

void heapPush(Heap *heap, int rating, char *food) {
    if (heap->size == heap->capacity) {
        heap->capacity *= 2;
        heap->nodes = (HeapNode*)realloc(heap->nodes, sizeof(HeapNode)*heap->capacity);
    }
    heap->nodes[heap->size].rating = rating;
    heap->nodes[heap->size].food = food;
    heapifyUp(heap, heap->size);
    heap->size++;
}

HeapNode heapTop(Heap *heap) {
    return heap->nodes[0];
}

void heapPop(Heap *heap) {
    heap->nodes[0] = heap->nodes[heap->size-1];
    heap->size--;
    heapifyDown(heap, 0);
}

// Find or create CuisineHeap by cuisine string
Heap* getCuisineHeap(FoodRatings *obj, char *cuisine) {
    struct CuisineHeap *cur = obj->cuisineList;
    while (cur) {
        if (strcmp(cur->cuisine, cuisine) == 0)
            return cur->heap;
        cur = cur->next;
    }
    // Create new cuisine heap
    struct CuisineHeap *newCuisine = (struct CuisineHeap*)malloc(sizeof(struct CuisineHeap));
    newCuisine->cuisine = cuisine;
    newCuisine->heap = createHeap(16);
    newCuisine->next = obj->cuisineList;
    obj->cuisineList = newCuisine;
    return newCuisine->heap;
}

FoodRatings* foodRatingsCreate(char** foods, int foodsSize, char** cuisines, int cuisinesSize, int* ratings, int ratingsSize) {
    FoodRatings *obj = (FoodRatings*)malloc(sizeof(FoodRatings));
    obj->foodCount = foodsSize;
    obj->foodMap = (FoodInfo*)malloc(sizeof(FoodInfo)*foodsSize);
    obj->hashSize = 40000; // enough for 2*10^4
    obj->foodHash = (struct HashNode**)calloc(obj->hashSize, sizeof(struct HashNode*));
    obj->cuisineList = NULL;

    for (int i = 0; i < foodsSize; i++) {
        obj->foodMap[i].food = foods[i];
        obj->foodMap[i].cuisine = cuisines[i];
        obj->foodMap[i].rating = ratings[i];
        insertFoodHash(obj, foods[i], i);
        // Push into cuisine heap
        Heap *heap = getCuisineHeap(obj, cuisines[i]);
        heapPush(heap, ratings[i], foods[i]);
    }
    return obj;
}

void foodRatingsChangeRating(FoodRatings* obj, char* food, int newRating) {
    int idx = searchFoodHash(obj, food);
    if (idx == -1) return;
    obj->foodMap[idx].rating = newRating;
    // Push new rating to heap of corresponding cuisine
    Heap *heap = getCuisineHeap(obj, obj->foodMap[idx].cuisine);
    heapPush(heap, newRating, food);
}

char* foodRatingsHighestRated(FoodRatings* obj, char* cuisine) {
    Heap *heap = getCuisineHeap(obj, cuisine);
    while (heap->size > 0) {
        HeapNode top = heapTop(heap);
        int idx = searchFoodHash(obj, top.food);
        if (idx == -1) {
            // Food not found, pop and continue
            heapPop(heap);
            continue;
        }
        if (obj->foodMap[idx].rating == top.rating) {
            return top.food;
        } else {
            // stale entry, pop and continue
            heapPop(heap);
        }
    }
    return NULL; // shouldn't happen per constraints
}

void foodRatingsFree(FoodRatings* obj) {
    freeFoodHash(obj);
    free(obj->foodMap);
    // Free cuisine heaps
    struct CuisineHeap *cur = obj->cuisineList;
    while (cur) {
        struct CuisineHeap *tmp = cur;
        cur = cur->next;
        freeHeap(tmp->heap);
        free(tmp);
    }
    free(obj);
}
