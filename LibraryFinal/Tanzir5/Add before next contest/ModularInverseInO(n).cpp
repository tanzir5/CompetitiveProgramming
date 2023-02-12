LL inv[?];
void buildInverse(int lim)
{
    inv[1] = 1;
    for(int i = 2; i<=lim; i++)
    {
        inv[i] = (MOD - ((MOD/i) * inv[MOD%i]) % MOD);
        if(inv[i] < 0)
            inv[i] += MOD;
    }
}
