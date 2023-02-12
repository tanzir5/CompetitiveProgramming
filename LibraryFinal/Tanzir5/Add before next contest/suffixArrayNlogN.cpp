/*
Suffix array implementation using bucket sorting + lcp.
Complexity O(n log n), text[] is the target string,
n is its length and SA[i] contains i'th sorted suffix position.
getLcp(i,j) gives the lcp length of suffix starting from i-th and j-th position.
*/

const int MAXN = 50010;
const int MAXL = 18;

int n, step, mv, SA[MAXN], tmp[MAXN];
int sum[MAXN], cnt[MAXN], Rank[MAXL][MAXN];
char text[MAXN];

inline bool eq(const int &u, const int &v)
{
    if(!step) return text[u] == text[v];
    if(Rank[step-1][u] != Rank[step-1][v]) return false;
    int a = u + mv < n ? Rank[step-1][u+mv] : -1;
    int b = v + mv < n ? Rank[step-1][v+mv] : -1;
    return a == b;
}

void update()
{
    int i, rnk;
    for(i = 0; i < n; i++) sum[i] = 0;
    for(i = rnk = 0; i < n; i++)
    {
        SA[i] = tmp[i];
        if(i && !eq(SA[i], SA[i-1]))
        {
            Rank[step][SA[i]] = ++rnk;
            sum[rnk+1] = sum[rnk];
        }
        else Rank[step][SA[i]] = rnk;
        sum[rnk+1]++;
    }
}

void Sort()
{
    int i;
    for(i = 0; i < n; i++) cnt[i] = 0;
    memset(tmp, -1, sizeof tmp);
    for(i = 0; i < mv; i++)
    {
        int idx = Rank[step - 1][n - i - 1];
        int x = sum[idx];
        tmp[x + cnt[idx]] = n - i - 1;
        cnt[idx]++;
    }
    for(i = 0; i < n; i++)
    {
        int idx = SA[i] - mv;
        if(idx < 0)continue;
        idx = Rank[step-1][idx];
        int x = sum[idx];
        tmp[x + cnt[idx]] = SA[i] - mv;
        cnt[idx]++;
    }
    update();
    return;
}

inline bool cmp(const int &a, const int &b)
{
    if(text[a]!=text[b]) return text[a]<text[b];
    return false;
}

void buildSA()
{
    int i;
    n = strlen(text);
    for(i = 0; i < n; i++) tmp[i] = i;
    sort(tmp, tmp + n, cmp);
    step = 0;
    update();
    ++step;
    for(mv = 1; mv < n; mv <<= 1)
    {
        Sort();
        step++;
    }
    step--;
    for(i = 0; i <= step; i++) Rank[i][n] = -1;
}

inline int getLCP(int u, int v)
{
    if(u == v) return n - u;
    int ret, i;
    for(ret = 0, i = step; i >= 0; i--)
    {
        if(Rank[i][u] == Rank[i][v])
        {
            ret += 1<<i;
            u += 1<<i;
            v += 1<<i;
        }
    }
    return ret;
}
