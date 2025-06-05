int find(int* p, int x) {
    if (p[x] != x) {
        p[x] = find(p, p[x]);
    }
    return p[x];
}
char* smallestEquivalentString(char* s1, char* s2, char* baseStr) {

    int p[26] = {0};
    for (int i = 0; i < 26; i++) {
        p[i] = i;
    }

    const int n = strlen(s1);
    for (int i = 0; i < n; i++) {
        const int a = s1[i] - 'a';
        const int b = s2[i] - 'a';
        const int pa = find(p, a);
        const int pb = find(p, b);
        if (pa < pb) 
            p[pb] = pa; 
        else 
            p[pa] = pb;
    }
    
    const int m = strlen(baseStr);
    char* result = (char*)calloc(m + 1, sizeof(char));

    for (int i = 0; i < m; i++) {
        result[i] = (char)(find(p, baseStr[i] - 'a') + 'a');
    }
    return result;
}
