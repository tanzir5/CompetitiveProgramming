/*
    our task is to find a^(exp^(b)),
    a:Provided in input,10^5=>a>=0
    b:Provided in Input,10^5=>b>=0
    exp=(nC0)^2 + (nC1)^2 +(nC2)^2+..........+(nCn)^2,
    n:Provided in the input, 10^5=>n>=0
*/
int main()
{
    int i, k, cs, t;
    LL a, b, n;
    LL exp, MOD2, ans, j, MOD3;
    MOD2 = (MOD-1)/2;
    MOD3 = MOD-1;
    fact[0] = 1;
    FRE(i,1,200010)
        fact[i] = (fact[i-1] * i) % MOD2;
    sf(t);
    FRE(cs,1,t)
    {
        scanf("%lld %lld %lld",&a,&b,&n);
        /// find (a^(exp^b)) % MOD
        /// where exp = C(2n,n);
        /// C(a,b) means combination of b things out of a things.
        /// p = 1000000007 which is a prime.
        /// From Fermat's little theorem, (a^(p-1)) % p = 1 for any prime p.
        /// let's assume m = exp^b;
        /// m = c*(p-1) + (m%(p-1));
        /// j = (m%(p-1));
        /// so m = c*(p-1) + j;
        /// a^m = (a^(p-1))^c * a^j;
        /// (a^(p-1))^c = 1;(Fermat)
        /// so (a^m) % p = (a^j) % p;

        /// now for j, j = (exp^b)%(p-1);
        /// let MOD2 = (p-1)/2; [which is 500000003, a prime number]
        /// exp = C(2n,n) = 2*C(2n-1,n-1);
        /// we know, (2*a) % (2*b) = (2*(a%b))%(2*b);
        /// so j = (2*C(2n-1,n-1))^b % (p-1)
        /// j = ((2*(C(2n-1,n-1)% MOD2))^b)%(p-1);
        /// then find (a^j) % p;
        ans = fact[2*n-1];
        ans = (ans * ip((fact[n-1]*fact[n])%MOD2, MOD2-2, MOD2))%MOD2;
        ans = (2 * ans) % MOD3;
        ans = ip(ans,b,MOD3);
        ans = ip(a,ans,MOD);
        pf("%lld\n",ans);
    }
    return 0;
}
