/// Finds Modular inverse of a with respect to MOD
inline int inv(int a, int MOD)
{
    int x = 0,y = 1,u = 1,v = 0;
    int e = MOD,f = a;
    int c,d,q,r;
    while(f != 1)
    {
        q = e/f;
        if(e >= f)
            r = e%f;
        else
            r = e;
        c = x-q*u;
        d = y-q*v;
        x = u;
        y = v;
        u = c;
        v = d;
        e = f;
        f = r;
    }
    if(u < 0)
        u += MOD;
    if( u >= MOD)
        u -= MOD;
    return u;
}
