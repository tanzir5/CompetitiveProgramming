
// Suffix_Array O( n * lgn * lgn)
// 0 based indexing

int Plc[MAXLG+5][MAXN+10], stp;
int S[MAXN+10]; //Sorted Suffixes
pair< pii , int> L[MAXN+10];

void Generate_SA(string str)
{
    int i, j, k, len = str.size(), cur;
    for(i = 0; i < len; i++)    Plc[0][i] = str[i];

    for(cur = stp = 1; (cur>>1) < len; cur *= 2, stp++)
    {
        for(i = 0; i < len; i++)
        {
            L[i].xx.xx = Plc[stp-1][i];
            L[i].xx.yy = i+cur < len? Plc[stp-1][i+cur]:-inf; // set it to -inf when dealing with negative numbers
            L[i].yy = i;
        }
        sort(L, L+len);
        for(i = 0; i < len; i++)
        {
            if( !i || L[i-1].xx.xx != L[i].xx.xx || L[i-1].xx.yy != L[i].xx.yy ) Plc[stp][L[i].yy] = i;
            else Plc[stp][L[i].yy] = Plc[stp][L[i-1].yy];
        }
    }
    for(i = 0; i < len; i++)
        S[Plc[stp-1][i]] = i;
    stp--;
}

int lcp(int u, int v, int N) // Here N = length of the string **Call Generate_SA(string)**
{
    int ret = 0, k;
    if(u == v) return N-u;
    for(k = stp; k >= 0 && u < N && v < N; k--)
        if(Plc[k][u] == Plc[k][v])
            ret += 1<<k, u += 1<<k, v += 1<<k;
    return ret;
}
