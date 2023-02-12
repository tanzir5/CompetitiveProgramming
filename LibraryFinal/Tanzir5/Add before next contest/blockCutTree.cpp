namespace BCT{
/*
    1 based indexing
    Basic idea:
    In the block cut tree(BCT), each BCC will be a node and each articulation point will be a node.
    Each edge will be between an articulation point and a BCC whose part is that articulation point.
    Remember, only articulation points can be part of more than one BCC. Normal nodes will be part
    of only one BCC. So you need to do something with node u of NORMAL GRAPH, you do that something
    with the node that represents BCC of u ( if u is not an articulation point ) or the node that
    represents u ( if u is an articulation point ) in the BCT.  myBCC[u].back() will be the representative
    of u in both case. myBCC[] and tree[] are the things that you would need to access for solving problems.
    isAP[u] will tell you if node u of the NEW TREE is an articulation point or not.
    *** MAX must be twice as big as maximum number of nodes.
    *** _n is the number of nodes in initial graph. nNode will be the number of nodes in the block cut tree.
*/
#define MAX     ?
vector<int> E[MAX+10], stck, BCC[MAX+10], AP, myBCC[MAX+10];
int n, m, low[MAX+10], disc[MAX+10], BCC_cnt, parent[MAX+10], sizeOfBCC[MAX+10];
bool vis[MAX+10], pushed[MAX+10], isAP[MAX+10];
bool checkAP(int u, int v, int children)
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
            if(checkAP(u, v, children))
            {
                if(!pushed[u])
                    AP.pb(u);
                pushed[u] = 1;
                BCC_cnt++;
                myBCC[u].push_back(BCC_cnt);
                BCC[BCC_cnt].push_back(u);
                while(true)
                {
                    int nw = stck.back();
                    myBCC[nw].pb(BCC_cnt);
                    BCC[BCC_cnt].pb(nw);
                    stck.pop_back();
                    if(nw == v)
                        break;
                }
            }
        }
        else if( v !=parent[u])
            low[u] = min(low[u],disc[v]);
    }
    return;
}


void find_BCC()
{
    for(int i = 0; i<=MAX; i++)
        BCC[i].clear(), myBCC[i].clear();
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
                myBCC[stck.back()].pb(BCC_cnt);
                BCC[BCC_cnt].pb(stck.back());
                stck.pop_back();
            }
        }
    }
}

vector<int>tree[MAX+10];
void createBlockCutTree(int _n, int &nNode)
{
    mem(isAP, 0);
    for(int i = 1; i<=MAX; i++)
        tree[i].clear();
    n = _n;
    find_BCC();
    for(int i = 1; i<=BCC_cnt; i++)
        sizeOfBCC[i] = BCC[i].size();
    for(int i = 1; i<=n; i++)
    {
        if(myBCC[i].size() > 1)
        {
            BCC_cnt++;
            for(int j = 0; j<myBCC[i].size(); j++)
            {
                int u = myBCC[i][j];
                int v = BCC_cnt;
                tree[u].push_back(v);
                tree[v].push_back(u);

                sizeOfBCC[u]--;
            }
            myBCC[i].push_back(BCC_cnt);
            BCC[BCC_cnt].pb(i);
            isAP[BCC_cnt] = true;
            sizeOfBCC[BCC_cnt] = 1;
        }
    }
    nNode = BCC_cnt;
}
}
