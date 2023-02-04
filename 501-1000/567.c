#define ALPHABET    26
bool checkInclusion(char * s1, char * s2){
    int l1 = strlen(s1), l2 = strlen(s2), cnt = 0, letter;
    
    if(l1 > l2) return false;
    int s1Cnt[ALPHABET] = {0}, s2Cnt[ALPHABET] = {0};
    
    // add l1 characters to both count maps
    for(int i = 0; i < l1; i++) {
        s1Cnt[s1[i] - 'a']++;   s2Cnt[s2[i] - 'a']++;
    }
    
    // number of character count matches in both strings count map
    cnt = 0;
    for(int i = 0; i < ALPHABET; i++) 
        if(s1Cnt[i] == s2Cnt[i]) cnt++;
    
    // check all remaining characters in s2 by moving the window
    for(int l = 0, r = l1; r < l2; r++,l++) {
        if(cnt == ALPHABET) return true;
        
        // increase window by adding char at right
        letter = s2[r] - 'a';
        s2Cnt[letter]++;
        // if by adding this letter count matches increment count else decrement
        if(s2Cnt[letter] == s1Cnt[letter]) cnt++;
        else if(s2Cnt[letter] == s1Cnt[letter] + 1) cnt--;  // was equal before including right char
        
        // decrease window by adding char at left
        letter = s2[l] - 'a';
        s2Cnt[letter]--;
        // if by removing this letter count matches increment count else decrement
        if(s2Cnt[letter] == s1Cnt[letter]) cnt++;
        else if(s2Cnt[letter] == s1Cnt[letter] - 1) cnt--;  // was equal before removing left char
    }
    return cnt == ALPHABET;
}
