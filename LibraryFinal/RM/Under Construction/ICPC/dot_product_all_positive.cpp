
#include<bits/stdc++.h>
using namespace std;
#define D(x)        cout << #x " = " << (x) << endl
#define MAX         500000
#define eps         1e-9
typedef long long  LL;


int n;
struct Line{
        LL m,c;
        Line(LL _m = 0, LL _c = 0):m(_m), c(_c){};
};

bool operator < (const Line &u, const Line &v){
    return u.m > v.m;
}

struct fraction{
    LL up, dwn;
    fraction(){}
    fraction(LL uu, LL dd){
        LL g = __gcd(uu, dd);
        up = uu / g;
        dwn = dd / g;
    }
};

fraction init[MAX+5];

bool operator < (const fraction &a, const fraction &b){
    /*
        a.up / a.dwn  < b.up / b.dwn
    */
    if(a.up / (double) a.dwn + eps < b.up / (double) b.dwn) return true;
    return false;

    if(a.dwn > 0 && b.dwn > 0) return a.up * b.dwn < b.up * a.dwn;
    if(a.dwn < 0 && b.dwn < 0) return a.up * b.dwn < b.up * a.dwn;
    return a.up * b.dwn > b.up * a.dwn;
}


bool operator <= (const fraction &a, const fraction &b){
    if(a < b) return true;
    return a.up * b.dwn == b.up * a.dwn;
}


fraction operator * (const LL &u, fraction &f){
    fraction ret = fraction(u, f.dwn);
    return fraction(ret.up * f.up, ret.dwn);
}


fraction operator + (const fraction &f, const LL &u){
    return fraction(f.up + u * f.dwn, f.dwn);
}

struct ConvexHullTrick{ //works with long long integers.

    vector<Line> Q; //Fast -> Slow -> Slower -> Slowest
    vector<Line> input;
    bool minFlag;
    int lo;

    ConvexHullTrick(bool flg = false):minFlag(flg){lo = 0;};

    fraction getX(Line u, Line v){ // Fast vrs Slow *ORDER MATTERS*
        LL difC = v.c - u.c, difM = u.m - v.m;
        return fraction(difC, difM);
    }



    bool isBad(Line L1, Line L2, Line L3)
    {
        if(minFlag == false) return fraction(L2.c-L1.c, (L1.m - L2.m)) < fraction(L3.c - L1.c , (L1.m - L3.m));
        else return fraction(L3.c - L1.c, (L1.m - L3.m)) < fraction(L2.c-L1.c, (L1.m - L2.m));
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



    void offlineAdd(Line L){
        input.push_back(L);
    }

    void build(){
        sort(input.begin(), input.end());
        for(auto x : input) addLine(x);
    }

    fraction query(fraction pos){
        int hi = (int) Q.size() - 1, n = hi, mid;
        fraction L, R;
        while(true)
        {
            if(lo == hi) break;
            fraction a = Q[lo].m * pos + Q[lo].c;
            fraction b = Q[lo+1].m * pos + Q[lo+1].c;
            if(b < a) lo++;
            else break;
        }
        return Q[lo].m * pos + Q[lo].c;
    }
}cht_mx = ConvexHullTrick(false), cht_mn = ConvexHullTrick(true);

char str[55];
LL x[MAX+5];
LL y[MAX+5];

struct query{
    LL qx, qy, idx;
}Q[MAX+5];

bool operator < (const query &u, const query &v){
    return u.qy * v.qx < v.qy * u.qx;
}

LL answer[MAX+5];

int main()
{
//    freopen("rm.txt", "r", stdin);
//    freopen("fast.txt", "w", stdout);

    int i, m;
    LL mn_y = numeric_limits<LL>::max(), mx_y = numeric_limits<LL>::min();

    scanf("%d", &m);
    for(i = 1; i <= m; i++){
        scanf("%lld %lld", &Q[i].qx, &Q[i].qy);
        Q[i].idx = i;
    }

    scanf("%d", &n);
    for(i = 1; i <= n; i++){
        scanf("%lld %lld", &x[i], &y[i]);
        mn_y = min(mn_y, y[i]);
        mx_y = max(mx_y, y[i]);
    }


    for(i = 1; i <= n; i++) cht_mn.offlineAdd(Line(y[i], x[i]));
    cht_mn.build();

    sort(Q + 1, Q + m + 1);
    for(i = 1; i <= m; i++){
        int qx = Q[i].qx;
        int qy = Q[i].qy;

        if(!qx){
            LL ret = min(qy * mn_y, qy * mx_y);
            answer[Q[i].idx] = ret;
        }
        else{
            fraction ret = cht_mn.query(fraction(qy, qx));
            ret = qx * ret;
            answer[Q[i].idx] = ret.up;
        }
    }

    for(i = 1; i <= m; i++)
        printf("%lld ", answer[i]);
    return 0;
}

