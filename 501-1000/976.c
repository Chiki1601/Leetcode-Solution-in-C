int cmpFunc(const int* a, const int* b)
{
    return (*b - *a);
}

int largestPerimeter(int* A, int ASize) {
    qsort(A, ASize, sizeof(int), cmpFunc);
    int i, j, k;
    for(i = 0; i < ASize - 2; i++)
    {
        if(A[i+2] + A[i+1] > A[i])
        {
            return (A[i+2] + A[i+1] + A[i]);
        }
    }
    return 0;
}
