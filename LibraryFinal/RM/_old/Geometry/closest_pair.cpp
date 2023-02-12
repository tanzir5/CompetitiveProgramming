// Closest Pair

bool cmp(const point &u, const point &v){
        if(eq(u.y , v.y)) return u.x < v.x;
        return u.y > v.y;
}

// Don't forget to sort all the points before calling closest_pair
// Don't forget to call unique() over the points
// Indexing does not matter here
long double closest_pair(point *P, int st, int ed)
{
    if(st == ed) return numeric_limits<double>::max();
    if(st + 1 == ed) return abs(P[st] -  P[ed]);

    int mid = (st+ed)/2, i, j, k, turn;
    long double soFar = min(closest_pair(P, st, mid), closest_pair(P, mid+1, ed));


    vector<point> Lt, Rt;
    for(i = st; i <= mid; i++)
        if(abs(P[mid].x - P[i].x) < soFar + eps)
            Lt.push_back(P[i]);

    for(i = mid+1; i <= ed; i++)
        if(abs(P[i].x - P[mid].x) < soFar + eps)
            Rt.push_back(P[i]);


    stable_sort(Lt.begin(), Lt.end(), cmp);
    stable_sort(Rt.begin(), Rt.end(), cmp);

    for(i = j = 0; i < Lt.size(); i++)
    {
        while(j < Rt.size() && Rt[j].y > Lt[i].y + soFar + eps) j++;
            for(k = j; k < min((int) Rt.size(), j + 6); k++) // You may increase the bound.
                soFar = min(soFar, (long double) abs(Lt[i] - Rt[k]));
    }

    return soFar;
}
