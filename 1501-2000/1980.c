typedef struct{
    char *str;
    UT_hash_handle hh;
} hElem;

char *backtrack(int idx, char *res, hElem **map, char **nums, int size) {
    hElem *t;
    char *localRes;
    if(idx == size) {
        HASH_FIND_STR(*map, res, t);
        return t ? NULL : res;
    }
    
    // place '0' at index idx and backtrack
    res[idx] = '0';
    localRes = backtrack(idx + 1, res, map, nums, size);
    if(localRes) return localRes;
    
    res[idx] = '1';
    localRes = backtrack(idx + 1, res, map, nums, size);
    if(localRes) return localRes;
    
    return NULL;
}

char * findDifferentBinaryString(char ** nums, int numsSize){
    hElem *map = NULL, *s;
    char *res = calloc(sizeof(char), strlen(nums[0]) + 1);
    memset(res, '0', sizeof(char) * strlen(nums[0]));
    
    // add all given strings to hash map for fast lookup
    for(int i = 0; i < numsSize; i++) {
        s = calloc(sizeof(hElem), 1);
        s->str = nums[i];
        HASH_ADD_STR(map, str, s);
    }
    
    int startIdx = 0;
    return backtrack(startIdx, res, &map, nums, numsSize);    
}
