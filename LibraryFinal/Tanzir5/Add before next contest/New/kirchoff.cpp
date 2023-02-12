#include<bits/stdc++.h>
using namespace std;
#define D(x)    cout << #x " = " <<(x) << endl
#define MAX     100
typedef long long int LL;

int edge[MAX+5][MAX+5]; /// edge[u][v] = number of edges between u & v

/*
    ----------------------
*/

LL mul(LL u, LL v, LL m)
{
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

LL kirchoff(int n, int m)
{
    if(n == 1) return 1;

    A.clear();
    A.resize(n);
    memset(deg, 0, sizeof(deg));

    for(int i = 0; i < n; i++) A[i].resize(n + 1);

    for(int u = 1; u <= n; u++)
        for(int v = u + 1; v <= n; v++){
            deg[u - 1] = add(deg[u - 1], edge[u][v], m), deg[v - 1] = add(deg[v - 1], edge[u][v], m);
            A[u - 1][v - 1] = A[v - 1][u - 1] = (-edge[u][v] % m + m) % m;
        }

    for(int i = 0; i < n; i++)
        A[i][i] = deg[i];


    B.clear();
    B.resize(n - 1);
    for(int i = 0; i < (int) B.size(); i++)
    {
        B[i].resize((int) A[i].size() - 1);
        for(int j = 0; j < (int) B[i].size(); j++)
            B[i][j] = A[i][j];
    }
    return gauss(B, m);
}

/*
    ----------------------
*/

int main()
{
    //freopen("in.txt", "r", stdin);
    int n = 5, i , j;

    for(i = 1; i <= n; i++)
        for(j = 1; j <= n; j++)
            if(i != j)
                edge[i][j] = 1;

    D(kirchoff(n, 1000000007));
    return 0;
}
