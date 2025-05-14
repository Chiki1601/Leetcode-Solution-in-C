#include <stdint.h>
#include <string.h>
#define K 26
#define MOD 1000000007

static void mat_mul(int64_t A[K][K], int64_t B[K][K], int64_t C[K][K]) {
    int i, j, k;
    for(i=0;i<K;i++) for(j=0;j<K;j++) C[i][j]=0;
    for(i=0;i<K;i++){
        for(k=0;k<K;k++){
            int64_t aik = A[i][k];
            if (!aik) continue;
            for(j=0;j<K;j++){
                C[i][j] = (C[i][j] + aik * B[k][j]) % MOD;
            }
        }
    }
}

static void mat_pow(int64_t M[K][K], int exp, int64_t R[K][K]) {
    int64_t tmp[K][K], base[K][K];
    int i, j;
    for(i=0;i<K;i++) for(j=0;j<K;j++){
        R[i][j]    = (i==j);
        base[i][j] = M[i][j];
    }
    while(exp > 0) {
        if (exp & 1) {
            mat_mul(R, base, tmp);
            memcpy(R, tmp, sizeof tmp);
        }
        mat_mul(base, base, tmp);
        memcpy(base, tmp, sizeof tmp);
        exp >>= 1;
    }
}

int lengthAfterTransformations(char* s, int t, int* nums, int numsSize) {
    int64_t freq[K] = {0};
    for(char* p = s; *p; ++p) {
        freq[*p - 'a']++;
    }
    int64_t M[K][K] = {{0}};
    for(int i=0;i<K;i++){
        for(int d=1; d<=nums[i]; d++){
            M[i][(i+d)%K]++;
        }
    }
    int64_t Mt[K][K];
    mat_pow(M, t, Mt);
    int64_t ans = 0;
    for(int i=0;i<K;i++){
        if (!freq[i]) continue;
        for(int j=0;j<K;j++){
            ans = (ans + freq[i] * Mt[i][j]) % MOD;
        }
    }
    return (int)ans;
}
