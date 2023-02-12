
//Extended Euclid
pii ex_euclid(int a, int b) // a'x'+b'y' = gcd(a,b) //minimized |x| + |y|
{
    if(a == 0) return mp(0,1);
    pii pr = ex_euclid(b%a, a), ret;
    ret.fi = pr.se - (b / a) * pr.fi;
    return mp(ret.fi, pr.fi);
}
