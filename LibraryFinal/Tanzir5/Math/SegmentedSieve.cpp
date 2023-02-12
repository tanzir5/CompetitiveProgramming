/*
    Segmented Sieve
    This code was for 1 <= a <= b <= 2^31-1
    Change variable types appropriately.
*/
bool notPrime[ ? ];
void segmented_sieve(int a, int b)
{
    int p, f;
    mem(notPrime, 0);
    for(int i = 0; i<tot_prime; i++)
    {
        p = prime[i];
        if(a%p == 0) f = a;
        else f = (a - (a%p)+ p);

        f = max( p*p, f);
        for(unsigned j = f; j<=b; j+=p)
            notPrime[j-a] = true;
    }
    if(a == 1)
        notPrime[0] = 1;
}
