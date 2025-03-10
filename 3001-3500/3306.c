#include <stdbool.h>
#include <stdio.h>
#include <string.h>

bool isVowel(char c) {
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

long long atLeastK(char* word, int k) {
    int n = strlen(word);
    long long ans = 0;
    int consonants = 0;
    int left = 0;
    int vowelMap[26] = {0};
    int vowelCount = 0;

    for (int right = 0; right < n; right++) {
        if (isVowel(word[right])) {
            vowelMap[word[right] - 'a']++;
            if (vowelMap[word[right] - 'a'] == 1) {
                vowelCount++;
            }
        } else {
            consonants++;
        }

        while (vowelCount == 5 && consonants >= k) {
            ans += n - right;
            if (isVowel(word[left])) {
                vowelMap[word[left] - 'a']--;
                if (vowelMap[word[left] - 'a'] == 0) {
                    vowelCount--;
                }
            } else {
                consonants--;
            }
            left++;
        }
    }
    return ans;
}

long long countOfSubstrings(char* word, int k) {
    return atLeastK(word, k) - atLeastK(word, k + 1);
}
