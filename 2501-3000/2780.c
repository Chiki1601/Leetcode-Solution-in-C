int minimumIndex(int* nums, int numsSize) {
    int count = 1, total = 0;
    int x = nums[0];
    for(int i = 1; i < numsSize; i++) {
        if(nums[i] == x) count++;
        else count--;
        if(!count) {
            count = 1;
            x = nums[i];
        }
    }

    count = 0;

    for(int i = 0; i < numsSize; i++) {
        if(nums[i] == x) total++;
    }
    for(int i = 0; i < numsSize - 1; i++) {
        if(nums[i] == x) count++;
        if((count > (i+1) / 2) && ((total - count) > (numsSize - i - 1) / 2)) return i;
    }

    return -1;
}
