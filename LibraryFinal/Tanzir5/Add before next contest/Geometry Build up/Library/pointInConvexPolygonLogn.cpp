/// points of poly must be in clockwise order
LL triArea(point a, point b, point c)
{
    return (a.x*b.y) + (b.x*c.y) + (c.x*a.y) - (a.x*c.y) - (b.x*a.y) - (c.x*b.y);
}

bool inTriangle(point a, point b, point c, point p)
{
    if((llabs(triArea(a,p,b)) + llabs(triArea(b,p,c)) + llabs(triArea(c,p,a))) == llabs(triArea(a,b,c)))
        return true;
    else
        return false;
}

bool isCCW(point a, point b, point c)
{
    return (triArea(a,b,c) > 0);
}

bool inConvexPoly(vector<point>&poly, point p)
{
    int lo = 0, hi = (int)poly.size()-1;
    while(lo < hi-1)
    {
        int mid = (lo+hi)/2;
        if(inTriangle(poly[lo],poly[mid],poly[hi],p))
        {

            if(( lo+1 == mid && triArea(poly[lo], p, poly[mid]) == 0) || (mid+1 == hi && triArea(poly[mid], p, poly[hi]) == 0)
                || ((hi+1)%poly.size() == lo && triArea(poly[hi], p, poly[lo]) == 0))
                return false;
            else
                return true;
        }
        else
        {
            if(isCCW(poly[lo], p, poly[mid])== 0)
                hi = mid;
            else
                lo = mid;
        }
    }
    return false;
}
