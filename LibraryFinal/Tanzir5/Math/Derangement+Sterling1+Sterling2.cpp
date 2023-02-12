//derangement
int derangement(int n)
{
    if(!n) return n;
    if(n <= 2) return n-1;
    return (n-1)*(derangement(n-1) + derangement(n-2));
}

/// Finds the number ways to put n balls into k indistinguishable boxes such that no box is empty`.
int stirling2(int n, int k)
{
    if(n < k)
        return 0;
    if(k == 1)
        return 1;
    if(dp[n][k] == dp[n][k])
        return dp[n][k];
    return dp[n][k] = stirling2(n-1,k-1) + stirling2(n-1,k)*k;

}

/// Finds the number of ways to put n elements into k cycles where no cycle is empty
int stirling1(int n, int k)
{
    dp[n][k] = stirling1(n-1,k-1) + stirling(n-1,k)*n-1;
}
