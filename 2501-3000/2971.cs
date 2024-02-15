int cmpFunc(const void* a, const void* b){ return *(int*)b - *(int*)a; }

long long largestPerimeter(int* nums, int numsSize) {
    long long result=-1, sums[numsSize-1];

    qsort(nums, numsSize, sizeof(int), cmpFunc);
    sums[numsSize-2]=nums[numsSize-2]+nums[numsSize-1];
    for(int i=numsSize-3; i>=0; i--){
        sums[i]=nums[i]+sums[i+1];
        if(nums[i]<sums[i+1]){ result=sums[i]; }
    }

    return result;
}
