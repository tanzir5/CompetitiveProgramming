//Area of Sub-Polygon [st ... ed]

vector< pii > polygon;
LL dp[MAX+5];

LL F(int ed)
{
    if(ed < 0) return 0;
    if(dp[ed] != -1) return dp[ed];

    int nxt = (ed + 1) % polygon.size();
    return dp[ed] = (LL) polygon[ed].xx * polygon[nxt].yy - (LL) polygon[ed].yy * polygon[nxt].xx + F(ed - 1);
}

LL compute(int st, int ed)
{
    LL ret = (LL) polygon[ed].xx * polygon[st].yy - (LL)polygon[ed].yy * polygon[st].xx;
    if(st <= ed) return abs( ret + F(ed - 1) - F(st - 1));
    return abs( ret + F((int) polygon.size() - 1) - (F(st - 1) - F(ed - 1)));
}
