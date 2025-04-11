// 10 < n < 100, n = 11*k
// 1000 < n < 10000, digit3+digit2 = digit1+digit0
int countSymmetricIntegers(int low, int high) {
  int rs = 0;
  for (int i = low; i <= high; i++) {
    if (i > 10 && i < 100) {
      if (i % 11 == 0)
        rs++;
    } else if (i > 1000 && i < 10000) {
      if (i / 1000 + i / 100 % 10 == i / 10 % 10 + i % 10)
        rs++;
    }
  }
  return rs;
}
