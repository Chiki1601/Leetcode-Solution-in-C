/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findBall(int** grid, int gridSize, int* gridColSize, int* returnSize){

    int * retarray = (int*) malloc(sizeof(int) * *gridColSize);
    int retidx = 0;
    
    for (int i = 0; i < *gridColSize; i++)
    {
        int c = i;
        int r = 0;
        for (; r < gridSize; r++)
        {
        
            if (c < (*gridColSize)-1)
                if (grid[r][c] == 1 && grid[r][c+1] == -1) break;

            if (c >0)
                if (grid[r][c] == -1 && grid[r][c-1] == 1) break;
          
            if (grid[r][c] == 1) c++;
            else c--;
            
            // If column not in range break
            if (c < 0 || c > (*gridColSize)-1) break;          

        }
        
        if (r != gridSize) retarray[retidx] = -1; 
        else retarray[retidx] = c;
        retidx++;      
    }
    
    *returnSize = retidx;
    return retarray;
    

}
