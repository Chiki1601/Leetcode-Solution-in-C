int longestNiceSubarray(int* nums, int numsSize) {
    int usedBits = 0, left = 0, ans = 0;  

    for(int right = 0; right < numsSize; ++right){
        while((usedBits & nums[right]) != 0){
            usedBits ^= nums[left++];
        }
        usedBits |= nums[right];

        ans = ans > right-left+1 ? ans : right-left+1;
    }

    return ans;
}
