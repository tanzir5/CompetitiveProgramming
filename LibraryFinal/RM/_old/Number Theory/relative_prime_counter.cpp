
//Number of Relative primes
LL phi[MAX+10]; // must be LL
void calc_phi(int n)
{
    int i, j;
    phi[1] = 1; // may be 0, if needed
    for(i = 2; i <= n; i++) phi[i] = i;
    for(i = 2; i <= n; i++)
        if(phi[i] == i)
            for(j = i; j <= n; j += i) phi[j] *= (i-1), phi[j]/=i;
}
