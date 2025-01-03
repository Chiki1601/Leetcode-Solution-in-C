int waysToSplitArray(int* nums, int numsSize) {
    long long leftSum = 0, rightSum = 0;
    for (int i = 0; i < numsSize; i++) {
        rightSum += nums[i];
    }

    int validSplits = 0;
    for (int i = 0; i < numsSize - 1; i++) {
        leftSum += nums[i];
        rightSum -= nums[i];
        if (leftSum >= rightSum) {
            validSplits++;
        }
    }

    return validSplits;
}
