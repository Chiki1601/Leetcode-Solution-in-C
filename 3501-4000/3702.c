int longestSubsequence(int* nums, int numsSize) {
    int allZero = 1;
    int xorSum = 0;
    for (int i = 0; i < numsSize; ++i) {
        xorSum ^= nums[i];
        if (nums[i] != 0) {
            allZero = 0;
        }
    }
    if (allZero) return 0;
    return xorSum != 0 ? numsSize : numsSize - 1;
}
