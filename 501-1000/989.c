int* addToArrayForm(int* A, int ASize, int K, int* returnSize)
{
    int i, j, k, c, ksize, rsize;
    int *karr, *res;
    
    for (i = K, ksize = 0; i > 0; i /= 10)
        ksize++;

    karr = malloc(sizeof(int) * ksize);
    
    for (i = ksize -1, k = K; i >= 0; k /= 10)
        karr[i--] = k % 10;
    
    rsize = ksize > ASize ? ksize : ASize;
    res = malloc(sizeof(int) * (++rsize));
    
    for (k = rsize - 1, i = ASize, j = ksize, c = 0; k >= 0; k--) {
        c += i > 0 ? A[--i] : 0;
        c += j > 0 ? karr[--j] : 0;
        res[k] = c % 10;
        c /= 10;
    }
    
    if (res[0] == 0)
        memmove(res, res + 1, sizeof(int) * (--rsize));
    
    *returnSize = rsize;
    
    free(karr);

    return res;
}
