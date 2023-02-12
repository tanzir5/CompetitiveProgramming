#include <cstdio>
#include <cstring>
/*
there are n companies who require one employee each and there are n candidates. All the candidates interviewed in each of the companies
and eventually they have different preferences over the companies and the companies have different preferences over the candidates.

So, you are given the task to assign each candidate to each company such that the employment scheme is stable. A scheme is stable if there is no pair (candidatei, companyj) and (candidatex, companyy) where

a)      Candidatei prefers companyy more than companyj and
b)      Companyy prefers candidatei more than candidatex.
*/

/// Code: Zobayer Vai
/// Complexity: O(N^2)
const int MAX = 128;

int m, L[MAX][MAX], R[MAX][MAX], L2R[MAX], R2L[MAX], p[MAX];

void stableMarriage()
{
    int i, man, wom, hubby;
    memset(R2L, -1, sizeof R2L);
    memset(p, 0, sizeof p);
    for(i = 0; i < m; i++ )
    {
        man = i;
        while(man >= 0)
        {
            while(true)
            {
                wom = L[man][p[man]++];
                if(R2L[wom] < 0 || R[wom][man] > R[wom][R2L[wom]]) break;
            }
            hubby = R2L[wom];
            R2L[L2R[man] = wom] = man;
            man = hubby;
        }
    }
}

int main()
{
    int test, cs, i, j, pref;
    scanf("%d", &test);
    for(cs = 1; cs <= test; cs++)
    {
        scanf("%d", &m);
        for(i = 0; i < m; i++)
        {
            for(j = 0; j < m; j++)
            {
                scanf("%d", &L[i][j]);
                L[i][j] -= (m+1);
            }
        }
        for(j = 0; j < m; j++)
        {
            for(i = 0; i < m; i++)
            {
                scanf("%d", &pref);
                R[j][pref-1] = m-i;
            }
        }
        stableMarriage();
        printf("Case %d:", cs);
        for(i = 0; i < m; i++) printf(" (%d %d)", i+1, L2R[i]+m+1);
        printf("\n");
    }
    return 0;
}
