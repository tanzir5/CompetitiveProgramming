int order(point l, point r, point mid) // (l___r) -> mid
{
    LL ret = 0;
    ret += (LL) l.x*r.y + (LL) r.x*mid.y + (LL) mid.x*l.y - (LL) l.x*mid.y - (LL) mid.x*r.y - (LL) r.x*l.y;
    if(ret < 0) return -1;
    if(ret > 0) return +1;
    return 0;
}

bool onsegment(point l, point r, point mid) // (l___r) -> mid
{
    if(order(l,r,mid)) return 0;
    return (min(l.x,r.x) <= mid.x && mid.x <= max(l.x,r.x) && min(l.y,r.y) <= mid.y && mid.y <= max(l.y,r.y));
}

inline bool intersect(point p1, point p2, point p3, point p4)
{
    int d1, d2, d3, d4;
    d1 = order(p3, p4, p1);
    d2 = order(p3, p4, p2);
    d3 = order(p1, p2, p3);
    d4 = order(p1, p2, p4);
    if(((d1 < 0 && d2 > 0) || (d1 > 0 && d2 < 0)) && ((d3 < 0 && d4 > 0) || (d3 > 0 && d4 < 0))) return true;
    if(!d3 && onsegment(p1, p2, p3)) return true;
    if(!d4 && onsegment(p1, p2, p4)) return true;
    if(!d1 && onsegment(p3, p4, p1)) return true;
    if(!d2 && onsegment(p3, p4, p2)) return true;
    return false;
}

bool onBoundary(vector<point>&P, point a)
{
    P.pb(P[0]);
    bool ret = 0;
    for(int i = 1; i<P.size(); i++)
    {
        if(onsegment(P[i], P[i-1], a))
        {
            ret = true;
            break;
        }
    }
    P.pop_back();
    return ret;
}

bool insidePoly(vector<point>&P, point a)
{
    if(onBoundary(P,a))
        return true;
    point b;
    b.x = (1e4+7);
    b.y = (b.x - a.x + 1 + a.y);
//    assert(__gcd(b.x-a.x, b.y - a.y) == 1 || __gcd(b.x-a.x, b.y - a.y) == -1);
    P.push_back(P[0]);
    int cnt = 0;
    for(int i = 1; i<P.size(); i++)
    {
        if(intersect(P[i], P[i-1], a, b))
            cnt ^= 1;
    }
    P.pop_back();
    if(cnt & 1)
        return true;
    else
        return false;
}
