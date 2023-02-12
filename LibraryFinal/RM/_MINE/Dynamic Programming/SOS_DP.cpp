
/* SOS DP
    Size of the dp table has to be quite large
    Don't forget to memset the dp array with 0 from main() function
*/

void sos_dp(int *arr, LL dp[], int n){

    int k = 1, i, pos, mask;

    while((1 << k) <= n) k++;
    for(i = 0; i <= n; i++)
        dp[i] = arr[i];

    for(pos = 0; pos < k; pos++)
        for(mask = 0; mask < (1 << k); mask++)
            if(mask & (1 << pos))
                dp[mask] += dp[mask ^ (1 << pos)];
}
