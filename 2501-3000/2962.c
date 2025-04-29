long long countSubarrays(int* nums, int numsSize, int k) {
    int maxVal = 0;
    for (int i = 0; i < numsSize; i++) {
        if (maxVal < nums[i]) {
            maxVal = nums[i];
        }
    }

    int count = 0;
    long res = 0;
    int left = 0;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] == maxVal) {
            count++;
        }

        while (count >= k) {
            if (nums[left++] == maxVal) {
                count--;
            }
        }

        res += left;
    }

    return res;
}
