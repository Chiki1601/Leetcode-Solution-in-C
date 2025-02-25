int numOfSubarrays(int* arr, int arrSize) {
    long long oddCount = 0, prefixSum = 0;
    for(int i = 0; i < arrSize; i++) {
        prefixSum += arr[i];
        oddCount += prefixSum % 2;
    }
    oddCount += (arrSize - oddCount) * oddCount;
    return (int)(oddCount % 1000000007);
}
