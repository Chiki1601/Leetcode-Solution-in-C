/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** getLongestSubsequence(
    char** words, int wordsSize,
    int* groups, int groupsSize,
    int* returnSize
) {
    char** result=malloc(wordsSize*sizeof(char*));
    int lastGroup=groups[0]; result[0]=words[0];
    *returnSize=1;

    for(int i=1; i<wordsSize; i++) {
        if(groups[i]==lastGroup){ continue; }
        result[(*returnSize)++]=words[i];
        lastGroup=groups[i];
    }

    return result;
}
