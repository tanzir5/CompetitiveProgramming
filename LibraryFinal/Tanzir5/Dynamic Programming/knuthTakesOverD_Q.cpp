// k is the total number of groups
LL call(int group, int pos)
{
    if(pos == 0)
        return dp[group][pos] = 0;
    if(group == 0)
        return dp[group][pos] = inf;

    if(dp[group][pos] != -1)
        return dp[group][pos];

    int L = 1, R = pos;
    if(pos-1 > 0)
    {
        call(group, pos-1);
        L = max(L, path[group][pos-1]);
    }
    if(group+1 <= k)
    {
        call(group+1, pos);
        R = min(R, path[group+1][pos]);
    }
    LL ret = inf;
    for(int i = L; i<=R; i++)
    {
        LL cur = call(group-1, i-1) + (cum[pos] - cum[i-1])*(pos-i+1);
        if(cur < ret)
        {
            ret = cur;
            path[group][pos] = i;
        }
    }
    return dp[group][pos] = ret;
}

