/*
    Rabin Miller Primality Testing
    Russian Peasant Multiplication with Nafis vai's addition is used for multiplying two large numbers.
    O(iterations * log(p) * log(p) )
    Probabilistic algorithm.
    If N iterations are performed on a composite number, then the probability that it passes each test is 1/4^N or less.
    But there's also another good thing that says Rabin Miller will not fail for any p < 2^64 if 12 iterations are done with the first 12 primes.
    " The primality of numbers < 2^64 can be determined by asserting strong pseudoprimality to all prime bases <= 37 (=prime(12)).
    Testing to prime bases <=31 does not suffice, as a(11) < 2^64 and a(11) is a strong pseudoprime to all prime bases <= 31"

    Smallest odd number for which Miller-Rabin primality test on bases <= n-th prime does not reveal compositeness.
    2047, 1373653, 25326001, 3215031751, 2152302898747, 3474749660383, 341550071728321, 341550071728321, 3825123056546413051,
    3825123056546413051, 3825123056546413051, 318665857834031151167461, 3317044064679887385961981

*/

inline ULL add(ULL a, ULL b, ULL m)
{
    a%= m, b%= m;
    if(m-b > a)
        return (a+b);
    else
        return (a-(m-b));
}

inline ULL mul(ULL a, ULL b, ULL m)
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

int A[20] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43};


inline LL ip(LL a, LL b, LL mod)
{
    LL ret;
    ret = 1;
    while(b)
    {
        if(b&1)
            ret = (mul(ret , a, mod)) ;
        b = b >> 1;
        a = mul(a,a,mod) ;
    }
    return ret;
}
bool RabinMiller(LL p, int iterations)
{
    if(p < 2)
        return false;
    if( p == 2)
        return true;
    LL d, a;
    int s = 0;
    d = p-1;
    while((d&1) == 0)
    {
        s++;
        d = d >> 1;
    }
    for(int i = 0; i< iterations; i++)
    {
        a = A[i] % (p-1);
        if(a == 0)
            a = p-1;
        a = ip(a,d,p);
        if(a == 1 || a == p-1)
            continue;
        for(int i = 1; i<s; i++)
        {
            a = mul(a,a,p);
            if(a == 1)
                return false;
            if(a == p-1)
                break;
        }
        if(a != p-1)
            return false;
    }
    return true;
}
