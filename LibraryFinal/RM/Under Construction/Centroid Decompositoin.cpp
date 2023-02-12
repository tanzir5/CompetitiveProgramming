
#include<bits/stdc++.h>
using namespace std;
typedef long long int LL;

#define MAXN        100000
#define MAXLG       17

struct centroid_tree
{
    LL tab[MAXLG+3][MAXN+3];
    vector<LL>dlist[MAXN+5];

    int par[MAXN+3], depth[MAXN+3], subsize[MAXN+3];
    vector<int> child[MAXN+3], edge[MAXN+3], cost[MAXN+3];
    bool vis[MAXN+3];

    /*
        Do u really need child wise data?
    */
    vector< vector< LL > > childwise[MAXN+3];
    int ch_id[MAXN+3];

    void dfs(int idx, int &r, int p = -1)
    {
        subsize[idx] = 1;
        for(auto x : edge[idx])
        {
            if(x == p) continue;
            if(vis[x])
            {
                if(r == -1) r = x;
                else if(depth[x] > depth[r]) r = x;
                continue;
            }
            dfs(x, r, idx);
            subsize[idx] += subsize[x];
        }
    }

    void find(int idx, int &c, int n, int p = -1)
    {
        int mx = 0;
        for(auto x : edge[idx])
        {
            if(x == p)
            {
                mx = max(mx, n - subsize[idx]);
                continue;
            }
            else if(vis[x]) continue;
            mx = max(mx, subsize[x]);
            find(x, c, n, idx);
        }

        if(mx <= n/2) c = idx;
    }

    void preprocess(int idx, int r, LL d = 0, int p = -1)
    {
        tab[depth[r]][idx] = d;
        dlist[r].push_back(d);

        int i, v, w;
        for(i = 0; i < (int) edge[idx].size(); i++)
        {
            v = edge[idx][i];
            w = cost[idx][i];

            if(v == p) continue;
            if(vis[v]) continue;
            preprocess(v, r, d + w, idx);
        }
    }

    void dfs1(int r, int idx, int ch = -1){
        if(ch != -1) childwise[r][ch].push_back(tab[depth[r]][idx]);

        for(int i = 0; i < (int) child[idx].size(); i++){
            if(ch == -1) dfs1(r, child[idx][i], i);
            else dfs1(r, child[idx][i], ch);
        }
    }

    void build(int n)
    {
        int iter = 1;

        while(iter <= n)
        {
            if(vis[iter]) iter++;
            else
            {
                int r = -1, c = -1;
                dfs(iter, r);
                find(iter, c, subsize[iter]);

                assert(c != -1);
                if(r != -1)
                {
                    ch_id[c] = child[r].size();
                    child[r].push_back(c);
                    childwise[r].push_back(vector<LL>());
                    depth[c] = depth[r] + 1;
                }
                else depth[c] = 0;

                par[c] = r;
                vis[c] = true;
                preprocess(c, c);
            }
        }

        for(int i = 1; i <= n; i++)
            dfs1(i, i);

        for(int i = 1; i <= n; i++)
        {
            sort(dlist[i].begin(), dlist[i].end());
            for(auto &l : childwise[i])
                sort(l.begin(), l.end());
        }
    }

    /*
        number of nodes within distance bound, from the node idx
    */
    int query(int idx, LL bound){
        int ret = upper_bound(dlist[idx].begin(), dlist[idx].end(), bound) - dlist[idx].begin();
        int u = idx;
        int p = par[u];

        while(p != -1){
            LL taken = tab[depth[p]][idx];
            if(taken <= bound){
                int counter = upper_bound(dlist[p].begin(), dlist[p].end(), bound - taken) - dlist[p].begin();
                int invalid = upper_bound(childwise[p][ch_id[u]].begin(), childwise[p][ch_id[u]].end(),  bound - taken) - childwise[p][ch_id[u]].begin();
                assert(invalid <= counter);
                ret += counter - invalid;
            }

            u = par[u];
            p = par[u];
        }

        return ret;
    }
} ctree;

int main()
{
    //    freopen("in.txt", "r", stdin);
    int n, q, i, u, v, w;
    LL bound;

    scanf("%d %d", &n, &q);
    for(i = 1; i < n; i++){
        scanf("%d %d %d", &u, &v, &w);
        ctree.edge[u].push_back(v);
        ctree.edge[v].push_back(u);

        ctree.cost[u].push_back(w);
        ctree.cost[v].push_back(w);
    }

    ctree.build(n);
    while(q--){
        scanf("%d %lld", &v, &bound);
        printf("%d\n", ctree.query(v, bound));
    }
    return 0;
}
