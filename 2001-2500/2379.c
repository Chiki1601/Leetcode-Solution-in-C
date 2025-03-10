int minimumRecolors(char* blocks, int k) {
    int min = k;
    for(int i = 0; i <= strlen(blocks)-k; i++){
        int count = 0;
        for(int j = i; j < i+k; j++){
            if(blocks[j] == 'W')
                count++;
        }
        min = min<count?min:count;
    }
    return min;
}
