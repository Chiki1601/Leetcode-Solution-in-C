void sortColors(int* nums, int numsSize){
    int i, c[3];
    
    for (i = c[0] = c[1] = c[2] = 0; i < numsSize; i++)
        c[nums[i]]++;
    
    for (i = 0; i < c[0]; i++)
        nums[i] = 0;
    while (i < c[0] + c[1])
        nums[i++] = 1;
    while (i < numsSize)
        nums[i++] = 2;}
