/*
    MAX must be equal to the maximum number of variables.
    n passed in init() is the number of variables.
    O(V+E)
    !a is represented as -a.
    example xor:
    |a|b|
    |0|0| x  or(a,b)
    |0|1|
    |1|0|
    |1|1| x  or(-a,-b)
    do OR of negation of values of variables for each undesired situation to make it impossible.
*/
#define MAX         ?
struct twoSat{
    int n;
    vector<int> E[MAX*2+10], V, Rev[MAX*2+10], sortedNodes;
    bool state[MAX*2+10], vis[MAX*2+10];
    int compId[MAX*2+10];

    void init(int _n)
    {
        n = _n;
        for(int i = 0; i<=2*n; i++)
            E[i].clear(), Rev[i].clear();
        V.clear();
        sortedNodes.clear();
        mem(state, 0);
    }

    inline int actual(int a)
    {
        if(a < 0)
            return n - a;
        else
            return a;
    }

    inline int neg(int a)
    {
        if(a > n)
            return a-n;
        else
            return n+a;
    }

    void dfs(int node)
    {
        vis[node] = true;
        for(auto v: E[node])
        {
            if(!vis[v])
                dfs(v);
        }
        V.push_back(node);
    }

    void dfsRev(int node, int id)
    {
        sortedNodes.push_back(node);
        vis[node] = true;
        compId[node] = id;
        for(auto v: Rev[node])
        {
            if(!vis[v])
                dfsRev(v, id);
        }
    }

    void buildSCC()
    {
        int i;
        V.clear();
        mem(vis,0);
        for(int i = 1; i<=2*n; i++)
        {
            if(!vis[i])
                dfs(i);
        }
        mem(vis,0);
        reverse(all(V));
        int cnt = 0;
        for(auto u: V)
        {
            if(!vis[u])
                cnt++,dfsRev(u, cnt);
        }
    }

    bool topologicalOrder(int a, int b)
    {
        return compId[a] < compId[b];
    }
    bool satisfy()
    {
        buildSCC();
        /// if leader of i and -i is the same, then they are in the same component
        /// 2-sat is impossible, return 0
        for(int i = 1; i<=n; i++)
        {
            if(compId[i]==compId[i+n])
                return 0;
        }
        /// topologically sort the components

        /// start from the back end of topologically sorted order and try to give everyone true state in that component
        /// if someone's opposite has true state, then let him have false state.
        for(int i = (int)sortedNodes.size()-1; i>=0; i--)
        {
            int u = sortedNodes[i];
            if( state[neg(u)] == 0)
                state[u]=1;
        }
        return 1;
    }

    void addEdge(int u, int v)
    {
        u = actual(u);
        v = actual(v);
        E[u].pb(v);
        Rev[v].pb(u);
    }
    void addOr(int u, int v)
    {
        addEdge(-u, v);
        addEdge(-v, u);
    }

    void addXor(int u, int v)
    {
        addOr(u,v);
        addOr(!u,!v);
    }

    void forceTrue(int u)
    {
        addEdge(-u, u);
    }
    void forceFalse(int u)
    {
        addEdge(u,-u);
    }

    void addOriginalImplication(int u, int v)
    {
        addOr(-u,v);
    }
}solver;
