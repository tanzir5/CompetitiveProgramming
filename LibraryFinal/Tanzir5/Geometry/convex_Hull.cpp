
//Convex-Hull (O(nlogn))
LL triArea2(pii a, pii b, pii c) // includes sign.. +ve -> ccw, -ve -> cw;
{
    LL ret = 0;
    ret += (LL) a.xx*b.yy + (LL) b.xx*c.yy + (LL) c.xx*a.yy - (LL) a.xx*c.yy - (LL) c.xx*b.yy - (LL) b.xx*a.yy;
    return ret;
}

bool ccw(pii a, pii b, pii c) {return triArea2(a,b,c) >= 0;}
bool cw(pii a, pii b, pii c)  {return triArea2(a,b,c) <= 0;}

void Convex_hull(vector<pii> &P, vector<pii> &hull) // Returns the points in acw order using minimum number of points
{
    hull.clear();
    vector<pii> up, dwn;
    pii L, R;

    int i, len = P.size();
    sort(P.begin(), P.end());

    up.push_back(P[0]), dwn.push_back(P.back());
    L = P[0]; R = P.back();

    for(i = 1; i <= len-1; i++) {
        if(i != len-1 && ccw(L, P[i], R)) continue;
        else while(up.size() >= 2 && ccw(up[up.size()-2], up.back(), P[i])) up.pop_back();
        up.push_back(P[i]);
    }

    for(i = len - 2; i >= 0; i--) {
        if(i && cw(L, P[i], R)) continue;
        else while(dwn.size() >= 2 && ccw(dwn[dwn.size()-2], dwn.back(), P[i])) dwn.pop_back();
        dwn.push_back(P[i]);
    }

    up.pop_back(); dwn.pop_back();
    hull = up;
    for(i = 0; i < dwn.size();i++) hull.push_back(dwn[i]);

    reverse(hull.begin(), hull.end());
}

