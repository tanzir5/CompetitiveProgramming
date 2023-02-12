/// UVA optimal Binary Search Tree
int call(int st, int ed)
{
    if(st == ed)
    {
        path[st][ed] = ed;
        return freq[st];
    }
    if(dp[st][ed] != -1)
        return dp[st][ed];
    int ret = 1e9;

    call(st, ed-1);
    call(st+1, ed);

    int L = max(st, path[st][ed-1]);
    int R = min(ed, path[st+1][ed]);

    for(int i = L; i<=R; i++)
    {
        int nw = 0;
        if(i-1 >= st)
            nw += call(st, i-1);
        if(ed >= i+1)
            nw += call(i+1, ed);
        nw += csum[ed] - csum[st-1];
        if(nw < ret)
        {
            ret = nw;
            path[st][ed] = i;
        }
    }
    return dp[st][ed] = ret;
}
