int maxScoreSightseeingPair(int* values, int valuesSize) {
  int max = 0, score = *values; 
  for (++values, --valuesSize; valuesSize; ++values, --valuesSize) {
    --score;
    if (score + *values > max) max = score + *values;
    if (*values > score) score = *values;
  }
  return max;
}
