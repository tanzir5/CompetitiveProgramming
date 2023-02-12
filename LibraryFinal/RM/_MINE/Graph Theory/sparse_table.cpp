
//Sparse Table
#define MAXLG   17
#define MAXN    10000
int Tab[MAXLG+5][MAXN+11], par[MAXN+11], lev[MAXN+11], stp; // par->parent, lev = level;

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
