
#include<bits/stdc++.h>
using namespace std;
#define D(x)    cout << #x " = " <<(x) << endl
#define MAX     100000
typedef long long int LL;

#define xx		first
#define yy		second
typedef long long int LL;
typedef pair<LL, LL> pii;

#define CW 		-1
#define ACW	 	 1

int direction(pii st, pii ed, pii q){
	LL xp = (LL) (ed.xx - st.xx) * (q.yy - ed.yy) - (LL) (ed.yy - st.yy) * (q.xx - ed.xx);
	if(!xp) return 0;
	if(xp > 0) return ACW;
	return CW;
}


///hull points must be sorted anti - clockwise
pii better(pii u, pii v, pii Q, int dir){
    if(direction(Q, u, v) == dir) return u;
    return v;
}

bool isGood(pii u, pii v, pii Q, int dir){
    return (direction(Q, u, v) != -dir);
}

pii tangents(vector<pii> &hull, pii Q, int dir, int lo, int hi){
    int mid;

    while(hi - lo + 1 > 2){
        mid = (lo + hi)/2;
        bool pvs = isGood(hull[mid], hull[mid - 1], Q, dir);
        bool nxt = isGood(hull[mid], hull[mid + 1], Q, dir);

        if(pvs && nxt) return hull[mid];
        if(!(pvs || nxt)){
            pii p1 = tangents(hull, Q, dir, mid+1, hi);
            pii p2 = tangents(hull, Q, dir, lo, mid - 1);
            return better(p1, p2, Q, dir);
        }

        if(!pvs){
            if(direction(Q, hull[mid], hull[lo]) == dir)  hi = mid - 1;
            else if(better(hull[lo], hull[hi], Q, dir) == hull[lo]) hi = mid - 1;
            else lo = mid + 1;
        }
        if(!nxt){
            if(direction(Q, hull[mid], hull[lo]) == dir)  lo = mid + 1;
            else if(better(hull[lo], hull[hi], Q, dir) == hull[lo]) hi = mid - 1;
            else lo = mid + 1;
        }
    }

    pii ret = hull[lo];
    for(int i = lo + 1; i <= hi; i++) ret = better(ret, hull[i], Q, dir);
    return ret;
}

/// [ACW, CW] Tangent [ACW Tangent keeps all the points in ACW side]
pair< pii, pii> get_tangents(vector<pii> &polygon, pii Q){
    pii acw_tan = tangents(polygon, Q, ACW, 0, (int) polygon.size() - 1);
    pii cw_tan = tangents(polygon, Q, CW, 0, (int) polygon.size() - 1);
    return make_pair(acw_tan, cw_tan);
}


int main()
{
    //freopen("in.txt", "r", stdin);

    return 0;
}

