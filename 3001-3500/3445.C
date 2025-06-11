static int upper_bound_int(const int *arr, int len, int key) {
    int lo = 0, hi = len;
    while (lo < hi) {
        int mid = lo + ((hi - lo) >> 1);
        if (arr[mid] <= key) {
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }
    return lo;
}

int maxDifference(char *s, int k) {
    int n = (int)strlen(s);
    if (n == 0 || k > n) return -1;

    int (*freq)[5] = malloc(sizeof(int[5]) * n);
    if (!freq) return -1;
    int present[5] = {0};
    for (int i = 0; i < n; i++) {
        int d = s[i] - '0';
        if (i == 0) memset(freq[i], 0, sizeof(int) * 5);
        else memcpy(freq[i], freq[i - 1], sizeof(int) * 5);
        freq[i][d]++;
        present[d] = 1;
    }

    int ans = INT_MIN;
    for (int a = 0; a < 5; a++) {
        if (!present[a]) continue;
        for (int b = 0; b < 5; b++) {
            if (!present[b] || a == b) continue;

            int *idx_lists[4], *val_lists[4], sz[4];
            for (int st = 0; st < 4; st++) {
                idx_lists[st] = malloc(sizeof(int) * n);
                val_lists[st] = malloc(sizeof(int) * n);
                sz[st] = 0;
            }

            int odd = 0, even = 0;
            for (int i = 0; i < n; i++) {
                int d = s[i] - '0';
                if (d == a) odd++;
                else if (d == b) even++;
                if ((odd & 1) && (even & 1) == 0 && (i + 1) >= k && even > 0) {
                    int diff = odd - even;
                    if (diff > ans) ans = diff;
                }

                int key1 = ((odd % 2 == 0) ? 1 : 0) << 1 | ((even % 2 == 0) ? 0 : 1);
                if (sz[key1] > 0) {
                    int limit = i - k;
                    if (limit >= 0) {
                        int pos = upper_bound_int(idx_lists[key1], sz[key1], limit);
                        if (pos > 0) {
                            int last = pos - 1, l = 0, r = last, localMin = INT_MAX;
                            while (l <= r) {
                                int mid = (l + r) >> 1;
                                int j = idx_lists[key1][mid];
                                if (freq[i][b] != freq[j][b]) {
                                    int v = val_lists[key1][mid];
                                    if (v < localMin) localMin = v;
                                    l = mid + 1;
                                } else {
                                    r = mid - 1;
                                }
                            }
                            if (localMin != INT_MAX) {
                                int cur = odd - even - localMin;
                                if (cur > ans) ans = cur;
                            }
                        }
                    }
                }

                int key2 = (odd % 2) << 1 | (even % 2);
                int curDiff = odd - even;
                if (sz[key2] == 0) {
                    idx_lists[key2][0] = i;
                    val_lists[key2][0] = curDiff;
                    sz[key2] = 1;
                } else {
                    int prev_min = val_lists[key2][sz[key2] - 1];
                    int new_min = (prev_min < curDiff) ? prev_min : curDiff;
                    idx_lists[key2][sz[key2]] = i;
                    val_lists[key2][sz[key2]] = new_min;
                    sz[key2]++;
                }
            }

            for (int st = 0; st < 4; st++) {
                free(idx_lists[st]);
                free(val_lists[st]);
            }
        }
    }

    free(freq);
    return (ans == INT_MIN ? -1 : ans);
}
