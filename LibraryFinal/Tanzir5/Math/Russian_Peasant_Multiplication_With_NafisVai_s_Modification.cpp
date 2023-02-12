/*
    Russian Peasant Multiplication with Nafis vai's addition.
    O(log(b))
    Gives (a*b)%m
    where (a,b,m) < 2^64
*/

ULL add(ULL a, ULL b, ULL m)
{
    a%= m, b%= m;
    if(m-b > a)
        return (a+b);
    else
        return (a-(m-b));
}

ULL mul(ULL a, ULL b, ULL m)
{
    a%= m, b%= m;
    int i = 0;
    ULL ret = 0;
    while(b)
    {
        if(b&1)
            ret = add(ret, a, m);
        a = add(a, a, m);
        b/=2;
    }
    return ret;
}

