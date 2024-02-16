static int debug = 0;

static void
dump_int_array(char *m, int *a, int size)
{
  int idx = 0;
  int cnt = 0;
  
  if (!debug)
    return;

  printf("%s\n", m);
  printf(" array= {");
  for (idx = 0; idx < size; idx++) {
    printf("%3d ", a[idx]);
    if (cnt++ == 7) {
      printf("\n         ");
      cnt = 0;
    }
  }
  printf("}\n");
}

static int
compf(const void *a, const void *b)
{
  return (*(int *)a - *(int *)b);
}

static int
massage_num_array(int *arr, int size)
{
  int idx1;  /* pointer behind */
  int idx2;  /* pointer forward */
  int val;

  dump_int_array("\nORIGINAL:", arr, size);
  qsort(arr, size, sizeof (int), compf);
  dump_int_array("ORIGINAL sorted:", arr, size);

  idx1 = 0;
  idx2 = 1;
  val = arr[idx1];
  arr[idx1] = 1;
  
  while (idx2 < size) {
    if (val == arr[idx2])
      ++arr[idx1];
    else {
      val = arr[idx2];
      arr[++idx1] = 1;
    }
    ++idx2;
  }

  for (idx2 = idx1 + 1; idx2 < size; idx2++)
    arr[idx2] = -1;
  
  dump_int_array("ORIGINAL occurrences:", arr, size);
  qsort(arr, idx1+1, sizeof (int), compf);
  dump_int_array("ORIGINAL sorted occurerences:", arr, size);
  
  return (idx1+1);
}

static int
LeastNumOfUniqueInts(int *n, int num_items, int k)
{
  int o_size = num_items;
  int idx = 0;
  for (idx = 0; idx < o_size; idx++) {
    if (n[idx] <= k) {
      --num_items;
      k = k - n[idx];
    } else
      break;
  }
  return (num_items);
}

int
findLeastNumOfUniqueInts(int *arr, int arrSize, int k)
{
  int nums;
  int ret;
  if (arrSize <= k)
    return (0);

  nums = massage_num_array(arr, arrSize);
  ret = LeastNumOfUniqueInts(arr, nums, k);

  if (debug)
    printf("RETURNING %d\n", ret);
  return (ret);
}
