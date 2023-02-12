
// Minimizes |X| + |Y|
// Breaks tie with X <= Y
LL exEuclid(LL a, LL b, LL &x, LL &y)
{
    if(b == 0){
        x = 1;
        y = 0;
        return a;
    }

    LL nx, ny, g, r;
    g = exEuclid(b, a % b, nx, ny);
    x = ny;
    y = nx - a / b * ny;

    return g;
}

LL __lower_bound(LL x0, LL dx, LL x)
{
    LL d = x - x0;
    if(d > 0 && d % dx)
    {
        if(dx > 0) return d/dx + 1;
        return d/dx - 1;
    }
    return d/dx;
}
