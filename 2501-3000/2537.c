typedef struct _IntHashMapEntry{
    int key;
    int value;
}IntHashMapEntry;
typedef struct _IntHashMap{
    IntHashMapEntry** entries;
    unsigned capacity;
    // struct _IntHashMap * (*createHashMap)(unsigned size);
    unsigned (*calculateHashValue)(struct _IntHashMap* map, const int key);
    unsigned (*getOrDefault)(struct _IntHashMap*map, const int key);
    int (*existInTable)(struct _IntHashMap* map, const int key);
    void (*insertEntry)(struct _IntHashMap* map, const int key, const int value);
    

}IntHashMap;
IntHashMap* createIntHashMap(unsigned size);
void freeIntHashMap(IntHashMap*map);
static unsigned calculateHashValue(IntHashMap* map, const int key){
    unsigned hash = (unsigned)key;   // Convert key to unsigned for bitwise operations
    hash ^= (hash >> 16);           // XOR upper and lower bits for better mixing
    hash *= 0x45d9f3b;              // Multiply with a prime number for spreading bits
    hash ^= (hash >> 16);           // Additional mixing step
    return hash % map->capacity;    // Constrain to the hash table capacity
}
static unsigned getOrDefault(IntHashMap*map, const int key){
    unsigned hash=map->calculateHashValue(map, key);
    while(map->entries[hash]!=NULL){
        if(map->entries[hash]->key==key){
            return map->entries[hash]->value;
        }
        hash++;
        if(hash==map->capacity){
            hash=0;
        }
    }
    return 0;
}
static int existInTable(IntHashMap* map, const int key){
    unsigned hash=map->calculateHashValue(map, key);
    while(map->entries[hash]!=NULL){
        if(map->entries[hash]->key==key){
            return 1;
        }
        hash++;
        if(hash==map->capacity){
            hash=0;
        }
    }
    return 0;
}
static void insertEntry(IntHashMap* map, const int key, const int value){
    unsigned hash=map->calculateHashValue(map, key);
    while(map->entries[hash]!=NULL){
        if(map->entries[hash]->key==key){
            map->entries[hash]->value=value;
            return ;
        }
        hash++;
        if(hash==map->capacity){
            hash=0;
        }
    }
    map->entries[hash]=malloc(sizeof(IntHashMapEntry));
    map->entries[hash]->key=key;
    map->entries[hash]->value=value;
}


IntHashMap* createIntHashMap(unsigned size){
    IntHashMap * map=malloc(sizeof(IntHashMap));
    map->capacity=2*size;
    map->entries=malloc(sizeof(IntHashMapEntry*)*map->capacity);
    for(unsigned i=0; i<map->capacity; i++){
        map->entries[i]=NULL;
    }
    // map->createHashMap=createHashMap;
    
    map->calculateHashValue=calculateHashValue;
    map->existInTable=existInTable;
    map->getOrDefault=getOrDefault;
    map->insertEntry=insertEntry;
    // map->printHashMap=printHashMap;
    return map;
}

void freeIntHashMap(IntHashMap*map){
    for(unsigned i=0; i<map->capacity; i++){
        if(map->entries[i]!=NULL){
            free(map->entries[i]);
        }
    }
    free(map->entries);
    free(map);
    // printf("successfully free int map\n");
}

long long countGood(int* nums, int numsSize, int k) {
    IntHashMap* map=createIntHashMap(numsSize);
    long long res=0;
    int l=0;
    long long window_count = 0;
    for(int r=0; r<numsSize; r++){
        int val = map->getOrDefault(map, nums[r]);
        window_count += val;
        map->insertEntry(map, nums[r], val + 1);

        while (window_count >= k) {
            res += numsSize - r;
            int count_left = map->getOrDefault(map, nums[l]);
            window_count -= count_left - 1;
            map->insertEntry(map, nums[l], count_left - 1);
            l++;
        }
    }
    freeIntHashMap(map);
    return res;
}
