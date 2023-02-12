/*
    Spoj Plane Hopping
    Find all pair shortest paths where at least k edges are used in every path
    Use bellman ford equation(O(V*E*K)) with matrix expo(O(V^3*log2(K)))
    Modify Matrix multiplication with the bellman ford recurrence.
    Do V more multiplications to make sure you have got the best path.
*/

#include<bits/stdc++.h>
using namespace std;

#define D(x)    cerr << #x " = " << x << endl
#define mem(arr, x)     memset(arr, x, sizeof(arr))
typedef long long int LL;
struct mat{
    int r, c;
    LL arr[55][55];
    void print()
    {
        cout << endl << "Printing Matrix " << endl;
        for(int i = 0; i<r; i++)
        {
            for(int j = 0; j<c; j++)
                cout << arr[i][j] << " " ;
            cout << endl;
        }
    }
}M, A, B, id;
const LL inf = 1e19;
mat mul(mat a, mat b)
{
    mat ret;
    ret.r = a.r, ret.c = b.c;
    for(int i = 0; i<a.r; i++)
    {
        for(int j = 0; j<b.c; j++)
        {
            ret.arr[i][j] = inf;
            for(int k = 0; k<a.c; k++)
            {
                //ret.arr[i][j] += (a.arr[i][k] * b.arr[k][j])%MOD;
                ret.arr[i][j] = min(ret.arr[i][j], a.arr[i][k] + b.arr[k][j]);
               // ret.arr[i][j] %= MOD;
            }
        }
    }
    return ret;
}
int n;
void init()
{
    id.r = id.c = n;
    for(int i = 0; i<id.r; i++)
    {
        for(int j = 0; j<id.c; j++)
            id.arr[i][j] = A.arr[i][j];
    }
    M.r = M.c = (n);

    A.r = n, A.c = n;
}

mat mat_exp(mat M, LL n)
{
    mat ret = id;
    while(n)
    {
        if(n&1) ret = mul(ret, M);
        n>>=1;
        M = mul(M,M);
    }
    return ret;
}
LL ans[55][55];
int main()
{
    int i, j, k, cs, t;
    scanf("%d",&t);
    for(cs = 1; cs<=t; cs++)
    {
        scanf("%d %d",&k,&n);
        for(i = 0; i<n; i++)
        {
            for(j = 0; j<n; j++)
                scanf("%d",&A.arr[i][j]), M.arr[i][j] = A.arr[i][j];
        }
        init();
        M = mat_exp(M, k-1);
        for(i = 0; i<n; i++)
        {
            for(j = 0; j<n; j++)
            {
                ans[i][j] = M.arr[i][j];
            }
        }

        for(k = 1; k<=n; k++)
        {
            M = mul(M, A);
            for(i = 0; i<n; i++)
            {
                for(j = 0; j<n; j++)
                {
                    ans[i][j] = min(ans[i][j], M.arr[i][j]);
                }
            }
        }
        printf("Region #%d:\n",cs);
        for(i = 0; i<n; i++)
        {
            for(j = 0; j<n; j++)
            {
                if(j)
                    printf(" ");
                printf("%lld",ans[i][j]);
            }
            puts("");
        }
        puts("");
    }

}
