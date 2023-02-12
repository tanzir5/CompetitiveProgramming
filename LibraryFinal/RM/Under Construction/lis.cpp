
// LIS - O(nlogk)
int fast_lis(int *arr, int N) //Calculates lis_len of arr[1]...arr[N] and returns lis
{
    if(!N) return 0;

    int ret = 1;
    vector<int> sq;
    int i, lo, hi, mid;

    sq.pb(arr[1]);
    lis_len[1] = 1;

    for(i = 2; i <= N; i++)
    {
        lo = 0;
        hi = sq.size()-1;

        if(arr[i] <= sq[lo]) sq[lo] = arr[i], lis_len[i] = 1;
        else if(arr[i] >  sq[hi]) sq.pb(arr[i]), lis_len[i] = hi+2;
        else
        {
            while(lo < hi)
            {
                mid = lo+ ((hi-lo+1) >> 1);
                if(sq[mid] < arr[i]) lo = mid;
                else hi = mid-1;
            }
            sq[lo+1] = arr[i];
            lis_len[i] = lo+2;
        }

        ret = max(ret, lis_len[i]);
    }
    return ret;
}
