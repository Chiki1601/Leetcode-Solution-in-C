int canCompleteCircuit(int* gas, int gasSize, int* cost, int costSize) 
{
    int i;
    int s, ret;//s: the start index of current sub-sequence; ret: the return value
    int diff[gasSize];//store (gas[i] - cost[i])
    int max = 0;//the largest and of the sub-sequence of diff[i]
    int sum = 0;//the and of current sub-sequence
    
    for(i=0; i<gasSize; i++)//get the difference between gas[i] and cost[i]
        diff[i] = gas[i] - cost[i];
        
    s = 0;

    for(i=0; s<gasSize; i++)//get the max and of diff
    {
        if(i>=s+gasSize)
            break;
            
        if(diff[i%gasSize]>=0)
        {
            sum += diff[i%gasSize];
            if(sum>max)
            {
                max = sum;
                ret = s;
            }
        }
        else
        {
            if(sum+diff[i%gasSize]<0)
            {
                s = i+1;
                sum = 0;
            }
            else
            {
                sum += diff[i%gasSize];
            }
        }
        
    }
    
    //if the sum which begin with index ret is not always >= 0, return -1
    sum = 0;
    for(i=ret; i!=ret+gasSize; i++)
    {
        sum += diff[i%gasSize];
        if(sum<0)
            return -1;
    }
    
    return ret;
}
