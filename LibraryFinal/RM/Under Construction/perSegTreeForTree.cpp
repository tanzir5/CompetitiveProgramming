
#include<bits/stdc++.h>
using namespace std;
#define D(x)    cout << #x " = " << (x) << endl
#define MAX     100000

vector<int> values, edge[MAX+5];
int w[MAX+5];

struct node{
    int sum;
    node *l, *r;

    node(){
        sum = 0;
        l = r = 0;
    }
} *segTree[MAX+5];

void init(node *t, int st, int ed){
    if(st == ed) return;
    t->l = new node;
    t->r = new node;

    int mid = (st + ed)/2;
    init(t->l, st, mid);
    init(t->r, mid+1, ed);
}

void ack(node *p, node *n, int st, int ed, int pos, int value){
    if(st == ed){
        n->sum = p->sum + value;
        return;
    }
    int mid = (st + ed)/2;

    if(pos <= mid){
        n->l = new node;
        n->r = p->r;
        ack(p->l, n->l, st, mid, pos, value);
    }
    else{
        n->r = new node;
        n->l = p->l;
        ack(p->r, n->r, mid+1, ed, pos, value);
    }
    n->sum = n->l->sum + n->r->sum;
}


#define MAXLG   17
#define MAXN    MAX
int Tab[MAXLG+2][MAXN+2], par[MAXN+2], lev[MAXN+2], stp;

void init_st(int n)
{
    int idx;

    for(idx = 1; idx <= n; idx++)
        Tab[0][idx] = par[idx];

    for(stp = 1; (1 << stp) < n; stp++)
        for(idx = 1; idx <= n; idx++)
            if(Tab[stp-1][idx] == -1) Tab[stp][idx] = -1;
            else Tab[stp][idx] = Tab[stp-1][Tab[stp-1][idx]];
    stp--;
}

int go(int cur, int gap, int pos)
{
    if(!gap) return cur;
    if(gap&1) return go(Tab[pos][cur], gap/2, pos+1);
    return go(cur, gap/2, pos+1);
}

int LCA(int u, int v)
{
    if(lev[u] > lev[v]) swap(u,v);
    v = go(v, lev[v]-lev[u], 0);
    if(u == v) return v;

    int i;
    for(i = stp; i >= 0; i--)
        if(Tab[i][u] != Tab[i][v])
            u = Tab[i][u], v = Tab[i][v];

    assert(Tab[0][u] > 0);
    return Tab[0][u];
}

void dfs(int idx, int p, node *s, int dpt = 0){
    par[idx] = p;
    lev[idx] = dpt;

    segTree[idx] = new node;
    ack(s, segTree[idx], 1, (int) values.size(), w[idx], +1);

    for(auto x : edge[idx]){
        if(x == p) continue;
        dfs(x, idx, segTree[idx], dpt + 1);
    }
}

int diablo(node *u, node *v, node *l, int st, int ed, int k, int wl){
    if(st == ed) return st;
    int mid = (st + ed)/2;

    int counter = u->l->sum + v->l->sum - l->l->sum * 2;
    if(st <= wl && wl <= mid) counter++;

    if(counter >= k) return diablo(u->l, v->l, l->l, st, mid, k, wl);
    else return diablo(u->r, v->r, l->r, mid+1, ed, k - counter, wl);
}

int query(int u, int v, int k){
    int l = LCA(u, v);
    return diablo(segTree[u], segTree[v], segTree[l], 1, (int) values.size(), k, w[l]) - 1;
}

int main(){
//    freopen("in.txt", "r", stdin);

    int i, n, m, u, v, k;

    scanf("%d %d", &n, &m);
    assert(n <= MAX);

    for(i = 1; i <= n; i++){
        scanf("%d", &w[i]);
        values.push_back(w[i]);
    }

    sort(values.begin(), values.end());
    values.erase(unique(values.begin(), values.end()), values.end());
    for(i = 1; i <= n; i++) w[i] = lower_bound(values.begin(), values.end(), w[i]) - values.begin() + 1;

    node *dummy = new node;
    init(dummy, 1, (int) values.size());

    for(i = 1; i < n; i++){
        scanf("%d %d", &u, &v);
        edge[u].push_back(v);
        edge[v].push_back(u);
    }

    dfs(1, -1, dummy);
    init_st(n);

    while(m--){
        scanf("%d %d %d", &u, &v, &k);
        printf("%d\n", values[query(u, v, k)]);
    }
    return 0;
}
