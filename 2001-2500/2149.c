/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* rearrangeArray(int* nums, int numsSize, int* returnSize){
    int* ans = malloc(sizeof(int)*numsSize);
    *returnSize = numsSize;
    int a = 0;
    int b = 1;
    for (int i = 0 ; i < numsSize ; i++){
        if (nums[i] > 0){
            ans[a] = nums[i];
            a += 2;
        } else {
            ans[b] = nums[i];
            b += 2;
        }
    }
    return ans;
}
