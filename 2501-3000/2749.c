#pragma GCC optimize("O3, unroll-loops")
int makeTheIntegerZero(int num1, int num2) {
    long long x=num1;
    for(int k=1; ;k++){
        x-=num2;
        if (x<k) return -1;
        if (k>=__builtin_popcountll(x))
            return k;
    }
    return -1;
}
