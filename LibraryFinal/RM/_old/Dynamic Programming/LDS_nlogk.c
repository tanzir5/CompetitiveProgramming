
// lds - O(nlogk)
int fast_lds(int *arr, int N) //Calculates lds_len of arr[1]...arr[N] and returns lds
{
    int ret = 1;
    vector<int> sq;
    int i, lo, hi, mid;

    sq.pb(arr[1]);
    lds_len[1] = 1;

    for(i = 2; i <= N; i++)
    {
        lo = 0;
        hi = sq.size()-1;

        if(num[i] >= sq[lo]) sq[lo] = num[i], lds_len[i] = 1;
        else if(num[i] <  sq[hi]) sq.pb(num[i]), lds_len[i] = hi+2;
        else
        {
            while(lo < hi)
            {
                mid = lo+ ((hi-lo+1) >> 1);
                if(sq[mid] > arr[i]) lo = mid;
                else hi = mid-1;
            }
            sq[lo+1] = arr[i];
            lds_len[i] = lo+2;
        }

        ret = max(ret, lds_len[i]);
    }
    return ret;
}
