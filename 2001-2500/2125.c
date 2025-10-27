#pragma GCC optimize("O3", "unroll-loops")
int numberOfBeams(char** bank, int bankSize) {
    int ans=0, prev=0;
    char *row;
    for (register int i=0; i<bankSize; i++){
        row=bank[i];
        int dev=0;
        for(register int j=0; row[j]!='\0'; j++)
            dev+=(row[j]=='1');
        if (dev>0){
            ans+=dev*prev;
            prev=dev;
        }   
    }
    return ans;
}

        
