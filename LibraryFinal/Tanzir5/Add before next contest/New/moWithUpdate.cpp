/// O(n^(5/3))
#define MAX         ?
int k = cbrt(MAX*MAX);
int n, Q, A[MAX+10], B[MAX+10], angry[MAX+10];
struct data{
    int st, ed, stBlock, edBlock, t, idx;
    data(int a, int b, int u, int i)
    {
        idx = i;
        st = a;
        ed = b;
        stBlock = st/k;
        edBlock = ed/k;
        t = u;
    }
};

bool operator < (data a, data b)
{
    if(a.stBlock != b.stBlock)
        return a.stBlock < b.stBlock;
    if(a.edBlock != b.edBlock)
        return a.edBlock < b.edBlock;
    if(a.edBlock&1)
        return a.t > b.t;
    else
        return a.t < b.t;
}

vector<data>query;
struct upData{
    int idx, prev, cur;
}U[MAX+10];

LL ans = 0, freq[MAX+10];
inline void add(int idx);
inline void rmv(int idx);
int L, R;
inline void apply(int idx, int x)
{
    if(L <= idx && idx <= R)
        rmv(idx);
    A[idx] = x;
    if(L <= idx && idx <= R)
        add(idx);
}
LL res[MAX+10];
void Mo()
{
    sort(all(query));
    ans = 0;
    add(1);
    L = R = 1;
    int t = 0;
    for(int i = 0; i<query.size(); i++)
    {
        while(t < query[i].t) t++, apply(U[t].idx, U[t].cur);
        while(t > query[i].t) apply(U[t].idx, U[t].prev), t--;

        while(L < query[i].st) rmv(L), L++;
        while(L > query[i].st) L--, add(L);
        while(R < query[i].ed) R++, add(R);
        while(R > query[i].ed) rmv(R), R--;
        res[query[i].idx] = ans;
    }
}
