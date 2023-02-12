
vector< pii > antipodal(vector<point> polygon){
    /*
        No 3 points can be co-linear
        Has to be in anti-clockwise order
        Can't be degenerate
        ret[i] = range of vertices antipodal to the i-th vertex
    */
    vector<pii> ret;
    vector<point> nxt;
    int q_lo, q_hi, n = polygon.size(), i, mxCnt;
    for(i = 0; i < n; i++) nxt.push_back(polygon[(i+1) % n]);

    q_lo = 0;
    while(area(polygon[n-1], nxt[n-1], nxt[q_lo]) > area(polygon[n-1], nxt[n-1], polygon[q_lo]))
        q_lo = (q_lo + 1) % n;

    for(i = 0; i < n; i++)
    {
        if(q_lo == i) q_lo = (q_lo + 1) % n;

        mxCnt = 0;
        q_hi = q_lo;
        while(true){
            double h1 = area(polygon[i], nxt[i], nxt[q_hi]), h2 = area(polygon[i], nxt[i], polygon[q_hi]);
            if(h1 > h2 + eps) q_hi = (q_hi + 1) % n, mxCnt = 0;
            else if(eq(h1, h2)) q_hi = (q_hi + 1) % n, mxCnt++;
            else break;
        }
        ret.push_back(pii(q_lo, q_hi));
        q_lo = (q_hi - (mxCnt)) % n;
        if(q_lo < 0) q_lo += n;
    }
    return ret;
}
