
/*
InConvexPoly:
P contains points in acw order. Works for only convex polygon
Complexity O(lg n)
*/

LL triArea2(pii a, pii b, pii c) // includes sign
{
    LL ret = 0;
    ret += (LL) a.xx*b.yy + (LL) b.xx*c.yy + (LL) c.xx*a.yy - (LL) a.xx*c.yy - (LL) c.xx*b.yy - (LL) b.xx*a.yy;
    return ret;
}

bool inConvexPoly(vector<pair <int, int> > &P, pair <int, int> q)
{
    pii fix = P[0];
    int st = 1, ed = P.size()-1, mid;

    while(ed - st > 1)
    {
        mid = (st+ed)>>1;
        if(triArea2(fix, P[mid], q) > 0 ) st = mid;
        else ed = mid;
    }

    if(triArea2(fix, P[st], q) < 0) return false;
    if(triArea2(P[st], P[ed], q) < 0) return false;
    if(triArea2(P[ed], fix, q) < 0) return false;
    return true;
}
