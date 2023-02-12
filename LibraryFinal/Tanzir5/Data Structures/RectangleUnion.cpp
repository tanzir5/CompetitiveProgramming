struct point{
    LL x, y1, y2;
    bool st;
}A[MAX*2+10];
struct node{
    LL on, val;
}tree[MAX*32+10];
map<int,int> M;
vector<int> v;
LL ulta[MAX*4+10];
void update(int nd, int st, int ed, int i, int j, int v)
{
    if(st == ed)
        return;
    if(st > j || ed < i)
        return;
    int mid = (st+ed+1)/2, lft = 2*nd, rght = lft+1;
    if(i <= st && j >= ed)
    {
        tree[nd].val+=v;
        if(tree[nd].val == 0)
            tree[nd].on = tree[lft].on + tree[rght].on;
        else
            tree[nd].on = (ulta[ed]-ulta[st]);
        return;
    }
    if(ed -st == 1) return;
    update(lft, st, mid, i, j, v);
    update(rght, mid, ed, i, j, v);
    if(!tree[nd].val)
        tree[nd].on = tree[lft].on + tree[rght].on;
}
LL query()
{
    return tree[1].on;
}
bool operator < (point a, point b)
{
    return a.x < b.x;
}
int main()
{
    int cs, t, i, j, k, n;
    LL x1, y1, x2, y2;
    sf(t);
    FRE(cs,1,t)
    {
        mem(tree,0);
        M.clear();
        v.clear();
        sf(n);
        int mx = 1;
        FRE(i,1,n)
        {
            sll(x1,y1);
            sll(x2,y2);
            v.pb(x1);
            v.pb(x2);
            v.pb(y1);
            v.pb(y2);
            A[i*2-1].st = 1;
            A[i*2-1].x = x1;
            A[i*2-1].y1 = y1;
            A[i*2-1].y2 = y2;

            A[i*2].st = 0;
            A[i*2].x = x2;
            A[i*2].y1 = y1;
            A[i*2].y2 = y2;
        }
        sort(all(v));
        un(v);
        for(i = 0; i<v.sz; i++)
            M[v[i]] = i+1, ulta[i+1] = v[i];
        sort(A+1,A+2*n+1);
        LL nw = 0;
        LL total = 0;
        mx = v.sz;
        for(i = 1; i<=2*n; i++)
        {
            total += (A[i].x - nw) * (query());
            nw = A[i].x;
            if(A[i].st == 1)
                update(1,1,mx,M[A[i].y1],M[A[i].y2],1);
            else
                update(1,1,mx,M[A[i].y1],M[A[i].y2],-1);
        }
        pf("Case %d: %lld\n",cs,total);
    }
    return 0;
}


