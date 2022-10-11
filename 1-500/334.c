bool increasingTriplet(int* nums, int numsSize){
    int item1 = INT_MAX;
    int item2 = INT_MAX;

    for(int i = 0; i < numsSize; i++){
        if(nums[i] > item2)
            return true;
        
        else if(nums[i] < item1)
            item1 = nums[i];
        
        else if(nums[i] > item1 && nums[i] < item2)
            item2 = nums[i]; 
    }    
    return false;
}
