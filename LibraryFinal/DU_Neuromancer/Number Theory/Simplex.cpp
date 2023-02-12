

/*
    -> Simplex Algorithm
    -> Ax <= b              [ b is inserted at the end of every row of 'Eq' matrix ]
    -> maximize cx          [ c is inserted at the last row of 'Eq' matrix ]
    -> 0 based indexing
*/

#define maxm 10000              // Number of equations
#define maxn 100                // Number of variables
double INF = 1e100;
double eps = 1e-10;
double Eq[maxm+5][maxn+5];      // Holds the coefficient of the equations
double _R[maxn+5];              // Does nothing, space crated to store the optimal values of the variables.

int counter = 0;
void pivot(int m, int n, double a[maxm+5][maxn+5], int B[maxm+5], int N[maxn+5], int r, int c)
{
    int i, j;
    swap(N[c], B[r]);
    a[r][c]=1/a[r][c];
    for (j=0; j<=n; j++)if (j!=c) a[r][j]*=a[r][c];
    for (i=0; i<=m; i++)if (i!=r)
        {
            for (j=0; j<=n; j++)if (j!=c)
                    a[i][j]-=a[i][c]*a[r][j];
            a[i][c] = -a[i][c]*a[r][c];
        }
    counter++;
}

int feasible(int m, int n, double a[maxm+5][maxn+5], int B[maxm+5], int N[maxn+5])
{
    int r, c, i;
    double p, v;
    while (1)
    {
        for (p=INF, i=0; i<m; i++) if (a[i][n]<p) p=a[r=i][n];
        if (p>-eps) return 1;
        for (p=0, i=0; i<n; i++) if (a[r][i]<p) p=a[r][c=i];
        if (p>-eps) return 0;
        p = a[r][n]/a[r][c];
        for (i=r+1; i<m; i++) if (a[i][c]>eps)
            {
                v = a[i][n]/a[i][c];
                if (v<p) r=i, p=v;
            }
        pivot(m, n, a, B, N, r, c);
    }
}

// m    -> number of equations
// n    -> number of variables
// a    -> Co-efficient of the equations
// b    -> Optimal value of the variables are stored here
// ret  -> Maximum value of the objective function is stored at this variable
// returns 0 if no solution, -1 if the region is unbounded, 1 if there exists a finite solution.
int simplex(int m, int n, double a[maxm+5][maxn+5], double b[maxn+5], double& ret)
{
    ret = 0;
    int B[maxm+5], N[maxn+5], r, c, i;
    double p, v;
    for (i=0; i<n; i++) N[i]=i;
    for (i=0; i<m; i++) B[i]=n+i;
    if (!feasible(m, n, a, B, N)) return 0;
    while (1)
    {
        for (p=0, i=0; i<n; i++) if (a[m][i]>p)
                p=a[m][c=i];
        if (p<eps)
        {
            for (i=0; i<n; i++) if (N[i]<n)
                    b[N[i]]=0;
            for (i=0; i<m; i++) if (B[i]<n)
                    b[B[i]]=a[i][n];
            ret = -a[m][n];
            return 1;
        }
        for (p=INF, i=0; i<m; i++) if (a[i][c]>eps)
            {
                v = a[i][n]/a[i][c];
                if (v<p) p=v, r=i;
            }
        if (fabs(p-INF) < eps) return -1;
        pivot(m, n, a, B, N, r, c);
    }
}
