/*
    IDAStar to solve 15 puzzle
    Finds the minimum steps to reach solution. Finds the lexicographical minimum among the best.
    For 15 puzzle, there can be inputs that might need around 200 moves.
    ID_DFS() terminates after 35 steps.
    Manhattan distance from actual position is used as heuristics.
    Remember, heuristics should always give less than or equal to the actual answer.
    Heuristics can never overestimate the answer.

    For 8 puzzle, highest number of steps needed is 31 ( probably ) .
    Critical(31 steps) case for 8 puzzle:
    8 6 7
    2 5 4
    3 0 1
    Impossible checking for 8 puzzle:
    if(inv %2 ) return -1; ( impossible to solve if inversion count is odd )
*/
/// op[i] is the opposite move of move i.
int A[5][5], dest[5][5], R[20], C[20], op[5];

/// D L R U
int dy[] = {+0,-1,+1,+0};
int dx[] = {+1,+0,+0,-1};
int depth;
vector<int>sltn;
char Move[10];

bool ok(int nr, int nc)
{
    if(nr > 0 && nc > 0 && nr <= 4 && nc <= 4)
        return true;
    return false;
}

/// heuristics function
int heuristics(int nw, int r, int c)
{
    return abs(R[nw] - r) + abs(C[nw] - c);
}

int dfs(int r, int c, int d, int lst,  int h)
{
    int i, j, nr, nc;

    if(h == 0)
        return true;
    if(h + d > depth)
        return false;

    for(i = 0; i<4; i++)
    {
        /// Don't go to parent state
        if(lst >= 0 && op[lst] == i)
            continue;
        nr = r, nc = c;
        nr += dx[i];
        nc += dy[i];
        if( ok(nr,nc))
        {
            int nw = A[nr][nc];

            h -= heuristics(nw, nr, nc);
            swap(A[r][c],A[nr][nc]);
            h += heuristics(nw,r,c);
            sltn.pb(i);
            if(dfs(nr,nc,d+1,i,h))
                return true;

            sltn.pop_back();
            h += heuristics(nw,nr,nc);
            swap(A[r][c],A[nr][nc]);
            h -= heuristics(nw,r,c);
        }
    }
    return false;
}
int ID_DFS()
{
    int i, j, x, y, inv = 0, cnt = 0, h = 0;
    /// calculate heuristics for given input and count inversions
    for(i = 1; i<=4; i++)
    {
        for(j = 1; j<=4; j++)
        {
            if(A[i][j] == 0)
                x = i, y = j;
            if(A[i][j])
                h += heuristics(A[i][j], i, j);
            for(int k = i; k<=4; k++)
            {
                int l = 1;
                if(k == i) l = j+1;
                for(; l <= 4; l++)
                    if(A[i][j] && A[k][l] && A[i][j] > A[k][l])
                        inv++;
            }
        }
    }

    /// Impossible checking for 15 puzzle
    if( (inv %2 && (4-x+1)%2 == 1) || ( inv%2 == 0 && (4-x+1)%2 == 0))
        return -1;

    /// Increase depth by 1 of IDDFS
    for(depth = h; depth <= 35; depth++)
    {
        if(dfs(x,y,0,-10,h))
            return depth;
    }
    /// Solution not found within 35 moves
    return -1;
}

void pre()
{
    Move[0] = 'D';
    Move[1] = 'L';
    Move[2] = 'R';
    Move[3] = 'U';

    op[0] = 3;
    op[3] = 0;
    op[1] = 2;
    op[2] = 1;

    int cnt = 1;
    for(int i = 1; i<=4; i++)
    {
        for(int j = 1; j<=4; j++)
            dest[i][j] = cnt, R[cnt] = i, C[cnt] = j, cnt++;
    }
}

void solve()
{
    sltn.clear();
    int ans = ID_DFS();
    if(ans == -1)
        printf("This puzzle is not solvable.");
    else
    {
        for(int i = 0; i<sltn.size(); i++)
            printf("%c",Move[sltn[i]]);
    }
    puts("");
}

int main()
{
    int cs, t, i, j, k;

    pre();
    sf(t);
    FRE(cs,1,t)
    {
        for(i = 1; i<=4; i++)
        {
            for(j = 1; j<=4; j++)
                scanf("%d",&A[i][j]);
        }
        printf("Case %d: ",cs);
        solve();
    }
    return 0;
}
