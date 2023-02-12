/*
    Complexity: O(max(n*sqrt(n), q*sqrt(n), q*log(q)))
    Optimizations done:
    1. keep l_bucket
    2. use inline functions
    3. use even odd different sorting
*/
? A[?], ans,  sltn[?];
int freq[?], bucket_size = sqrt(?);

struct data{
    int st, ed, idx, l_bucket;
    bool even;
    data(int a, int b, int i)
    {
        st = a, ed = b, idx = i;
        l_bucket = st/bucket_size;
        if(l_bucket & 1)
            even = false;
        else
            even = true;
    }
    data(){}
};

vector< data > Q;

inline bool cmp(data a, data b)
{
    if(a.l_bucket == b.l_bucket)
    {
        if(a.even)
            return a.ed < b.ed;
        else
            return a.ed > b.ed;
    }
    return a.l_bucket < b.l_bucket;
}

inline void add(int idx)
{

}

inline void rmv(int idx)
{

}


void Mo()
{
    sort(all(Q), cmp);
    ans = 0;
    add(1);
    int l = 1, r = 1;
    for(int i = 0; i<Q.size(); i++)
    {
        while(l < Q[i].st)
            rmv(l), l++;
        while(l > Q[i].st)
            l--, add(l);
        while(r < Q[i].ed)
            r++, add(r);
        while(r > Q[i].ed)
            rmv(r), r--;
        sltn[Q[i].idx] = ans;
    }
}



