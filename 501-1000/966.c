#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static char *strdup_c(const char *s) {
    size_t n = strlen(s);
    char *r = (char*)malloc(n+1);
    memcpy(r, s, n+1);
    return r;
}

unsigned long djb2(const char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = (unsigned char)*str++))
        hash = ((hash << 5) + hash) + c;
    return hash;
}

typedef struct Node {
    char *key;
    char *val;
    struct Node *next;
} Node;

typedef struct HashMap {
    int size;
    Node **buckets;
} HashMap;

HashMap* map_create(int size) {
    HashMap *m = (HashMap*)malloc(sizeof(HashMap));
    m->size = size;
    m->buckets = (Node**)calloc(size, sizeof(Node*));
    return m;
}

void map_put_if_absent(HashMap *m, const char *key, const char *val) {
    unsigned long h = djb2(key) % m->size;
    Node *cur = m->buckets[h];
    while (cur) {
        if (strcmp(cur->key, key) == 0) return; // already present
        cur = cur->next;
    }
    Node *n = (Node*)malloc(sizeof(Node));
    n->key = strdup_c(key);
    n->val = strdup_c(val);
    n->next = m->buckets[h];
    m->buckets[h] = n;
}

char* map_get(HashMap *m, const char *key) {
    unsigned long h = djb2(key) % m->size;
    Node *cur = m->buckets[h];
    while (cur) {
        if (strcmp(cur->key, key) == 0) return cur->val;
        cur = cur->next;
    }
    return NULL;
}

char* to_lower_dup(const char *s) {
    char *res = strdup_c(s);
    for (char *p = res; *p; ++p) *p = tolower((unsigned char)*p);
    return res;
}

char* mask_vowels_dup(const char *s) {
    char *res = strdup_c(s);
    for (char *p = res; *p; ++p) {
        char c = *p;
        if (c=='a'||c=='e'||c=='i'||c=='o'||c=='u') *p = 'a';
    }
    return res;
}


char** spellchecker(char** wordlist, int wordlistSize, char** queries, int queriesSize, int* returnSize) {
    int mapSize = 1;
    while (mapSize < wordlistSize * 4) mapSize <<= 1; // simple sizing
    if (mapSize < 16) mapSize = 16;

    HashMap *exactMap = map_create(mapSize);
    HashMap *lowerMap = map_create(mapSize);
    HashMap *vowelMap = map_create(mapSize);

    for (int i = 0; i < wordlistSize; ++i) {
        char *w = wordlist[i];
        map_put_if_absent(exactMap, w, w);
        char *wl = to_lower_dup(w);
        map_put_if_absent(lowerMap, wl, w);
        char *masked = mask_vowels_dup(wl);
        map_put_if_absent(vowelMap, masked, w);
        free(wl);
        free(masked);
    }

    char **res = (char**)malloc(sizeof(char*) * queriesSize);
    for (int i = 0; i < queriesSize; ++i) {
        char *q = queries[i];
        if (map_get(exactMap, q) != NULL) {
            res[i] = strdup_c(q);
            continue;
        }
        char *ql = to_lower_dup(q);
        char *v = map_get(lowerMap, ql);
        if (v != NULL) {
            res[i] = strdup_c(v);
            free(ql);
            continue;
        }
        char *qmask = mask_vowels_dup(ql);
        v = map_get(vowelMap, qmask);
        if (v != NULL) res[i] = strdup_c(v);
        else res[i] = strdup_c("");
        free(ql);
        free(qmask);
    }

    *returnSize = queriesSize;
    return res;
}
