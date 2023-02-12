
// Returns the position of a grey code
// i-th grey code = i ^ (i / 2)

char bs[MAX+11]; //Keep the number here in binary representation
LL go(LL st, LL ed, int pos, bool isLeft = true)
{
    if(pos < 0) return 0;

    LL mid = (st+ed)/2;

    if(isLeft)
    {
        if(bs[pos] == '0') return go(st, mid, pos-1, true);
        else return (mid - st + 1) + go(mid+1, ed, pos-1, false);
    }
    else
    {
        if(bs[pos] == '1') return go(st, mid, pos-1, true);
        else return (mid - st + 1) + go(mid+1, ed, pos-1, false);
    }
}
LL getPos()
{
    int n = strlen(bs);

    reverse(bs, bs + n);
    LL ret = go(0, (1LL << n)-1, n-1);
    reverse(bs, bs+ n);
    return ret;
}
