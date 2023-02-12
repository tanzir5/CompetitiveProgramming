char text[MAX+10];
struct data{
    int tupleRank[2];
    int idx;
}A[MAX+10];
int sparseTable[MAXLG+2][MAX+10];
bool operator < (data a, data b)
{
    return (a.tupleRank[0] == b.tupleRank[0]) ? (a.tupleRank[1] < b.tupleRank[1]) : (a.tupleRank[0] < b.tupleRank[0]);
}
int step, SA[MAX+10], n;
void buildSA()
{
    n = strlen(text);
    if(n == 1)
    {
        sparseTable[0][0] = 0;
        SA[0] = 0;
        return;
    }
    for(int i = 0; i<n; i++)
        sparseTable[0][i] = text[i];
    step = 1;
    for(int jump = 1; jump < n; jump <<= 1, step++)
    {
        for(int i = 0; i<n; i++)
        {
            A[i].idx = i;
            A[i].tupleRank[0] = sparseTable[step-1][i];
            A[i].tupleRank[1] = (jump+i < n) ? (sparseTable[step-1][jump+i]) : -1;
        }
        sort(A,A+n);
        sparseTable[step][A[0].idx] = 0;
        for(int i = 1; i<n; i++)
        {
            if(A[i-1].tupleRank[0] == A[i].tupleRank[0] && A[i-1].tupleRank[1] == A[i].tupleRank[1])
                sparseTable[step][A[i].idx] = sparseTable[step][A[i-1].idx];
            else
                sparseTable[step][A[i].idx] = i;
        }
    }
    for(int i = 0; i<n; i++)
        SA[sparseTable[step-1][i]] = i;
}

int getLCP(int a, int b)
{
    int ret = 0;
    for(int i = step-1; i>=0; i--)
    {
        if(sparseTable[i][a] == sparseTable[i][b])
        {
            ret += (1<<i);
            a += (1<<i);
            b += (1<<i);
            if(a>=n || b>=n)
                break;
        }
    }
    return ret;
}
