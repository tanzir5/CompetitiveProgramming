/*
    Find the number of integer solutions to the problem:
        Ax + By = C
    x1<=x<=x2 and y1<=y<=y2
    Note:
    1.  Number of points with integer co-ordinates between (x,y) and (_x,_y) is:
        gcd(dx,dy)+1 ( Including both the terminal points )
    2.  Next point of(_x, _y) with integer co-ordinates on the straight line Ax+By=C
        (_x+b/g, _y-a/g).
*/

struct triple{
    LL x, y, g;
};

triple egcd(LL a, LL b)
{
    if(b == 0)
        return {1, 0, a};
    triple tmp = egcd(b, a%b);
    triple ret;
    ret.x = tmp.y;
    ret.y = (tmp.x - (a/b)*tmp.y);
    ret.g = tmp.g;
    return ret;
}

LL myCeil(LL a, LL b)
{
    LL ret = (a/b);
    if((a >= 0 && b>= 0) || (a < 0 && b < 0))
    {
        if(a%b)
            ret++;
    }
    return ret;
}

LL myFloor(LL a, LL b)
{
    LL ret = (a/b);
    if((a > 0 && b < 0) || (a < 0 && b > 0))
    {
        if(a%b)
            ret--;
    }
    return ret;
}

/// x1 <= _x + t*(b/g) <= x2
pll get_range(LL x1, LL x2, LL _x, LL b, LL g)
{
    if((b/g) < 0)
        swap(x1, x2);

    LL low = myCeil(((x1 - _x) * g), b);
    LL high = myFloor(((x2 - _x) * g), b);

    return {low, high};
}

/// ax + by = c
LL solve(LL a, LL b, LL c, LL x1, LL x2, LL y1, LL y2)
{
    triple sltn = egcd(a,b);
    LL ret;

    if(a == 0 && b == 0)
    {
        if(c == 0) ret = (x2 - x1 + 1) * (y2 - y1 + 1);
        else ret = 0;
    }
    else if(a == 0)
    {
        if(c%b) ret = 0;
        else
        {
            LL y = (c/b);
            if(y1 <= y && y <= y2)
                ret = (x2 - x1 + 1);
            else
                ret = 0;
        }
    }
    else if(b == 0)
    {
        if(c%a) ret = 0;
        else
        {
            LL x = (c/a);
            if(x1 <= x && x <= x2)
                ret = (y2 - y1 + 1);
            else
                ret = 0;
        }
    }
    else
    {
        if(c%sltn.g) ret = 0;
        else
        {
            sltn.x *= (c/sltn.g);
            sltn.y *= (c/sltn.g);
            pll rangeX = get_range(x1,x2,sltn.x,b,sltn.g);
            pll rangeY = get_range(y1,y2,sltn.y,-a,sltn.g);
            pll range;
            range = {max(rangeX.xx, rangeY.xx), min(rangeX.yy, rangeY.yy)};
            ret = range.yy - range.xx + 1;
            ret = max(0LL, ret);
        }
    }
    return ret;
}
