/*
  CRT:
      X = a_1 % m_1
      X = a_2 % m_2
      X = a_3 % m_3
      m_1,m_2,m_3 are pair wise co-prime
      M = m_1*m_2*m_3
      u_i = Modular inverse of (M/m_i) with respect m_i
      X = ( a_1 * (M/m_1) * u_1 + a_2 * (M/m_2) * u_2 + a_3 * (M/m_3) * u_3 ) % M

  Lucas:
    If we need to find nCr % P where P is a prime but P can be
    less than n or r, we can use Lucas Theorem.
    nCr = ((n_0 C r_0) * (n_1 C r_1) * (n_2 C r_2) * ... * (n_k C r_k)) % P
    Where n_i is the i'th digit in P based representation of n
    and r_i is the i'th digit in P based representation of r
*/
vector<int>prime;
/// generate primes of MOD in prime.
void genPrime(LL MOD);
LL exp(LL a, LL n, LL MOD);
LL fact[MAX+10];
LL lucas(int n, int r, int p)
{
    fact[0] = 1;
    for(int i = 1; i<p; i++)
        fact[i] = (fact[i-1]*i)%p;
    vector<int>digN, digR;
    while(n)
    {
        digN.push_back(n%p);
        n/=p;
    }
    while(r)
    {
        digR.push_back(r%p);
        r/=p;
    }
    LL ret = 1;
    for(int i = 0; i<digR.size(); i++)
    {
        LL tmp;
        if(digN[i] < digR[i])
            tmp = 0;
        else
        {
            tmp = (fact[digN[i]-digR[i]] * fact[digR[i]])%p;
            tmp = (fact[digN[i]]*exp(tmp,p-2,p))%p;
        }
        ret = (ret * tmp)%p;
    }
    return ret;
}

LL CRT(vector<LL>&a, vector<LL>&prime, LL M)
{
    vector<LL>u;
    for(int i = 0; i<prime.size(); i++)
        u.push_back(exp(M/prime[i], prime[i]-2, prime[i]));
    LL ret = 0;
    for(int i =0; i<prime.size(); i++)
    {
        LL tmp = (a[i] * (M/prime[i]))%M;
        tmp = (tmp * u[i])%M;
        ret = (ret + tmp);
        if(ret >= M)
            ret -= M;
    }
    return ret;
}


LL nCr(LL n, LL r, LL MOD)
{
    if(r > n)
        return 0;
    prime.clear();
    genPrime(MOD);
    vector<int>a;
    for(int i = 0; i<prime.size(); i++)
        a.push_back(lucas(n,r,prime[i]));
    return CRT(a, prime, MOD);
}
