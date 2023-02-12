
//Shank's Baby Step Gaint Step
int shanks(int a, int b, int p) // a^x = b (mod m), x = ?
{
    int i, rp;
    LL baby, ai = 1, j;
    rp = (int) ceil(sqrt(p));

    map<LL, int>::iterator it;
    map<LL, int> M;
    M.insert(mp(1,0));

    for(i = 1; i < rp; i++)
    {
        ai = ((LL)ai*a)%p;
        M.insert(mp(ai,i));
    }

    baby = ip(ip(a,p-2,p), rp, p); // a ^ (-m)
    for(j = b, i = 0; i < rp; i++)
    {
        it = M.find(j);
        if(it != M.end()) return i*rp + it->second;
        j = (j*baby)%p;
    }
    return 0;
}
