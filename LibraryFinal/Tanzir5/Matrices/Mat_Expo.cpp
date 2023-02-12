/*
    M^(n-1) * A = B
*/
struct mat{
    int r, c;
    LL arr[?][?];
}M, A, id;

mat mul(mat a, mat b)
{
    mat ret;
    ret.r = a.r, ret.c = b.c;
    for(int i = 0; i<a.r; i++)
    {
        for(int j = 0; j<b.c; j++)
        {
            ret.arr[i][j] = 0;
            for(int k = 0; k<a.c; k++)
            {
                ret.arr[i][j] += (a.arr[i][k] * b.arr[k][j])%MOD;
                ret.arr[i][j] %= MOD;
            }
        }
    }
    return ret;
}

void init()
{
    id.r = id.c = ?;
    mem(id.arr,0);
    for(int i = 0; i<id.r; i++)
        id.arr[i][i] = 1;

//    do rest of initiating here.

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
