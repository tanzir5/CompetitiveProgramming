vector<int>E[MAX+10];
int subtreeSize[MAX+10];

int getSize(int node, int par);

void add(int node, int par, int x, int bigChild = -1)
{
    /// Do whatever you have to do for this node with the command x
    for(auto v: E[node])
    {
        if(v == par || v == bigChild)
            continue;
        add(v, node, x);
    }
}

void dfs(int node, int par, bool keep)
{
    int bigChild = -1;
    for(auto v: E[node])
    {
        if(v == par)
            continue;
        if(bigChild == -1 || (subtreeSize[bigChild] < subtreeSize[v]))
            bigChild = v;
    }
    for(auto v: E[node])
    {
        if(v == par || v == bigChild)
            continue;
        dfs(v, node, 0);
    }
    if(bigChild != -1)
        dfs(bigChild, node, 1);
    add(node, par, 1, bigChild);
    /// my needed array is ready. Handle query next

    /// Clear solution as I'm not a bigchild. :(
    if(keep == 0)
    {
        add(node, par, -1);
    }
}
