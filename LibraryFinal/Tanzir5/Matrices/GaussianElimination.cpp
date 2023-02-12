#define MAX         ?
/// 0 based indexing
/// n rows, m columns
/// n equations, m variables
/// MAX is the maximum number of equations or variables
/// X holds the solution
/// returns 1 if unique solution, -1 if inconsistent, inf if infinite solutions
struct matrix{
    double arr[MAX+10][MAX+10];
    int n, m;
}A;

int where[MAX+10];
double X[MAX+10];
const int inf = INT_MAX;
int gauss(int totalRow, int totalCol)
{
    A.n = totalRow, A.m = totalCol;
    mem(where, -1);
    int row, col;
    for(row = col = 0; row<A.n && col<A.m; col++)
    {
        int pivot = row;
        for(int i = row+1; i<A.n; i++)
        {
            if(fabs(A.arr[pivot][col]) < fabs(A.arr[i][col]))
                 pivot = i;
        }

        if(fabs(A.arr[pivot][col]) < eps)
            continue;
        if(pivot != row)
        {
            for(int i = 0; i<=A.m; i++)
                swap(A.arr[row][i], A.arr[pivot][i]);
        }
        where[col] = row;
        for(int i = row+1; i<A.n; i++)
        {
            if(fabs(A.arr[i][col]) > eps)
            {
                double c = -A.arr[i][col]/A.arr[row][col];
                for(int j = col+1; j<=A.m; j++)
                    A.arr[i][j] += c*A.arr[row][j];
            }
            A.arr[i][col] = 0;
        }
        row++;
    }


    for(int i = 0; i<A.n; i++)
    {
        bool nothing = true;
        for(int j = 0; j<A.m;j++)
        {
            if(fabs(A.arr[i][j]) > eps)
                nothing = false;
        }
        if(nothing && fabs(A.arr[i][A.m]) > eps)
            return -1;
    }

    for(int i = A.m-1; i>=0; i--)
    {
        if(where[i] == -1)  return inf;
        int row = where[i];
        double sltn = A.arr[row][A.m];
        for(int j = i+1; j<A.m; j++)
            sltn -= A.arr[row][j]*X[j];
        X[i] = sltn/A.arr[row][i];
    }

    return 1;
}
