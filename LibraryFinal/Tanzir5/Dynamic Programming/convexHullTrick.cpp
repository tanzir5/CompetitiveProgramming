struct line {
    LL m, c;
    double intersect(const line p) const {
        LL a = p.c-c, b = m-p.m;
        return (long double)a / (long double)b;
//        LL g = __gcd(a, b);
//        return { a/g, b/g };
    }
    inline LL getY(LL x) {
        return m*x + c;
    }
};

namespace cht {
    line arr[MAX];
    int key;
    bool minFlag;

    void init(bool f) {
        key = 0;
        minFlag = f;
    }

    inline bool check(line a, line b, line c) {
        auto ac = a.intersect(c);
        auto ab = a.intersect(b);
        return (ac > ab);
//        return (1.0 * ac.uu * ab.vv > 1.0 * ac.vv * ab.uu);
    }

    inline void add(line l) {
        if(key == 0) arr[++key] = l;
        else if(arr[key].m == l.m) {
            if(minFlag) {
                if(arr[key].c < l.c) return;
                else arr[key] = l;
            }
            else {
                if(arr[key].c > l.c) return;
                else arr[key] = l;
            }
        }


        else {
            while(key >= 2) {
                if(!check(arr[key-1], arr[key], l)) key--;
                else break;
            }
            arr[++key] = l;
        }
    }



    inline bool onSegment(int idx, LL x) {
        if(idx != 1)  {
            auto p = arr[idx].intersect(arr[idx-1]);
            if(p > x) return false;
//            if(1.0 * p.uu > 1.0 * p.vv*x) return false;
        }
        if(idx != key) {
            auto p = arr[idx].intersect(arr[idx+1]);
            if(p < x) return false;
//            if(1.0 * p.uu < 1.0 * p.vv*x) return false;
        }
        return true;
    }
}

LL solve() {
    LL ret = LLONG_MAX;
    cht::init(true);
    cht::add({ height[n-1], 0 });
    int last = cht::key;
    for(int idx=n-2; idx>=0; idx--) {
        // querying
        last = min(last, cht::key);
        while(last <= cht::key && !cht::onSegment(last, cost[idx])) last++;
        ret = cht::arr[last].getY(cost[idx]);
        // inserting
        cht::add({ height[idx], ret });
    }
    return ret;
}

