#include<bits/stdc++.h>
using namespace std;

#define mem(t, v)   memset ((t) , v, sizeof(t))
#define all(x)      x.begin(),x.end()
#define un(x)       x.erase(unique(all(x)), x.end())
#define sf(n)       scanf("%d", &n)
#define sff(a,b)    scanf("%d %d", &a, &b)
#define sfff(a,b,c) scanf("%d %d %d", &a, &b, &c)
#define sl(n)       scanf("%lld", &n)
#define sll(a,b)    scanf("%lld %lld", &a, &b)
#define slll(a,b,c) scanf("%lld %lld %lld", &a, &b, &c)
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

#define MAX     100000

struct data{
    int lft, rght;
    int sum;
    data()
    {
        lft = rght = -1;
        sum = 0;
    }
    inline void Copy(data& copyFrom)
    {
        lft = copyFrom.lft;
        rght = copyFrom.rght;
        sum = copyFrom.sum;
    }
}tree[MAX*4*20+10], dummy;

int total, version[MAX+10];

inline int create(data& copyFrom)
{
	total++;
	tree[total].Copy(copyFrom);
	return total;
}

int A[MAX+10];

void init(int node, int st, int ed)
{
    if(st == ed)
    {
        tree[node].sum = A[st];
        return;
    }
    int mid = (st+ed)/2;

    tree[node].lft = create(dummy);
    init(tree[node].lft, st, mid);

    tree[node].rght = create(dummy);
    init(tree[node].rght, mid+1, ed);

    int lft = tree[node].lft, rght = tree[node].rght;
    tree[node].sum = tree[lft].sum + tree[rght].sum;
}

void update(int node, int st, int ed, int pos, int val)
{
    if(st == ed)
    {
        tree[node].sum += val;
        return;
    }

    int lft = tree[node].lft, rght = tree[node].rght, mid = (st+ed)/2;

    if(pos <= mid)
    {
        lft = tree[node].lft = create(tree[lft]);
        update(lft, st, mid, pos, val);
    }
    else
    {
        rght = tree[node].rght =  create(tree[rght]);
        update(rght, mid+1, ed, pos, val);
    }
    tree[node].sum = tree[lft].sum + tree[rght].sum;
}

int query(int node, int st, int ed, int i, int j)
{
    if(i <= st && ed <= j)
        return tree[node].sum;

    int mid = (st+ed)/2;
    int ret = 0;
    if(i <= mid)
        ret += query(tree[node].lft, st, mid, i, j);
    if(j > mid)
        ret += query(tree[node].rght, mid+1, ed, i, j);
    return ret;
}

int main()
{
   // freopen("maxon.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    total = 0;
    sf(n);
    for(int i = 1; i<=n; i++)
        sf(A[i]);
    version[0] = create(dummy);
    init(version[0],1,n);
    int q;
    sf(q);
    int type, idx, pos, st, ed, v;
    int cnt = 0;
    for(int i = 1; i<=q; i++)
    {
        sff(type, idx);
        if(type == 1)
        {
            sff(pos, v);
            version[++cnt] = create(tree[version[idx]]);
            update(version[cnt], 1, n, pos, v);
        }
        else
        {
            sff(st, ed);
            printf("%d\n",query(version[idx], 1, n, st, ed));
        }
    }
    return 0;
}
