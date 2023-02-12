char s[20];
int A[11][11], Row[11][11], Col[11][11], Box[11][11];
int boxNumber(int i, int j)
{
    return ((i-1)/3 * 3) + ceil(j/3.0);
}

int check(int i, int j)
{
    bool notCandidate[11] = {0};
    int b = boxNumber(i,j), k;
    for(k = 1; k<=9; k++)
        notCandidate[k] |= Row[i][k], notCandidate[k] |= Col[j][k], notCandidate[k] |= Box[b][k];
    int ret = 0;
    for(k = 1; k<=9; k++)
        ret += (notCandidate[k] == 0);
    return ret;
}

bool call()
{
    int i, j, k;
    pii nxt;
    int mn = inf;
    FRE(i,1,9)
    {
        FRE(j,1,9)
        {
            if(A[i][j] == 0)
            {
                int nw = check(i,j);
                if(nw < mn)
                {
                    mn = nw;
                    nxt = {i,j};
                }
            }
        }
    }
    if(mn == 0)
        return false;

    if(mn == inf)
        return true;

    bool notCandidate[11] = {0};
    i = nxt.xx, j = nxt.yy;
    int b = boxNumber(i,j);

    for(k = 1; k<=9; k++)
    {
        notCandidate[k] |= Row[i][k], notCandidate[k] |= Col[j][k], notCandidate[k] |= Box[b][k];
        if(!notCandidate[k])
        {
            Row[i][k] = Col[j][k] = Box[b][k] = 1;
            A[i][j] = k;
            if(call())
                return true;
            Row[i][k] = Col[j][k] = Box[b][k] = 0;
            A[i][j] = 0;
        }
    }
    return false;
}

int main()
{
    int i, j, k, cs, t;
    sf(t);
    FRE(cs,1,t)
    {
        mem(Row,0);
        mem(Col,0);
        mem(Box,0);
        FRE(i,1,9)
        {
            scanf("%s",s);
            for(j = 0; j<9; j++)
            {
                if(s[j] == '.')
                    A[i][j+1] = 0;
                else
                {
                    A[i][j+1] = s[j] - '0';
                    Row[i][s[j]-'0'] = 1;
                    Col[j+1][s[j]-'0'] = 1;
                    k = boxNumber(i,j+1);
                    Box[k][s[j]-'0'] = 1;
                }
            }
        }
        call();
        pf("Case %d:\n",cs);
        FRE(i,1,9)
        {
            FRE(j,1,9)
                 pf("%d",A[i][j]) ;
            puts("");
        }
    }
    return 0;
}

