int maximumSum(int* nums, int numsSize) {
    int max[82] = {0};
    int ans = -1;
    for (int i = 0; i < numsSize; i++) {
        int sum = 0, temp = nums[i];
        while (temp != 0) {
            sum += temp % 10;
            temp /= 10;
        }
        if (max[sum] != 0) ans = (ans > nums[i] + max[sum]) ? ans : nums[i] + max[sum];
        max[sum] = (max[sum] > nums[i]) ? max[sum] : nums[i];
    }
    return ans;
}
