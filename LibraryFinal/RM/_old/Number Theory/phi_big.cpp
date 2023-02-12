
//phi
LL phi(LL N)
{
    vector<pll> nw;
    LL ret = N;
    nw = decompose(N);

    LL i;
    for(i = 0; i < nw.size(); i++)
    {
        ret /= nw[i].fi;
        ret *= (nw[i].fi - 1);
    }

    return ret;
}
