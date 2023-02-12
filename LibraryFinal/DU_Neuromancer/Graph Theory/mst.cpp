
// Minimum Spanning Tree
VI edge[MAX+10];
int par[MAX+10];  //n ->number of nodes
VI mst_tree[MAX+10], mst_cost[MAX+10];

struct Eg{
    int u, v, cost;
    Eg(){};
    Eg(int a, int b, int c) {u = a, v = b, cost = c; }
};
vector<Eg> E; // contains the edges

bool cmp(Eg a, Eg b) {return a.cost < b.cost; }

int find_parent(int idx)
{
    return par[idx] == idx? idx:par[idx] = find_parent(par[idx]);
}

int mst(int n)
{
    int i, ret = 0;
    Eg e;
    for(i = 0; i <= n; i++) par[i] = i;

    sort(E.begin(), E.end(), cmp);
    for(i = 0; i < (int) E.sz; i++)
    {
        e = E[i];
        if(find_parent(e.u) == find_parent(e.v)) continue;
        else
        {
            par[find_parent(e.u)] = find_parent(e.v), ret += e.cost;
            mst_tree[e.u].pb(e.v);
            mst_tree[e.v].pb(e.u);
            mst_cost[e.u].pb(e.cost);
            mst_cost[e.v].pb(e.cost);
        }
    }
    return ret;
}
