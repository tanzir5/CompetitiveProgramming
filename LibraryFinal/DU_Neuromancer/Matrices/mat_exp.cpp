
///Matrix Exponentiation :: FIX THE DIM FOR EVERY MATRIX
#define DIM 5
#define EXPM 1000000007
struct matrix{
    int mat[DIM+5][DIM+5], dim;
    matrix(){}
    matrix(int d, int x = 1){                   ///* USE WITH CAUTION *///
        int i,j;
        dim = d;
        for(i = 1; i <= dim; i++)
            for(j = 1; j <= dim; j++)
                mat[i][j] = (i == j) ? x : 0;
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
                    ret.mat[i][j] = (ret.mat[i][j] + ((LL)mat[i][k]*r.mat[k][j])%EXPM)%EXPM;
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
