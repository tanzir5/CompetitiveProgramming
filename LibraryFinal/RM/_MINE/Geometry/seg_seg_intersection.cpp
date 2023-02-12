
///Segment Segment Intersection (2D)
int order(pii st, pii ed, pii q){
	LL xp = (LL) (ed.xx - st.xx) * (q.yy - ed.yy) - (LL) (ed.yy - st.yy) * (q.xx - ed.xx);
	if(!xp) return 0;
	if(xp > 0) return 1;
	return -1;
}

bool onsegment(pii l, pii r, pii mid) // (l___r) -> mid
{
    if(order(l,r,mid)) return 0;
    return (min(l.xx,r.xx) <= mid.xx && mid.xx <= max(l.xx,r.xx) && min(l.yy,r.yy) <= mid.yy && mid.yy <= max(l.yy,r.yy));
}

inline bool intersect(pii p1, pii p2, pii p3, pii p4)
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
