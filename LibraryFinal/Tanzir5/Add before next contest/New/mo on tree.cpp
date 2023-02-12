#include<bits/stdc++.h>
using namespace std;

#define mem(t, v)   memset ((t) , v, sizeof(t))
#define all(x)      x.begin(),x.end()
#define un(x)       x.erase(unique(all(x)), x.end())
//#define sf(n)       scanf("%d", &n)
//#define sff(a,b)    scanf("%d %d", &a, &b)
//#define sfff(a,b,c) scanf("%d %d %d", &a, &b, &c)
//#define sl(n)       scanf("%lld", &n)
//#define sll(a,b)    scanf("%lld %lld", &a, &b)
//#define slll(a,b,c) scanf("%lld %lld %lld", &a, &b, &c)
#define D(x)        cerr << __LINE__ << ": " << #x << " = " << (x) << '\n'
#define DD(x,y)     cerr << __LINE__ << ": " << #x << " = " << x << "   " << #y << " = " << y << '\n'
#define DDD(x,y,z)  cerr << __LINE__ << ": " << #x << " = " << x << "   " << #y << " = " << y << "   " << #z << " = " << z << '\n'
#define DBG         cerr << __LINE__ << ": Hi" << '\n'
#define pb          push_back
#define PI          acos(-1.00)
#define xx          first
#define yy          second
#define eps         1e-9

typedef unsigned long long int ULL;
typedef long long int LL;
typedef pair<int,int> pii;
typedef pair<LL,LL> pll;


inline int setBit(int N, int pos) { return N=N | (1<<pos); }
inline int resetBit(int N, int pos) { return N= N & ~(1<<pos); }
inline bool checkBit(int N, int pos) { return (bool)(N & (1<<pos)); }

//int fx[] = {+0, +0, +1, -1, -1, +1, -1, +1};
//int fy[] = {-1, +1, +0, +0, +1, +1, -1, -1}; //Four & Eight Direction


/// Run a dfs and fill up level and parent arrays first.
/// 1 based indexing
#define MAXLG       17
#define MAXN        100000
#define MAXQ        100000
int val[MAXN+10];
vector<pii>E[MAXN+10];

int parent[MAXN+10], sparseTable[MAXLG+2][MAXN+10], level[MAXN+10], n, counter, ara[MAXN*2+10];
int st[MAXN+10], ed[MAXN+10];
bool in[MAXN+10];

void dfs(int node, int par, int cur)
{
    st[node] = ++counter;
    ara[counter] = node;
    parent[node] = par;
    level[node] = cur;
    for(auto v: E[node])
    {
        if(v.xx!=par)
            val[v.xx] = v.yy, dfs(v.xx, node, cur+1);
    }
    ed[node] = ++counter;
    ara[counter] = node;
}
void initSparseTable(int Root)
{
    dfs(Root,0,1);
    val[Root] = 1e9;
    for(int i = 1; i<=n; i++)
        sparseTable[0][i] = parent[i];
    for(int p = 1; p <= MAXLG; p++)
    {
        for(int u = 1; u <= n; u++)
            sparseTable[p][u] = sparseTable[p-1][sparseTable[p-1][u]];
    }
}

int findLCA(int u, int v)
{
    /// keep u as the deeper node
    if(level[v] > level[u])
        swap(u,v);
    for(int i = MAXLG; i>=0; i--)
    {
        if((1<<i) <= level[u] - level[v])
            u = sparseTable[i][u];
    }
    if(u == v)
        return v;
    for(int i = MAXLG; i>=0; i--)
    {
        if(sparseTable[i][u] != sparseTable[i][v])
            u = sparseTable[i][u], v = sparseTable[i][v];
    }
    return parent[v];
}

/*
    Complexity: O(max(n*sqrt(n), q*sqrt(n), q*log(q)))
    Optimizations done:
    1. keep l_bucket
    2. use inline functions
    3. use even odd different sorting
*/

