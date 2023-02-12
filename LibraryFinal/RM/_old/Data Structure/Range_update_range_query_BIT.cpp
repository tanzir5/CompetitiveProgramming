
// Range_update_Range_query_BIT
// An array, suppose arr[MAX]
// 1 based indexing
LL BIT_ADD[MAX+10];
LL BIT_SUB[MAX+10];
int mxval;

void init()
{
    mem(BIT_ADD, 0);
    mem(BIT_SUB, 0);
}

void update(LL BIT[], int idx, LL val) //single point update, arr[idx] = val
{
    while(idx <= mxval)
        BIT[idx] += val, idx += idx&-idx;
}

LL query(LL BIT[], int idx) // single point query, cumulative sum from arr[1] to arr[idx]
{
    LL ret = 0;
    while(idx)
        ret += BIT[idx], idx -= idx&-idx;
    return ret;
}


LL range_query(int L, int R) // cumulative sum from arr[L] to arr[R]
{
    LL ret = (R*query(BIT_ADD, R) - (L-1)*query(BIT_ADD, L-1)) - (query(BIT_SUB, R) - query(BIT_SUB, L-1)) ;
    return ret;
}

void range_update(int L, int R, LL v) // For i = L to R, arr[i] += val
{
    update(BIT_ADD, L,v);
    update(BIT_ADD, R+1, -v);
    update(BIT_SUB, L, v*(L-1));
    update(BIT_SUB, R+1, -v*(R));
}
