/// 1 based indexing
/// sltn contains the list of edges if graph construction is possible.
/// For checking if a connected graph is built:
/// If graph can be built and sum of degrees of all vertices is more than or equal to 2*n-2 and
/// each vertex degree is > 0, then a connected graph can be built with that degree sequence.
struct nodeData{
    int degree, id;
}A[MAX+10];

bool operator < (nodeData a, nodeData b)
{
    return a.degree < b.degree;
}

priority_queue<nodeData> PQ;

bool havelHakimi(int n, vector< pii >&sltn)
{
    while(!PQ.empty())
        PQ.pop();
    int mx = 0, mn = n+1;
    int oddCount = 0;
    for(int i = 1; i<=n; i++)
    {
        mx = max(mx, A[i].degree);
        mn = min(mn, A[i].degree);
        oddCount += (A[i].degree&1);
        if(A[i].degree > 0)
            PQ.push(A[i]);
    }
    if((oddCount&1) || (mx >= n) || (mn < 0))
        return false;
    while(!PQ.empty())
    {
        vector<nodeData>tmp;
        nodeData u = PQ.top();
        PQ.pop();
        while(u.degree > 0)
        {
            if(PQ.empty())
                return false;
            nodeData v = PQ.top();
            PQ.pop();
            sltn.pb({u.id,v.id});
            u.degree--;
            v.degree--;
            if(v.degree)
                tmp.pb(v);
        }
        for(int i = 0; i<tmp.size(); i++)
            PQ.push(tmp[i]);
    }
    return true;
}


