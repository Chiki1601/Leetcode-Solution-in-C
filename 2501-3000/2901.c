#define MAX 1000

char grid[MAX][MAX];
int dp[MAX];
int par[MAX];

char can(char* word1, char* word2, int wi1, int wi2, int* groups) {
    int l1 = strlen(word1);
    int l2 = strlen(word2);

    if (l1 != l2 || groups[wi1] == groups[wi2]) {
        return 0;
    }

    int dif = 0;
    for (int i = 0; i < l1; ++i) {
        dif += (word1[i] != word2[i]);
    }

    return dif == 1;
}

char** getWordsInLongestSubsequence(char** words,
                                    int wordsSize,
                                    int* groups,
                                    int groupsSize,
                                    int* returnSize) {
    memset(grid, 0, sizeof(char) * MAX * MAX);
    for (int i = 0; i < wordsSize; ++i) {
        for (int j = i + 1; j < wordsSize; ++j) {
            grid[i][j] = grid[j][i] = can(words[i], words[j], i, j, groups);
        }
    }

    for (int i = 0; i < MAX; ++i) {
        dp[i] = 1;
        par[i] = -1;
    }
    int maxi = 0;
    for (int i = 0; i < wordsSize; ++i) {
        for (int j = 0; j < i; ++j) {
            if (grid[i][j] && (dp[i] < dp[j] + 1)) {
                dp[i] = dp[j] + 1;
                par[i] = j;
            }
            if (dp[i] > dp[maxi]) {
                maxi = i;
            }
        }
    }

    *returnSize = dp[maxi];

    char** ans = (char**)malloc(*returnSize * sizeof(char*));
    int ind = dp[maxi] - 1;
    while (maxi != -1) {
        ans[ind--] = words[maxi];
        maxi = par[maxi];
    }

    return ans;
}
