
#include<bits/stdc++.h>
using namespace std;
#define D(x)    cout << #x " = " << (x) << endl
#define MAX     100
typedef long long int LL;
/*
    way[i][j] = number of ways to create the j-th vertex module the i-th prime
    No loops / multi - edge
    Must be undirected
    MUST CALL CLEAR BEFORE CALLING RESIZE on A
*/

int mod[] = {3, 10337}, way[2][MAX+5], edge[MAX+5][MAX+5], n, nxt_edge[MAX+5][MAX+5], nxt_way[2][MAX+5], par[MAX+5], counter[MAX+5][MAX+5], nxt_counter[MAX+5][MAX+5];
vector<int> wlist, nodeList[MAX+5];
bool vis[MAX+5];

void dfs(int idx, int cmpNo, int cost)
{
    if(vis[idx]) return;

    par[idx] = cmpNo;
    vis[idx] = true;
    nodeList[cmpNo].push_back(idx);

    for(int i = 1; i <= n; i++)
        if(edge[idx][i] == cost)
            dfs(i, cmpNo, cost);
}

LL mul(LL u, LL v, LL m)
{
    if(u >= m) u %= m;
    if(v >= m) v %= m;
    LL ret = u * v;
    if(ret >= m) return ret % m;
    return ret;
}

LL add(LL u, LL v, LL m)
{
    return (u + v) % m;
}

LL sub(LL u, LL v, LL m)
{
    LL ret = (u - v) % m;
    if(ret < 0) ret += m;
    return ret;
}

LL ip(LL a, LL p, LL m)
{
    if(!p) return 1;
    if(p & 1) return mul(a, ip(a, p - 1, m), m);
    LL ret = ip(a, p/2, m);
    return mul(ret, ret, m);
}

LL mod_inv(LL v, LL m){return ip(v, m - 2, m);}

int gauss(vector < vector < int > > A,  int m){
    int eqn = A.size();
    int var = A.back().size() - 1, i, j;
    vector<int> where;
    where.resize(var, -1);
    LL c, d = 1, ret = 1;


    for(int clm = 0, row = 0; clm < var && row < eqn; clm++){
        if(!A[row][clm])
            for(i = row + 1; i < eqn; i++)
                if(A[i][clm]) {
                    for(j = 0; j <= var; j++)
                        swap(A[i][j], A[row][j]);
                    d = (-d) % m;
                    if(d < 0) d += m;

                    break;
                }

        if(!A[row][clm]) {continue;}
        where[clm] = row;

        for(c = mod_inv(A[row][clm], m), i = 0, d = mul(d, c, m); i <= var; i++) {
            A[row][i] = mul( A[row][i] , c , m);
        }

        for(i = 0; i < eqn; i++)
            if(i == row) continue;
            else
                for(c = A[i][clm], j = 0; j <= var; j++) {
                        A[i][j] = sub(A[i][j] , mul(A[row][j] , c, m), m);
                    }
        row++;
    }

    for(i = 0; i < eqn; i++)
        ret = mul(ret, A[i][i], m);

    d = mod_inv(d, m);
    return mul(ret, d, m);
}

vector< vector<int> > A, B;
int deg[MAX+5];

LL kirchoff(vector<int> node, int cost, int m)
{
    if(node.size() == 1) return 1;

    A.clear();
    A.resize(node.size());
    memset(deg, 0, sizeof(deg));

    for(int i = 0; i < (int) node.size(); i++) A[i].resize(node.size() + 1);

    for(int i = 0; i < (int) node.size(); i++)
        for(int j = i + 1; j < (int) node.size(); j++){
            int u = node[i];
            int v = node[j];

            if(edge[u][v] == cost){
                deg[i] = add(deg[i], counter[u][v], m), deg[j] = add(deg[j], counter[u][v], m);
                A[i][j] = A[j][i] = (-counter[u][v] % m + m) % m;
            }
        }

    for(int i = 0; i < (int) node.size(); i++)
        A[i][i] = deg[i];


    B.clear();
    B.resize(node.size() - 1);
    for(int i = 0; i < (int) B.size(); i++)
    {
        B[i].resize((int) A[i].size() - 1);
        for(int j = 0; j < (int) B[i].size(); j++)
            B[i][j] = A[i][j];
    }

    return gauss(B, m);
}

void _merge(int cost)
{
    int i, p, w, j, cmpNo = 0;
    memset(vis, 0, sizeof(vis));

    for(i = 1; i <= n; i++)
        if(vis[i] == false){
            cmpNo++;
            nodeList[cmpNo].clear();
            dfs(i, cmpNo, cost);

            for(p = 0; p < 2; p++)
            {
                w = kirchoff(nodeList[cmpNo], cost, mod[p]);

                for(auto x : nodeList[cmpNo]) w = (w * (LL) way[p][x]) % mod[p];
                nxt_way[p][cmpNo] = w;
            }
        }

    for(i = 1; i <= n; i++)
        for(j = 1; j <= n; j++)
            nxt_edge[i][j] = numeric_limits<int>::max();

    for(i = 1; i <= n; i++)
        for(j = 1; j <= n; j++)
            if(edge[i][j] != numeric_limits<int>::max()){
                int u = par[i];
                int v = par[j];

                if(u == v) continue;

                if(edge[i][j] < nxt_edge[u][v]){
                    nxt_edge[u][v] = edge[i][j];
                    nxt_counter[u][v] = counter[i][j];
                }
                else if(edge[i][j] == nxt_edge[u][v])
                {
                    nxt_counter[u][v] += counter[i][j];
                }
            }

    n = cmpNo;
    for(p = 0; p < 2; p++)
        for(i = 1; i <= n; i++)
            way[p][i] = nxt_way[p][i];

    for(i = 1; i <= n; i++)
        for(j = 1; j <= n; j++)
        {
            edge[i][j] = nxt_edge[i][j];
            counter[i][j] = nxt_counter[i][j];
        }
}

vector<int> prime;
vector<int> rm;

int crt()
{
    LL M = 1, ret = 0, b, c;
    for(auto x : prime)
        M = M * x;

    for(int i = 0; i < (int) prime.size(); i++){
        b = mod_inv( M / prime[i], prime[i]);
        c = (b * rm[i]) % M;
        c = (c * M/prime[i]) % M;
        ret = (ret + c) % M;
    }
    return ret;
}

int main()
{
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);


    int p, m, u, v, w, i, j, itr;

    scanf("%d %d", &n, &m);

    for(i = 1; i <= n; i++)
        for(j = 1; j <= n; j++)
            edge[i][j] = numeric_limits<int>::max();

    for(p = 0; p < 2; p++)
        for(i = 1; i <= n; i++)
            way[p][i] = 1;


    for(i = 1; i <= m; i++)
    {
        scanf("%d %d %d", &u, &v, &w);
        edge[u][v] = edge[v][u] = w;
        counter[u][v] = counter[v][u] = 1;

        wlist.push_back(w);
    }

    sort(wlist.begin(), wlist.end());
    wlist.erase(unique(wlist.begin(), wlist.end()), wlist.end());

    itr = 0;
    while(n != 1){
        assert(itr < wlist.size());
        w = wlist[itr++];
        _merge(w);
    }

    for(p = 0; p < 2; p++) {
        prime.push_back(mod[p]);
        rm.push_back(way[p][1]);
    }

    printf("%d\n", crt());
    return 0;
}
