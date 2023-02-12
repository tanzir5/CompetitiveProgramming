#include<bits/stdc++.h>
using namespace std;
typedef long long int LL;
typedef unsigned int ui;
#define MAX     50

ui ncr[MAX+10][MAX+10];

///Matrix Exponentiation
#define DIM 50
struct matrix{
    ui mat[DIM+5][DIM+5], dim;
    matrix(){}
    matrix(int d){
        int i,j;
        dim = d;
        for(i = 1; i <= dim; i++)
            for(j = 1; j <= dim; j++)
                mat[i][j] = (i == j);
    }
    matrix operator * (const matrix &r){
        int i, j, k;
        matrix ret = matrix(dim);
        assert(dim == r.dim);
        for(i = 1; i <= dim; i++)
            for(j = 1; j <= dim; j++)
            {
                ret.mat[i][j] = 0;
                for(k = 1; k <= ret.dim; k++)
                    ret.mat[i][j] = ret.mat[i][j] + (mat[i][k]*r.mat[k][j]);
            }
        return ret;
    }
};

matrix expo(matrix &in, LL p)
{
    matrix ret = matrix(in.dim), aux = in;
    while(p)
    {
        if(p&1) ret = ret*aux;
        aux = aux*aux;
        p>>=1;
    }
    return ret;
}

ui f(LL n, int k)
{
    matrix base;
    int i,j,cnt = 1;
    base.dim = k+2;

    base.mat[1][1] = 1;
    for(i = 2; i <= k+2; i++) base.mat[1][i] = ncr[k][i-2];
    for(i = 2; i <= k+2; i++,cnt++)
    {
        for(j = 1; j <= cnt; j++) base.mat[i][j] = 0;
        for(;j<=k+2;j++) base.mat[i][j] = ncr[k-i+2][j-cnt-1];
    }

    ui ret = 0;
    base = expo(base,n-1);
    for(i = 1; i <= k+2; i++)
        ret += base.mat[1][i];

    return ret;
}

int main()
{
    //freopen("c:\\Users\\User\\Desktop\\in.txt", "r", stdin);
    int i, j, k, t, cs;
    LL n;


    ncr[0][0] = 1;
    for(i = 1; i <= 50; i++)
        for(j = 0; j <= i; j++)
        {
            if(!j || i == j) ncr[i][j] = 1;
            else ncr[i][j] = ncr[i-1][j] + ncr[i-1][j-1];
        }

    scanf("%d", &t);
    for(cs = 1; cs <= t; cs++)
    {
        scanf("%lld %d",&n, &k);
        printf("Case %d: %u\n", cs, f(n,k));
    }
    return 0;
}
