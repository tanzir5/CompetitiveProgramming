int P[MAX+10];
/// P[i] is the length of the longest proper prefix which is also a proper suffix of the string S[0..i]
int prefixFunction(char *S)
{
    int now;
    P[0] = now = 0;
    int len = strlen(S);
    for(int i = 1; i<len; i++)
    {
        while(now != 0 && S[now] != S[i])
            now = P[now-1];
        if(S[now] == S[i])
            P[i] = ++now;
        else
            P[i] = now = 0;
    }
}

/// checks if pattern is a substring of S
bool KMPMatcher(char *S, char *pattern)
{
    int now = 0;
    int lenStr = strlen(S);
    int lenPat = strlen(pattern);
    prefixFunction(pattern);
    for(int i = 0; i<lenStr; i++)
    {
        while(now != 0 && pattern[now] != S[i])
            now = P[now-1];
        if(pattern[now] == S[i])
            now++;
        else
            now = 0;
        if(now == lenPat)
            return 1;
    }
    return 0;
}
