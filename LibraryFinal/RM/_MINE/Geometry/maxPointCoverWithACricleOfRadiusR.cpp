
#include<bits/stdc++.h>
using namespace std;
#define sf(n)       scanf("%d", &n)
#define sff(a,b)    scanf("%d %d", &a, &b)
#define sfff(a,b,c) scanf("%d %d %d", &a, &b, &c)
#define pb          push_back
#define mp          make_pair
#define xx          first
#define yy          second
#define MAX         2000
#define eps         1e-9
#define pi          acos(-1.00)

struct point{
    double x, y;
    point(){}
    point(double xx, double yy){x = xx, y = yy;}
};

point operator+(const point &u, const point &v){return point(u.x + v.x, u.y + v.y);}
point operator-(const point &u, const point &v){return point(u.x - v.x, u.y - v.y);}
bool operator == (const point &u, const point &v) {return fabs(u.x - v.x) < eps && fabs(u.y - v.y ) < eps;}

double norm(point u) {return u.x*u.x + u.y*u.y;}
double abs(point u) {return sqrt(norm(u));}
double arg(point u) {return atan2(u.y, u.x);}
double get_angle(double a, double b, double c) {return acos( (b*b+c*c-a*a)/(2*b*c) ); }

bool cmp(pair< double, int> u, pair< double, int> v)
{
    if(fabs(u.xx - v.xx) < eps) return u.yy > v.yy + eps;
    return u.xx + eps < v.xx;
}

int getMaxInt(vector < pair< double, int> > &vec)
{
    stable_sort(vec.begin(), vec.end(), cmp);
    int ret = 0, mx = 0;
    for(auto x : vec)
    {
        mx += x.yy;
        ret = max(ret, mx);
    }

    return ret;
}

int maxPointCover(double radius, point pnt[], int n)
{
    int i, j, ret = (bool) n, cnt;
    vector< pair< double, int> > ep[2];

    for(i = 1; i <= n; i++)
    {
        ep[0].clear();
        ep[1].clear();
        cnt = 0;

        for(j = 1; j <= n; j++)
        {
            if(pnt[i] == pnt[j]){
                cnt++;
                continue;
            }
            if(abs(pnt[j] - pnt[i]) > 2 * radius + eps) continue;

            double ang = get_angle(radius, abs(pnt[j] - pnt[i]), radius);
            double curr = arg(pnt[j] - pnt[i]);

            double seg_st = remainder(curr - ang, 2*pi);
            double seg_ed = remainder(curr + ang, 2*pi);

            if(seg_st + eps < 0 && seg_ed > eps){
                ep[0].pb(mp(0, +1));
                ep[0].pb(mp(abs(seg_st), -1));

                ep[1].pb(mp(0, +1));
                ep[1].pb(mp(seg_ed, -1));
            }
            else if(seg_st > eps && seg_ed + eps < 0){
                ep[0].pb(mp(abs(seg_ed), +1));
                ep[0].pb(mp(pi, -1));

                ep[1].pb(mp(seg_st, +1));
                ep[1].pb(mp(pi, -1));
            }

            else if(seg_st > eps)
            {
                ep[1].pb(mp(seg_st, +1));
                ep[1].pb(mp(seg_ed, -1));
            }
            else
            {
                ep[0].pb(mp(abs(seg_st), +1));
                ep[0].pb(mp(abs(seg_ed), -1));
            }
        }

        cnt += max(getMaxInt(ep[0]), getMaxInt(ep[1]));
        ret = max(ret, cnt);
    }

    return ret;
}

point P[MAX+5];

int main()
{
    //freopen("in.txt", "r", stdin);
    int i, j, k, n,r;
    int x, y;

    while(sff(n, r) == 2 && (n || r))
    {
        for(i = 1; i <= n; i++)
        {
            sff(x, y);
            P[i] = point(x, y);
        }
        printf("It is possible to cover %d points.\n", maxPointCover(r, P, n));
    }
    return 0;
}






