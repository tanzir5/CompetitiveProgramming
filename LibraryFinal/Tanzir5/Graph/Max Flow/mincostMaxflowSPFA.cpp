/// 0 based indexing

namespace mcmf{
    const int MAXN = ?, inf = ?;
    int src, snk, nNode, dist[MAXN+5], flow[MAXN+5], parent[MAXN+5];
    bool vis[MAXN+5];
    struct edgeData{
        int u, v, cost, cap, flow;
    };
    vector<edgeData> edges;
    vector<int>E[MAXN+5];
    void init(int _src, int _snk, int _n)
    {
        src = _src, snk = _snk, nNode = _n;
        edges.clear();
        for(int i = 0; i<nNode; i++)
            E[i].clear();
    }

    void inline add(int u, int v, int _cost, int _cap)
    {
        E[u].push_back(edges.size());
        edges.push_back({u,v,_cost,_cap,0});
        E[v].push_back(edges.size());
        edges.push_back({v,u,-_cost,0,0});
    }

    bool inline SPFA()
    {
        queue<int>q;
        mem(vis,false);
        for(int i = 0; i<nNode; i++)
            flow[i] = dist[i] = inf;
        vis[src] = true;
        dist[src] = 0;
        q.push(src);
        while(!q.empty())
        {
            int u = q.front();
            q.pop();
            vis[u] = false;
            for(int i = 0; i<E[u].size(); i++)
            {
                int idx = E[u][i];
                int v = edges[idx].v;
                int cost = edges[idx].cost;
                int cap = edges[idx].cap;
                int f = edges[idx].flow;
                if( f < cap &&  dist[v] > dist[u] + cost)
                {
                    dist[v] = dist[u]+cost;
                    parent[v] = idx;
                    flow[v] = min(flow[u], cap - f);
                    if(!vis[v])
                    {
                        q.push(v);
                        vis[v] = true;
                    }
                }
            }
        }
        return dist[snk] != inf;
    }

    pair<int,int> MCMF()
    {
        int totalFlow = 0, cost = 0;
        while(SPFA())
        {
            int u = snk;
            totalFlow += flow[snk];
            while(u != src)
            {
                edges[parent[u]].flow += flow[snk];
                edges[parent[u]^1].flow -= flow[snk];
                u =  edges[parent[u]].u;
            }
            cost += dist[snk] * flow[snk];
        }
        return {totalFlow, cost};
    }
}
