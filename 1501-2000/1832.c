bool checkIfPangram(char * s){
    bool *arr = (bool *)calloc(26,sizeof(bool));
    for(int i = 0 ; s[i] ; i++) arr[s[i]-'a'] = true;
    for(int i = 0 ; i < 26 ; i++)
        if(!arr[i]) return false;
    return true;
}
