/*
    SUST 17 Endor solution. Find the number of active groups who have the highest frequency. If distance between a pair of members is less equal to k,
    then the group is active.
    1. put queries in buckets and sort buckets by right pointer and solve each bucket separately
    2. Solve query by brute force if query end is before bucketend.
    3. For each query move right pointer forward
    4. For each query move left pointer from bucketend to start of query and merge data in temp array
    5. get temp array back to initial state to keep it persistent.
*/
struct queryData{
    int st, ed, id;
};

struct queryBucket{
    int bucketEd;
    vector<queryData>V;
}bucket[320];

bool operator < ( queryData a, queryData b)
{
    return a.ed < b.ed;
}

int A[MAX+10], bucketSize, bucketTotal;

int freq[MAX+10], tmpFreq[MAX+10], FF[MAX+10], tmpFF[MAX+10],
    active[MAX+10], tmpActive[MAX+10], latest[MAX+10], tmpLatest[MAX+10],
    firstFound[MAX+10];
int sltn[MAX*10+10], k;

int bruteFreq[MAX+10], bruteFF[MAX+10], bruteActive[MAX+10], bruteLatest[MAX+10];

void preProcess(int n)
{
    mem(tmpLatest,-1);
    mem(bruteLatest,-1);
    bucketSize = sqrt(n);
    bucketTotal = 0;
    for(int i = bucketSize-1; ;i+=bucketSize,bucketTotal++)
    {
        bucket[bucketTotal].bucketEd = min(i,n);
        if(i >= n)
        {
            bucketTotal++;
            break;
        }
    }
}

int brute(int st, int ed)
{
    int mxFreq = 0, ans = 0;
    vector<pii>changed;
    for(int i = st; i<=ed; i++)
    {
        int nw = A[i];
        if(bruteActive[nw])
        {
            changed.pb({bruteFreq[nw],-1});
            bruteFF[bruteFreq[nw]]--;
        }
        if(bruteLatest[nw] != -1 && abs(bruteLatest[nw]-i) <= k)
            bruteActive[nw] = true;

        bruteFreq[nw]++;
        if(bruteActive[nw])
        {
            changed.pb({bruteFreq[nw],+1});
            bruteFF[bruteFreq[nw]]++;
        }
        bruteLatest[nw] = i;

        if(mxFreq <= bruteFreq[nw] && bruteActive[nw])
        {
            mxFreq = bruteFreq[nw];
            ans = bruteFF[bruteFreq[nw]];
        }
    }

    for(int i = ed; i>=st; i--)
    {
        int nw = A[i];
        bruteLatest[nw] = -1;
        bruteFreq[nw]--;
        bruteActive[nw] = 0;
    }

    for(int i = 0; i<changed.size(); i++)
    {
        bruteFF[changed[i].xx] -= changed[i].yy;
    }
    return ans;
}

void solveBucket(int idx)
{
    int bucketEd = bucket[idx].bucketEd;
    int curRight = bucketEd+1;
    int ans = 0, mxFreq = 0;
    for(int i = 0; i<bucket[idx].V.size(); i++)
    {
        int st = bucket[idx].V[i].st;
        int ed = bucket[idx].V[i].ed;
        int id = bucket[idx].V[i].id;
        if(ed <= bucketEd)
        {
            sltn[id] = brute(st,ed);
            continue;
        }
        /// shift rightPointer to ed
        while(curRight <= ed)
        {
            int nw = A[curRight];

            if(active[nw])
                FF[freq[nw]]--, tmpFF[freq[nw]]--;

            if(latest[nw] != -1 && abs(latest[nw]-curRight) <= k)
                active[nw] = tmpActive[nw] = true;

            freq[nw]++;
            tmpFreq[nw]++;

            if(active[nw])
            {
                FF[freq[nw]]++;
                tmpFF[freq[nw]]++;
                if(mxFreq <= freq[nw])
                {
                    mxFreq = freq[nw];
                    ans = FF[freq[nw]];
                }
            }

            if(latest[nw] == -1)
                firstFound[nw] = curRight;
            latest[nw] = curRight;

            curRight++;
        }
        int tmpAns = ans;
        int tmpMxFreq = mxFreq;
        vector<pii>changed;
        /// shift leftPointer to st
        for(int j = bucketEd; j>= st; j--)
        {
            int nw = A[j];
            if(tmpActive[nw])
            {
                changed.pb({tmpFreq[nw],-1});
                tmpFF[tmpFreq[nw]]--;
            }

            if(tmpLatest[nw] != -1 && abs(tmpLatest[nw]-j) <= k)
                tmpActive[nw] = true;
            if(firstFound[nw] != -1 && abs(firstFound[nw] - j) <= k)
                tmpActive[nw] = true;

            tmpFreq[nw]++;
            if(tmpActive[nw])
            {
                changed.pb({tmpFreq[nw], +1});
                tmpFF[tmpFreq[nw]]++;
                if(tmpMxFreq <= tmpFreq[nw])
                {
                    tmpMxFreq = tmpFreq[nw];
                    tmpAns = tmpFF[tmpFreq[nw]];
                }
            }
            tmpLatest[nw] = j;
        }
        sltn[id] = tmpAns;

        /// keep persistency
        for(int j = st; j<=bucketEd; j++)
        {
            int nw = A[j];
            tmpLatest[nw] = -1;
            tmpFreq[nw]--;
            tmpActive[nw] = active[nw];
        }

        for(int j = 0; j<changed.size(); j++)
            tmpFF[changed[j].xx] -= changed[j].yy;
    }
}

void solve()
{
    for(int i = 0; i<bucketTotal; i++)
    {
        mem(latest,-1);
        mem(firstFound,-1);
        mem(active,0);
        mem(tmpActive,0);
        mem(freq,0);
        mem(tmpFreq,0);
        mem(FF,0);
        mem(tmpFF,0);

        sort(all(bucket[i].V));
        solveBucket(i);
   }
}

int main()
{
    int n, q, st, ed, t;
    scanf("%d",&t);
    for(int cs = 1; cs<=t; cs++)
    {
        scanf("%d %d",&n,&k);
        preProcess(n);
        for(int i = 1; i<=n; i++)
            scanf("%d",&A[i]);

        scanf("%d",&q);
        for(int i = 1; i<=q; i++)
        {
            scanf("%d %d",&st,&ed);
            bucket[st/bucketSize].V.push_back({st,ed,i});
        }
        solve();
        for(int i = 1; i<=q; i++)
            printf("%d\n",sltn[i]);
        for(int i = 0; i<=bucketTotal; i++)
            bucket[i].V.clear();
    }
}

