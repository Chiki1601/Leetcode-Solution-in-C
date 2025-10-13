/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** removeAnagrams(char** words, int wordsSize, int* returnSize) {
    char** res = (char**)malloc(wordsSize * sizeof(char*));
    res[0] = words[0];
    int idx = 1;
    
    for (int i = 1; i < wordsSize; i++) {
        int freq1[26] = {0}, freq2[26] = {0};
        
        char* lastWord = res[idx - 1];
        for (int j = 0; lastWord[j]; j++) {
            freq1[lastWord[j] - 'a']++;
        }
        for (int j = 0; words[i][j]; j++) {
            freq2[words[i][j] - 'a']++;
        }
        
        int isAnagram = 1;
        for (int j = 0; j < 26; j++) {
            if (freq1[j] != freq2[j]) {
                isAnagram = 0;
                break;
            }
        }
        
        if (!isAnagram) {
            res[idx++] = words[i];
        }
    }
    
    *returnSize = idx;
    return res;
}
