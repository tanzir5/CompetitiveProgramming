
//Mobius Function
void calc_mu(int n)
{
    int i, j;

    for(i = 1; i <= n; i++)
        mu[i] = mp(i,0);

    for(i = 2; i <= n; i++)
        if(!mu[i].ss)
            for(j = i; j <= n; j += i)
                mu[j].ff /= i, mu[j].ss++;

    for(i = 2; i <= n; i++)
        if(mu[i].ff != 1) mu[i].ff = 0;
        else if(mu[i].ss & 1) mu[i].ff = -1;
}
