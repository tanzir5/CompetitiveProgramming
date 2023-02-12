inline LL bigMod(LL a, LL n, LL MOD)
{
    LL ret = 1%MOD;
    a %= MOD;
    while(n)
    {
        if(n&1) ret *= a, ret %= MOD;
        a *= a;
        a %= MOD;
        n >>= 1;
    }
    return ret;
}
