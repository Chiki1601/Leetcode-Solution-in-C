#define max(a, b) ((a) > (b) ? (a) : (b))

char** wordSubsets(char** words1, int words1Size, char** words2, int words2Size, int* returnSize) {
    int maxCharFreq[26] = {0};
    int tempCharFreq[26];

    for (int i = 0; i < words2Size; ++i) {
        memset(tempCharFreq, 0, sizeof(tempCharFreq));
        for (int j = 0; words2[i][j] != '\0'; ++j) {
            tempCharFreq[words2[i][j] - 'a']++;
        }
        for (int i = 0; i < 26; ++i) {
            maxCharFreq[i] = max(maxCharFreq[i], tempCharFreq[i]);
        }
    }

    char** universalWords = (char**)malloc(words1Size * sizeof(char*));
    *returnSize = 0;

    for (int i = 0; i < words1Size; ++i) {
        memset(tempCharFreq, 0, sizeof(tempCharFreq));
        for (int j = 0; words1[i][j] != '\0'; ++j) {
            tempCharFreq[words1[i][j] - 'a']++;
        }

        int isUniversal = 1;
        for (int j = 0; j < 26; ++j) {
            if (maxCharFreq[j] > tempCharFreq[j]) {
                isUniversal = 0;
                break;
            }
        }

        if (isUniversal) {
            universalWords[*returnSize] = words1[i];
            (*returnSize)++;
        }
    }

    return universalWords;
}
