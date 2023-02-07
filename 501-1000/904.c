int totalFruit(int* fruits, int fruitsSize){
    int n = fruitsSize;
    int type = 0;
    int* hash = calloc(n , sizeof(int) );
    int left = 0, right = 0;
    while(right < fruitsSize){
        if(hash[fruits[right]] == 0){
            type++;
        }
        hash[fruits[right]]++;
        right++;
        if(type > 2){
            if(hash[fruits[left]] == 1){
                type--;
            }
            hash[fruits[left]]--;
            left++;
        }
    }
    free(hash);
    return right - left ;
}
