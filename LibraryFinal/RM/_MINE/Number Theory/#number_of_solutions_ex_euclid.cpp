
LL go(LL a, LL b, LL p) // 0 < min(a,b,p) && max(a,b,p) < 1e8
{
    int i, j;
    pair<LL, LL> init;
    LL l, r, n, g = __gcd(a,b), m = p/g;
    if(p%g) return 0;
    init = ex_euclid(a,b);
    init.xx *= m;
    init.yy *= m;
    if(init.xx > 0)
    {
        n = g*init.xx;
        n = n/b+1;
    }
    else n = 1;
    init.xx -= (b/g) * n;
    init.yy += (a/g) * n;
    l = (-init.xx * g);
    if(l % b) l = l/b + 1;
    else l = l/b;
    r = init.yy * g;
    r = r/a + 1;
    return max(0LL, r-l);
}