int ans,  sltn[MAXQ+10], on[MAXN+10];
int freq[MAXN+10], bucket_size = sqrt(MAXQ);

struct data{
    int st, ed, idx, l_bucket, u, v, lca;
    bool even;
    data(int a, int b, int i, int uu, int vv, int LCA)
    {
        u = uu, v = vv, lca = LCA;
        st = a, ed = b, idx = i;
        l_bucket = st/bucket_size;
        if(l_bucket & 1)
            even = false;
        else
            even = true;
    }
    data(){}
};

vector< data > Q;
priority_queue<int, vector<int>, greater <int>> S;
bool present[MAXN+10];
inline bool cmp(data a, data b)
{
    if(a.l_bucket == b.l_bucket)
    {
        if(a.even)
            return a.ed < b.ed;
        else
            return a.ed > b.ed;
    }
    return a.l_bucket < b.l_bucket;
}

inline void add(int node)
{
    if(val[node] > n)
        return;
    freq[val[node]]++;
    if(freq[val[node]] == 1)
        present[val[node]] = 1;
}

inline void rmv(int node)
{
    if(val[node] > n)
        return;
    freq[val[node]]--;
    if(freq[val[node]] == 0)
    {
        present[val[node]] = 0;
        if(in[val[node]] == 0)
            S.push(val[node]), in[val[node]] = 1;
    }
}

inline void check(int idx)
{
    int node = ara[idx];
    if(on[node])
        rmv(node);
    else
        add(node);
    on[node] ^= 1;
}

inline void fix()
{
    while(present[S.top()])
        in[S.top()] = 0, S.pop();
}


void Mo()
{
    sort(all(Q), cmp);
    ans = 0;
    check(1);
    int l = 1, r = 1;
    for(int i = 0; i<Q.size(); i++)
    {
//        DD(Q[i].st, Q[i].ed);
//        DDD(Q[i].u, Q[i].v, Q[i].lca);
        while(l < Q[i].st)
            check(l), l++;
        while(l > Q[i].st)
            l--, check(l);
        while(r < Q[i].ed)
            r++, check(r);
        while(r > Q[i].ed)
            check(r), r--;
        if(Q[i].lca == Q[i].u || Q[i].lca == Q[i].v)
            check(st[Q[i].lca]);
        fix();
        sltn[Q[i].idx] = S.top();

        if(Q[i].lca == Q[i].u || Q[i].lca == Q[i].v)
            check(st[Q[i].lca]);
    }
}
inline void sf(int &a)
{
    int cc = getc(stdin);
    for (; (cc < '0' || cc > '9') && (cc!='-');)  cc = getc(stdin);
    bool neg = false;
    if(cc == '-')
    {
        neg = true;
        cc = getc(stdin);
    }
    int ret = 0;
    for (; cc >= '0' && cc <= '9';)
    {
        ret = ret * 10 + cc - '0';
        cc = getc(stdin);
    }
    if(neg)
        ret = -ret;
    a = ret;
}

int main()
{
//    freopen("maxon.txt","r",stdin);
    //freopen("out.txt","w",stdout);

    int u, v, c, m;
    sf(n), sf(m);
    for(int i = 0; i<=n; i++)
        S.push(i), in[i] = 1;
    for(int i = 1; i<n; i++)
        sf(u), sf(v), sf(c), E[u].pb({v,c}), E[v].pb({u,c});
    initSparseTable(1);
    for(int i = 1; i<=m; i++)
    {
        sf(u), sf(v);
        if(st[u] > st[v])
            swap(u, v);
        int lca = findLCA(u,v);
        if(u == lca)
            Q.pb(data(st[u], st[v], i, u, v, lca));
        else
            Q.pb(data(ed[u], st[v], i, u, v, lca));
    }
    Mo();
    for(int i = 1; i<=m; i++)
        printf("%d\n",sltn[i]);
    return 0;
}

