
/*
Given a_1, a_2, a_3, a_4..... a_n
Supports two operation:
1. Add L R X: adds X to a_L, a_(L+1), ....... a_R
2. Query L R: returns fib(a_L) + fib(a_(L+1)) + ..... + fib(a_R)
*/

#include<bits/stdc++.h>
using namespace std;
#define MOD     1000000007
#define MAX     100000
#define D(x)    cout << #x " = " << (x) << endl
typedef long long int LL;

inline LL mul(LL x, LL y){
    LL ret = x * y;
    if(ret >= MOD) ret %= MOD;
    return ret;
}

inline LL add(LL u, LL v){
    LL ret = u + v;
    if(abs(ret) >= MOD) ret %= MOD;
    if(ret < 0) ret += MOD;

    return ret;
}


struct matrix{
    int mat[2][2], dim;
    matrix(){}

    matrix operator * (const matrix &r){
        int i, j, k;
        matrix ret;

        for(i = 0; i < 2; i++)
            for(j = 0; j < 2; j++)
            {
                ret.mat[i][j] = 0;
                for(k = 0; k < 2; k++)
                    ret.mat[i][j] = add(ret.mat[i][j], mul(mat[i][k], r.mat[k][j]));
            }
        return ret;
    }

};

matrix unitMatrix(){
    matrix ret;
    ret.mat[0][0] = ret.mat[1][1] = 1;
    ret.mat[0][1] = ret.mat[1][0] = 0;
    return ret;
}

matrix expo(matrix &in, LL p)
{
    matrix ret = unitMatrix(), aux = in;
    while(p)
    {
        if(p&1) ret = ret*aux;
        aux = aux*aux;
        p>>=1;
    }
    return ret;
}

matrix fibMatrix(int p){
    matrix ret;
    ret.mat[0][0] = ret.mat[0][1] = ret.mat[1][0] = 1;
    ret.mat[1][1] = 0;

    return expo(ret, p);
}

bool notCleared(matrix m){
    if(m.mat[0][0] != 1) return true;
    if(m.mat[0][1] != 0) return true;
    if(m.mat[1][0] != 0) return true;
    if(m.mat[1][1] != 1) return true;
    return false;
}

int arr[MAX+5];

struct lazy{
    matrix M;

    lazy(){
        M = unitMatrix();
    }
    void compose(lazy ano){
        M = M * ano.M;
    }
};

struct node{
    int sW, sX;
    lazy L;

    node(){
        sW = sX = 0;
    }

    void apply(lazy _L){
        int t_sW = sW;
        int t_sX = sX;

        sW = mul( sW , _L.M.mat[0][0]);
        sW = add(sW , mul(sX, _L.M.mat[1][0]));

        sX = mul(t_sW, _L.M.mat[0][1]);
        sX = add(sX, mul( t_sX, _L.M.mat[1][1]));

        L.compose(_L);
    }

    void clearLazy(){
        L.M = unitMatrix();
    }
} tree[MAX << 2];


void propagate(int idx, int st, int ed)
{
    int mid = (st+ed)/2, l = 2*idx, r = l + 1;

    tree[l].apply(tree[idx].L);
    tree[r].apply(tree[idx].L);

    tree[idx].clearLazy();
}

void build_tree(int idx, int st, int ed)
{
    if(st == ed){
        tree[idx].L.M = fibMatrix(arr[st]);
        tree[idx].sW = tree[idx].L.M.mat[1][0];
        tree[idx].sX = tree[idx].L.M.mat[1][1];

        return;
    }
    int mid = (st+ed)/2, l = 2*idx, r = l + 1;
    build_tree(l, st, mid);
    build_tree(r, mid+1, ed);

    tree[idx].sX = add(tree[l].sX, tree[r].sX);
    tree[idx].sW = add(tree[l].sW, tree[r].sW);
}

void update(int idx, int st, int ed, int i, int j, lazy &curr)
{
    if(st == i && ed == j)
    {
        tree[idx].apply(curr);
        return;
    }

    int mid = (st+ed)/2, l = 2*idx, r = l+1;
    if( notCleared(tree[idx].L.M) ) propagate(idx, st, ed);

    if(j <= mid) update(l , st, mid, i, j, curr);
    else if(i > mid) update(r, mid+1, ed, i, j, curr);
    else update(l, st, mid, i, mid, curr), update(r, mid+1, ed, mid+1, j, curr);

    tree[idx].sX = add(tree[l].sX, tree[r].sX);
    tree[idx].sW = add(tree[l].sW, tree[r].sW);
}

int query(int idx, int st, int ed, int i, int j)
{
    if(st == i && ed == j) return tree[idx].sW;
    int mid = (st+ed)/2, l = 2*idx, r = l + 1;
    if( notCleared(tree[idx].L.M) ) propagate(idx, st, ed);

    if(j <= mid) return query(l, st, mid, i, j);
    if(i > mid) return query(r, mid+1, ed, i, j);
    return (query(l,st,mid,i,mid) + query(r,mid+1,ed,mid+1,j))%MOD;
}

int main()
{
    //freopen("in.txt", "r", stdin);

    int i, j, k, n, q;
    int l, r, x, tp;
    lazy L;

    scanf("%d %d", &n, &q);
    for(i = 1; i <= n; i++)
        scanf("%d", arr + i);

    build_tree(1, 1, n);

    while(q--)
    {
        scanf("%d", &tp);
        if(tp == 1){
            scanf("%d %d %d", &l, &r, &x);
            L.M = fibMatrix(x);
            update(1, 1, n, l, r, L);

        }
        else{
            scanf("%d %d", &l, &r);
            printf("%d\n", query(1, 1, n, l, r));
        }
    }
    return 0;
}
