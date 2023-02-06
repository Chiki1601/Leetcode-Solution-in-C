int* shuffle(int* nums, int numsSize, int n, int* returnSize) {
    *returnSize = numsSize;
    int* ans = (int*) malloc(numsSize * sizeof(int));
    int k = 0;
    for(int i = 0; i < numsSize; i++) {
        ans[i] = (i % 2 == 0) ? nums[k++] : nums[n++];
    }
    return ans;
}
