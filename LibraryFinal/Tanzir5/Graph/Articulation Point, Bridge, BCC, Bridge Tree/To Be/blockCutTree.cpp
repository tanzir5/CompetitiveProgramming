#include<bits/stdc++.h>
using namespace std;
#define MAX     100000
#define pb      push_back
#define mem(t, v)   memset ((t) , v, sizeof(t))
#define D(x)        cerr << #x " = " << x << '\n'
int n, m;
/// Decomposes the graph into  Biconnected Components and also finds the articulation points
/// n is the number of nodes
/// BCC[i] will contain the nodes of i'th BCC
/// AP will contain the articulation points
/// 1 based indexing
typedef long long int LL;
vector<int> E[MAX+10], stck, BCC[MAX+10], AP, id[MAX+10];
int low[MAX+10], disc[MAX+10], BCC_cnt, parent[MAX+10];
bool vis[2*MAX+10], pushed[MAX+10];

bool is_AP(int u, int v, int children)
{
    if(parent[u] == -1)
    {
        /// u is root and has two children who have no connection except the root. so it's an articulation point.
        if(children > 1)
            return true;
        return false;
    }
    else
    {
        /// There is no backedge towards u's ancestor from any node of the subtree from u going through v and u is not a root.
        /// so u must be an articulation point
        if(low[v] >= disc[u])
            return true;
        return false;
    }
}

void dfs(int node)
{
    vis[node] = 1;
    stck.push_back(node);
    if(parent[node] == -1)
        disc[node] = low[node] = 1;
    else
        disc[node] = low[node] = disc[parent[node]]+1;

    int children = 0, v, u = node;
    for(int i = 0; i<E[u].size();i++)
    {
        v = E[u][i];
        if( !vis[v] )
        {
            children++;
            parent[v]=u;
            dfs(v);
            low[u]=min(low[u],low[v]);
            if(is_AP(u, v, children))
            {
                if(!pushed[u])
                    AP.pb(u);
                pushed[u] = 1;
                BCC_cnt++;
                BCC[BCC_cnt].push_back(u);
                id[u].pb(BCC_cnt);
                while(true)
                {
                    int nw = stck.back();
                    BCC[BCC_cnt].pb(nw);
                    id[nw].pb(BCC_cnt);
                    stck.pop_back();
                    if(nw == v)
                        break;
                }
            }
        }
        else if( v != parent[u])
            low[u] = min(low[u],disc[v]);
    }
    return;
}


void find_BCC()
{
    for(int i = 0; i<=MAX; i++)
        BCC[i].clear();
    mem(parent, -1);
    BCC_cnt = 0;
    mem(vis, 0);
    AP.clear();
    mem(pushed, 0);
    for(int i = 1; i<=n; i++)
    {
        if(!vis[i])
        {
            dfs(i);
            if(!stck.empty())
                BCC_cnt++;
            while(!stck.empty())
            {
                BCC[BCC_cnt].pb(stck.back());
                id[stck.back()].pb(BCC_cnt);
                stck.pop_back();
            }
        }
    }
}

vector<int>tree[MAX*2+10];
int total[MAX+10], leaderOf[MAX+10];
int dfs2(int node, int leader)
{
    leaderOf[node] = leader;
    vis[node] = true;
    int ret = 1;
    for(int i = 0; i<E[node].size(); i++)
    {
        int v = E[node][i];
        if(!vis[v])
            ret += dfs2(v, leader);
    }
    return ret;
}
int actual[MAX*2+10], nodeCnt[MAX*2+10];
LL ans[MAX+10];

int call(int node)
{
    vis[node] = true;
    int ret = 0;
    int u;
    LL t;
    if(actual[node])
    {
        u = actual[node];
        t = total[leaderOf[u]];
    }
    for(int i = 0; i<tree[node].size(); i++)
    {
        int v = tree[node][i];
        if(!vis[v])
        {
            int nw = call(v);
            ret += nw;
            if(actual[node])
                ans[u] += (t - nw - 1)*nw;
        }
    }
    if(actual[node])
    {
        ans[u] += (t - ret - 1)*ret;
        ans[u] /= 2;
    }
    ret += nodeCnt[node];
    return ret;
}

void solve()
{
    mem(total,0);
    mem(vis,0);
    mem(ans,0);
    mem(actual,0);
    for(int i = 1; i<=n; i++)
    {
        if(!vis[i])
            total[i] = dfs2(i,i);
    }
    find_BCC();
//    D(AP.size());
    for(int i = 1; i<=BCC_cnt; i++)
    {
        nodeCnt[i] = BCC[i].size();
        for(int j = 0; j<BCC[i].size(); j++)
        {
            if(pushed[BCC[i][j]])
                nodeCnt[i]--;
        }
    }
    for(int i = 0; i<AP.size(); i++)
    {
        int u = AP[i];
        BCC_cnt++;
        for(int j = 0; j<id[u].size(); j++)
            tree[BCC_cnt].pb(id[u][j]), tree[id[u][j]].pb(BCC_cnt);
        nodeCnt[BCC_cnt] = 1;
        actual[BCC_cnt] = u;
    }

    mem(vis,0);
    for(int i = 1; i<=BCC_cnt;i++)
    {
        if(!vis[i])
            call(i);
    }

    for(int i = 1; i<=n; i++)
    {
        ans[i] += total[leaderOf[i]]-1;
        printf("%lld\n",ans[i]);
    }
    for(int i = 1; i<=BCC_cnt; i++)
        tree[i].clear();
    for(int i = 1; i<=n; i++)
        id[i].clear();

}

int main()
{
//    freopen("inSubtask3.txt", "r", stdin);
//    freopen("outSubtask3BlockCut.txt", "w", stdout);
    int cs, t, u, v;
    assert(scanf("%d",&t));
    for(cs = 1; cs<=t; cs++)
    {
        assert(scanf("%d %d",&n,&m) == 2);
        for(int i = 1; i<=m; i++)
        {
            assert(scanf("%d %d",&u,&v) == 2);
            E[u].pb(v);
            E[v].pb(u);
        }
        printf("Case %d:\n",cs);
        solve();
        for(int i = 1; i<=n; i++)
            E[i].clear();
    }
    assert(scanf("%d",&t) == EOF);
}
