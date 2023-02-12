const LL MOD = ?;
LL lagrange(LL F[], int total, LL n)
{
    if(1<=n && n <= total)
        return F[n];
    LL up = 1, down = 1;
    for(int i = 2; i<=total; i++)
    {
        LL nw = n - i;
        if(nw < 0)
            nw += MOD;
        up *= (nw);
        up %= MOD;

        nw = (1-i);
        if(nw < 0)
            nw += MOD;
        down *= nw;
        down %= MOD;
    }

    LL ret = (up * F[1])%MOD;
    ret *= expo(down, MOD-2);
    ret %= MOD;
    for(int i = 2; i<=total; i++)
    {
        LL nw = n - (i-1);
        if(nw < 0)
            nw += MOD;
        up *= (nw);
        up %= MOD;

        nw = (n-i);
        if(nw < 0)
            nw += MOD;
        down *= nw;
        down %= MOD;

        down *= (i-1);
        down %= MOD;

        nw = ((i-1)-total);
        if(nw < 0)
            nw += MOD;
        up *= nw;
        up %= MOD;

        LL tmp = (up * F[i])%MOD;
        tmp *= expo(down, MOD-2);
        tmp %= MOD;

        ret += tmp;
        if(ret >= MOD)
            ret -= MOD;
    }
    return ret;
}
