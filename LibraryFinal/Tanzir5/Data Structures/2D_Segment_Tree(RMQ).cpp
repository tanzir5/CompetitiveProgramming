/// Single point update, Range Query
struct node{
    int t[MAX*4 + 10];
}T[MAX*4 + 10];
int n;
int q(int tr, int nd, int st, int ed, int i, int j)
{
    if(st >= i && ed<= j)
        return T[tr].t[nd];
    int lft = 2*nd, rght = lft+1, mid = (ed+st)/2;
    int a, b, ret;
    if(i <= mid)
        a = ret = q(tr, lft, st, mid, i, j);
    if(j > mid)
        b = ret = q(tr, rght, mid+1, ed, i, j);
    if(i <= mid && j > mid)
        ret = max(a,b);
    return ret;
}
int query(int nd, int st, int ed, int i, int j, int _i, int _j)
{
    if(st >= i && ed<= j)
       return q(nd, 1, 1, n, _i, _j);
    int lft = 2*nd, rght = lft+1, mid = (ed+st)/2;
    int a, b, ret;
    if(i <= mid)
        a = ret = query(lft, st, mid, i, j, _i, _j);
    if(j > mid)
        b = ret = query(rght, mid+1, ed, i, j, _i, _j);
    if(i <= mid && j > mid)
        ret = max(a,b);
    return ret;
}
void u(int tr, int nd, int st, int ed, int i, int v)
{
    if(i == st && st == ed)
    {
        T[tr].t[nd] = v;
        return;
    }
    int lft = 2*nd, rght = lft+1, mid = (ed+st)/2;
    if(i <= mid)
        u(tr, lft, st, mid, i, v);
    if(i > mid)
        u(tr, rght, mid+1, ed, i, v);
    T[tr].t[nd] = max(T[tr].t[lft], T[tr].t[rght]);
}
void update(int nd, int st, int ed, int i, int _i, int v)
{
    if(i == st && st == ed)
    {
        u(nd, 1, 1, n, _i, v);
        return;
    }
    int lft = 2*nd, rght = lft+1, mid = (st+ed)/2;
    if(i <= mid)
        update(lft, st, mid, i, _i, v);
    if(i > mid)
        update(rght, mid+1, ed, i, _i, v);
    int a = q(lft, 1, 1, n, _i, _i);
    int b = q(rght, 1, 1, n, _i, _i);
    u(nd, 1, 1, n, _i, max(a,b));
}
