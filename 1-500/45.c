int jump(int* nums, int numsSize) {
    int pos = 0;
    int c = 0;
    while(pos < numsSize-1) {
        int next_pos=-1;
        if(pos+nums[pos]<numsSize-1) {
            // if we can not directly jump to the last element
            // Find out the best one
            for(int i=1; i<=nums[pos]; i++) {
                if(next_pos == -1 || (pos+i<numsSize && nums[next_pos]+(next_pos-pos) <= nums[pos+i]+i))
                    next_pos = pos+i;
            }
        } else
            next_pos = pos+nums[pos];
        pos = next_pos;
        c++;
    }
    return c;
}
