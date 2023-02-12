void pre()
{
    // set the cost function
    // Then set the base case
}

void call(int group, int L, int R, int optL, int optR)
{
    if(L > R)
        return;
    int mid = (L+R)/2;
    int ret = INT_MAX, idx;
    int lim = min(optR, mid);
    for(int i = optL; i<=lim; i++)
    {
        int cur = dp[group-1][i-1] + cost[i][mid];
        if(cur <= ret)
        {
            ret = cur;
            idx = i;
        }
    }
    dp[group][mid] = ret;
    call(group, L, mid-1, optL, idx);
    call(group, mid+1, R, idx, optR);
}

int solve(int n, int k)
{
    pre();
    for(int group = 1; group <= k; group++)
        call(group, 1, n, 1, n);
    return dp[k][n];
}
