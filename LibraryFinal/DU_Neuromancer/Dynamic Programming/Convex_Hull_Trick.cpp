
struct Line{
        LL m,c;
        Line(LL _m = 0, LL _c = 0):m(_m), c(_c){};
};

struct ConvexHullTrick{ //works with long long integers.

    vector<Line> Q; //Fast -> Slow -> Slower -> Slowest
    bool minFlag;

    ConvexHullTrick(bool flg = false):minFlag(flg){};

    LL getX(Line u, Line v){ // Fast vrs Slow *ORDER MATTERS*
        LL difC = v.c - u.c, difM = u.m - v.m, ret = difC/difM;
        return (difC % difM) ? ret+1:ret;
    }

    bool isBad(Line L1, Line L2, Line L3)
    {
        if(minFlag == false) return (L3.c - L1.c) / (long double) (L1.m - L3.m) > (L2.c-L1.c) / (long double) (L1.m - L2.m);
        else return (L3.c - L1.c) / (long double) (L1.m - L3.m) < (L2.c-L1.c) / (long double) (L1.m - L2.m);
    }

    void addLine(Line L){ //Has to be slower than then the slowest in the Q
        while(Q.empty() == false)
        {
            if(Q.back().m < L.m) __builtin_trap();
            else if(minFlag == false && Q.back().m == L.m && L.c > Q.back().c) Q.pop_back();
            else if(minFlag == true && Q.back().m == L.m && L.c < Q.back().c) Q.pop_back();
            else if(Q.back().m == L.m) return;
            else if(Q.size() <= 1) break;
            else if(isBad(Q[Q.size()-2], Q.back(), L)) Q.pop_back();
            else break;
        }
        Q.push_back(L);
    }

    LL query(LL pos){
        int lo = 0, hi = (int) Q.size() - 1, n = hi, mid;
        LL L, R;

        while(true)
        {
            mid = (lo+hi)/2;
            if(minFlag)
            {
                if(mid == 0) L = -5e18;
                else L = getX(Q[mid-1], Q[mid]);

                if(mid == n) R = 5e18;
                else R = getX(Q[mid], Q[mid+1]);

                if(L <= pos && pos < R) return Q[mid].m * pos + Q[mid].c;
                if(pos < L) hi = mid-1;
                else lo = mid+1;
            }

            else
            {
                if(mid == n) L = -5e18;
                else L = getX(Q[mid], Q[mid+1]);

                if(mid == 0) R = 5e18;
                else R = getX(Q[mid-1], Q[mid]);

                if(L <= pos && pos < R) return Q[mid].m * pos + Q[mid].c;
                if(pos < L) lo = mid+1;
                else hi = mid-1;
            }
        }
    }
};
