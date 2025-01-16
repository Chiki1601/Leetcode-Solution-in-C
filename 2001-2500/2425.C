int xorAllNums(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    int x1 = 0, x2 = 0;

    if (nums1Size % 2 != 0) {
        for (int i = 0; i < nums2Size; i++) {
            x2 ^= nums2[i];
        }
    }
    if (nums2Size % 2 != 0) {
        for (int i = 0; i < nums1Size; i++) {
            x1 ^= nums1[i];
        }
    }
    return x1 ^ x2;
}
