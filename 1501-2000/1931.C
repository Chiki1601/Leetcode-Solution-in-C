int colorTheGrid(int m, int n) {
    const int MOD = 1000000007;
    int maxMask = 1;
    for (int i = 0; i < m; ++i) maxMask *= 3;
    int states[48], S = 0;
    for (int mask = 0; mask < maxMask; ++mask) {
        int x = mask, prev = -1, ok = 1;
        for (int i = 0; i < m; ++i) {
            int d = x % 3; 
            if (d == prev) { ok = 0; break; }
            prev = d; 
            x /= 3;
        }
        if (ok) states[S++] = mask;
    }
    int compat[48][48], compatSz[48];
    for (int i = 0; i < S; ++i) compatSz[i] = 0;
    for (int i = 0; i < S; ++i) {
        for (int j = 0; j < S; ++j) {
            int x = states[i], y = states[j], ok = 1;
            for (int k = 0; k < m; ++k) {
                if (x % 3 == y % 3) { ok = 0; break; }
                x /= 3; y /= 3;
            }
            if (ok) compat[i][ compatSz[i]++ ] = j;
        }
    }
    int dp[48], new_dp[48];
    for (int i = 0; i < S; ++i) dp[i] = 1;
    for (int t = 0; t < n - 1; ++t) {
        for (int j = 0; j < S; ++j) new_dp[j] = 0;
        for (int i = 0; i < S; ++i) {
            int di = dp[i];
            if (di) {
                for (int k = 0; k < compatSz[i]; ++k) {
                    int j = compat[i][k];
                    new_dp[j] = (new_dp[j] + di) % MOD;
                }
            }
        }
        for (int i = 0; i < S; ++i) dp[i] = new_dp[i];
    }
    long long ans = 0;
    for (int i = 0; i < S; ++i) ans = (ans + dp[i]) % MOD;
    return (int)ans;
}
