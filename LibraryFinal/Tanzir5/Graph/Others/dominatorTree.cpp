//1-Based directed graph input
#define MAX		200000
vector<int> g[MAX+5],tree[MAX+5],rg[MAX+5],bucket[MAX+5];
int sdom[MAX+5],par[MAX+5],dom[MAX+5],dsu[MAX+5],label[MAX+5];
int arr[MAX+5],rev[MAX+5],T,n, source;
void init(int _n, int _source)
{
    T = 0;
    n = _n;
    source = _source;
    for(int i = 1; i<=n; i++)
    {
        g[i].clear(), rg[i].clear(), tree[i].clear(), bucket[i].clear();
        arr[i] = sdom[i] = par[i] = dom[i] = dsu[i] = label[i] = rev[i] = 0;
    }
}
void dfs(int u)
{
    T++;
    arr[u]=T;
    rev[T]=u;
    label[T]=T;
    sdom[T]=T;
    dsu[T]=T;
    for(int i=0; i<g[u].size(); i++)
    {
        int w = g[u][i];
        if(!arr[w])
        {
            dfs(w);
            par[arr[w]]=arr[u];
        }
        rg[arr[w]].push_back(arr[u]);
    }
}

int Find(int u,int x = 0)
{
    if(u==dsu[u])return x?-1:u;
    int v = Find(dsu[u],x+1);
    if(v<0)return u;
    if(sdom[label[dsu[u]]]<sdom[label[u]])
        label[u] = label[dsu[u]];
    dsu[u] = v;
    return x?v:label[u];
}
void Union(int u,int v)  //Add an edge u-->v
{
    dsu[v]=u;
}

void build()
{
    dfs(source);
    for(int i=n; i>=1; i--)
    {
        for(int j=0; j<rg[i].size(); j++)
            sdom[i] = min(sdom[i],sdom[Find(rg[i][j])]);
        if(i>1)bucket[sdom[i]].push_back(i);
        for(int j=0; j<bucket[i].size(); j++)
        {
            int w = bucket[i][j],v = Find(w);
            if(sdom[v]==sdom[w]) dom[w]=sdom[w];
            else dom[w] = v;
        }
        if(i>1)Union(par[i],i);
    }

    for(int i=2; i<=n; i++)
    {
        if(dom[i]!=sdom[i])dom[i]=dom[dom[i]];
//        tree[rev[i]].push_back(rev[dom[i]]);
        tree[rev[dom[i]]].push_back(rev[i]);
    }
}
