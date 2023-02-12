
struct point{
    double x, y;
};
point P[MAX+10], temp[MAX+10], S[MAX+10];
const double inf = ?;
double dist(point a, point b)
{
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
bool operator < (point a, point b)
{
    if(a.x == b.x)
        return a.y < b.y;
    return a.x < b.x;
}
double closestPair(int st, int ed)
{
    if(st == ed)
        return inf;

    int mid = (st+ed)/2;
    point midPoint = P[mid];

    double d = min(closestPair(st,mid), closestPair(mid+1, ed));
    int L = st, R = mid+1, cnt = 0;
    for(int id = 0; id<(ed-st)+1; id++ )
    {
        if(L > mid)
            temp[id] = P[R++];
        else if(R > ed)
            temp[id] = P[L++];
        else
        {
            if(P[L].y < P[R].y)
                temp[id] = P[L++];
            else
                temp[id] = P[R++];
        }
        if(fabs(midPoint.x - temp[id].x) < d)
            S[cnt++] = temp[id];
    }
    for(int id = 0, i = st; id<(ed-st)+1; id++, i++)
        P[i] = temp[id];
    for(int i = 0; i<cnt; i++)
    {
        for(int j = i+1; j<cnt; j++)
        {
            if(fabs(S[i].y - S[j].y) > d)
                break;
            d = min(d, dist(S[i], S[j]));
        }
    }
    return d;
}

