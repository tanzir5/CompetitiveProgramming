
void update(int idx, int val)
{
    while(idx <= mxval)
        BIT[idx] += val, idx += idx&-idx;
}

LL query(int idx)
{
    LL ret = 0;
    while(idx)
        ret += BIT[idx], idx -= idx&-idx;
    return ret;
}
