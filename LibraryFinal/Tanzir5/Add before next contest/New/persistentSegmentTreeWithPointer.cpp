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
    data *lft, *rght;
    int sum;
    data()
    {
        lft = rght = NULL;
        sum = 0;
    }
    data(data* copyFrom)
    {
        lft = copyFrom->lft;
        rght = copyFrom->rght;
        sum = copyFrom->sum;
    }
};
data *version[MAX+10];

int A[MAX+10];

void init(data *node, int st, int ed)
{
    if(st == ed)
    {
        node->sum = A[st];
        return;
    }
    int mid = (st+ed)/2;

    node->lft = new data();
    init(node->lft, st, mid);

    node->rght = new data();
    init(node->rght, mid+1, ed);

    node->sum = node->lft->sum + node->rght->sum;
}

void update(data* node, int st, int ed, int pos, int val, data *copyFrom)
{
    if(st == ed)
    {
        node->sum += val;
        return;
    }

    int mid = (st+ed)/2;
    if(pos <= mid)
    {
        node->lft = new data(copyFrom->lft);
        update(node->lft, st, mid, pos, val, copyFrom->lft);
    }
    else
    {
        node->rght = new data(copyFrom->rght);
        update(node->rght, mid+1, ed, pos, val, copyFrom->rght);
    }
    node->sum = node->lft->sum + node->rght->sum;
}

int query(data* node, int st, int ed, int i, int j)
{
    if(i <= st && ed <= j)
        return node->sum;

    int mid = (st+ed)/2;
    int ret = 0;
    if(i <= mid)
        ret += query(node->lft, st, mid, i, j);
    if(j > mid)
        ret += query(node->rght, mid+1, ed, i, j);
    return ret;
}

int main()
{
//    freopen("maxon.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    sf(n);
    for(int i = 1; i<=n; i++)
        sf(A[i]);
    version[0] = new data();
    init(version[0],1,n);
    int q;
    sf(q);
    int type, idx, pos, st, ed, v;
    int cnt = 0;
    for(int i = 1; i<=q; i++)
    {
//        D(i);
        sff(type, idx);
        if(type == 1)
        {
            sff(pos, v);
            version[++cnt] = new data(version[idx]);
            update(version[cnt], 1, n, pos, v, version[idx]);
        }
        else
        {
            sff(st, ed);
            printf("%d\n",query(version[idx], 1, n, st, ed));
        }
    }
    return 0;
}
