
//decompose
vector<pll> decompose(LL N)
{
    LL i, s = sqrt(N);
    LL cnt;

    vector <pll> prmf;
    for(i = 2; i <= s; i++)
    {
        if(N%i) continue;
        cnt = 0;
        while(!(N%i)) cnt++, N/=i;
        prmf.pb(mp(i,cnt));
        s = sqrt(N);
    }
    if(N != 1) prmf.pb(mp(N,1));

    return prmf;
}
