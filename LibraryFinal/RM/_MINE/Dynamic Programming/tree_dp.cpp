
inline int maxLoad(int idx){
    if(idx == -1) return 0;
    if(ml[idx] != -1) return ml[idx];
    return ml[idx] = sz[idx] + maxLoad(sibling[idx]);
}

int calc(int idx, int k, bool dflag)
{
    if(k == 0) return 0;
    if(idx == -1) return inf;
    if(k > maxLoad(idx)) return inf;
    if(dp[dflag][k][idx] != -1) return dp[dflag][k][idx];

    int with = inf, without = inf, current;
    int x = min(maxLoad(fc[idx]), k), y = min(maxLoad(fc[idx]), k - 1);
    for(int i = max(0, k - maxLoad(sibling[idx])); i <= x; i++) without = min(without, calc(fc[idx], i, false) + calc(sibling[idx], k - i, dflag));
    for(int i = max(0, k - 1 - maxLoad(sibling[idx])); i <= y; i++) with = min(with, calc(fc[idx], i, dflag) + calc(sibling[idx], k - 1 - i, dflag));

    with += c[idx];
    if(dflag) with -= d[idx];
    return dp[dflag][k][idx] = min(inf , min(with, without));
}
