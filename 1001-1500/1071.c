int GCD(int a, int b){
    int t = a%b;
    while(t){
        a = b;
        b = t;
        t = a%b;
    }
    return b;
}

char * gcdOfStrings(char * str1, char * str2){
    int n1 = strlen(str1) ;
    int n2 = strlen(str2) ;
    char* ans;
    if(n1 == n2){
        if(strcmp(str1, str2) == 0){
            ans = malloc((n1+1) * sizeof(char));
            strcpy(ans, str1);
            return ans;
        }
        else
            return "";
    }    
    int gcd = GCD(n1, n2);
    for(int i = 1; i < n1/gcd; i++){
        if(strncmp(&str1[i*gcd], str1, gcd) != 0)
            goto fail;
    }
    for(int i = 1; i < n2/gcd; i++){
        if(strncmp(&str2[i*gcd], str2, gcd) != 0)
            goto fail;
    }
    ans = malloc((gcd+1) * sizeof(char));
    ans[gcd] ='\0';
    strncpy(ans, str1, gcd);
    return ans;
    
    fail:
       
    return "";
}
