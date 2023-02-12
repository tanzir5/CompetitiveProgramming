
//Sum of Divisors upto N

LL sum(LL L, LL R) {return (R * (R+1))/2 - (L * (L-1))/2;}

LL sodUpto(LL n)
{
    int s = sqrt(n), i;
    LL x_min, x_max, ret = 0;

    for(i = 1; i <= s; i++)
        ret += i * (n/i);

    if(s * s == n) s--;    for(i = 1; (LL) i <= s; i++)
    {
        x_min = max((LL)s + 1, n/(i+1) + 1);
        x_max = n/i;

        if(x_min > x_max) continue;
        ret += sum(x_min, x_max) * i;
    }
    return ret;
}

