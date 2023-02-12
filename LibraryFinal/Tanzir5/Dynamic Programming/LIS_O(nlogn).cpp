/// O(nlogk) LIS
/// k is the length of the LIS
/// Code by: Leonardo Boshell ( LOJ Wavio Sequence )
int L[MAX+10];
int lis(int *seq, int *dp, int N)
{
    int len = 0;
    for (int i = 1; i <= N; ++i) {
        int lo = 1, hi = len;
        while (lo <= hi) {
            int m = (lo + hi) / 2;
            if (L[m] < seq[i]) lo = m + 1;
            else hi = m - 1;
        }
        L[lo] = seq[i], dp[i] = lo;
        if (len < lo) len = lo;
    }
    return len;
}
