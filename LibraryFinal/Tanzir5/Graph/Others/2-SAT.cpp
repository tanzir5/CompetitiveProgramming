/*
    1 based indexing
    2-SAT
    Finds if 2-SAT is possible and also prints the solution if possible.
    Solution to the problem LOJ - Forming the council
    Problem Description:
    In a city there are n voters, and m people formed the Govt. council. The council members are numbered from 1 to
    m. Now everyone is complaining that the council is biased. So, they made a plan. The plan is that the voters are
    given a chance to vote again to form the new council. A vote will be like ±i ±j. '+' means the voter wants that member
    to be in the council, '-' means the voter doesn't want the member to be in the council. For example, there are 4 voters,
    they voted like
    +1 -3    the voter wants member 1 to be kept in the council or member 3 to be thrown out
    +2 +3  the voter wants member 2 to be kept in the council or member 3 to be kept in the council
    -1 -2     the voter wants member 1 to be thrown out or member 2 to be thrown out
    -4 +1    the voter wants member 4 to be thrown out or member 1 to be kept in the council
    A voter will be satisfied if at least one of his wishes becomes true. Now your task is to form the council such that all
    the voters are happy.

    Input:
    Input starts with an integer T (≤ 20), denoting the number of test cases.
    Each case starts with a line containing two integers n (1 ≤ n ≤ 20000) and m (1 ≤ m ≤ 8000). Each of the next n lines contains a vote in the form ±i ±j (1 ≤ i, j ≤ m).
    Output:
    For each case, print the case number and 'Yes' if a solution exists, or 'No' if there is no solution. Then if the result is yes, print another line containing the number of members in the council followed by the members in ascending order. And print a single space between two numbers. There can be many solutions. Any valid one will do.
*/
#define MAX         16010
int m, n, cnt;
/// total nodes = n
/// i is i, -i is n+i
int actual(int a)
{
    if(a < 0)
        return n+(-a);
    else
        return a;
}
/// sqnc holds sequence of the nodes obtained from the reversed graph
/// E holds the edges
/// component[i] holds the nodes in i'th component
/// scc holds the compressed graph description with each component as one node
vector<int> E[MAX+10], sqnc, REV[MAX+10], component[MAX+10], scc[MAX+10];

/// TIME holds every node of the components with their time after topologically sorting them
/// xx means time, yy means the node.
/// The starting node has the largest time.
vector <pii> TIME;
/// state holds the final state of the nodes after satisfying everyone
bool state[MAX+10];
int vis[MAX+10], TM[MAX+10];
/// lead means the current leader under whom everyone who will go in the component
/// leader[i] signifies the leader of node i in the component
int  lead, leader[MAX+10];
/// Runs DFS on the reversed graph
void dfsRev(int node)
{
    if(vis[node])
        return;
    int i;
    vis[node]=1;

    FRL(i,0,REV[node].size())
        dfsRev(REV[node][i]);

    sqnc.pb(node);
    return;
}
/// dfs to create the components and the compressed graph
void dfs(int node)
{
    if(vis[node]==-1)
        return;
    if(vis[node])
    {
        if(leader[node]!=lead )
            scc[lead].pb(leader[node]);
        return;
    }
    int i;
    leader[node]=lead;
    component[lead].pb(node);
    vis[node]=-1;
    FRL(i,0,E[node].size())
        dfs(E[node][i]);

    vis[node]=1;
    return;

}
/// topologically sorts the components
int topo_sort(int node)
{
    if(vis[node]!=-1)
        return TM[node];
    int i,ret=0;
    for(i=0;i<scc[node].size();i++)
        ret=max(ret,topo_sort(scc[node][i]));
    TIME.pb({ret,node});
    vis[node] = 1;
    TM[node] = ret;
    return ret+1;
}
void SCC()
{
    /// find out the order in the reversed graph
    int i;
    sqnc.clear();
    mem(vis,0);
    FRE(i,1,2*n)
    {
        if(!vis[i])
            dfsRev(i);
    }
    /// run dfs from the end of sqnc
    mem(vis,0);
    lead=0;
    for(i=(2*n)-1;i>=0;i--)
    {
        if(!vis[sqnc[i]])
        {
            lead++;
            dfs(sqnc[i]);
        }
    }
}
bool two_Sat()
{
    int i, u, v, j;
    SCC();
    /// if leader of i and -i is the same, then they are in the same component
    /// 2-sat is impossible, return 0
    FRE(i,1,n)
    {
        if(leader[i]==leader[i+n])
            return 0;
    }
    /// topologically sort the components
    mem(vis,-1);
    TIME.clear();
    FRE(i,1,lead)
    {
        if(vis[i] == -1)
            topo_sort(i);
    }
    /// start from the back end of topologically sorted order and try to give everyone true state in that component
    /// if someone's opposite has true state, then let him have false state.
    sort(all(TIME));
    mem(state, 0);
    FRL(i,0,TIME.size())
    {
        v = TIME[i].yy;
        FRL(j,0,component[v].size())
        {
            u = component[v][j];
            if(( u>n && !state[u-n]) || ( u<=n && !state[u+n]))
            {
                if(u <= n)
                    cnt++;
                state[u]=1;
            }
        }
    }
    return 1;
}
void add(int u, int v)
{
    u = actual(u);
    v = actual(v);
    E[u].pb(v);
    REV[v].pb(u);
}
void _or(int u, int v)
{
    add(-u, v);
    add(-v, u);
}
int main()
{
    int cs, t, i, j, u, v;

    sf(t);
    FRE(cs,1,t)
    {
        cnt = 0;
        FRE(i,1,MAX)
        {
            E[i].clear();
            REV[i].clear();
            scc[i].clear();
            component[i].clear();
        }
        sff(m,n);

        FRE(i,1,m)
        {
            sff(u, v);
            _or(u,v);
        }
        printf("Case %d: ",cs);
        if(!two_Sat())
            printf("No\n");
        else
        {
            printf("Yes\n");
            printf("%d",cnt);
            FRE(i,1,n)
            {
                if(state[i])
                    printf(" %d",i);
            }
            printf("\n");
        }
    }
}
