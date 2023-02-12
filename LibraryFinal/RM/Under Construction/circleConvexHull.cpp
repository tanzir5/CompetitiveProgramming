
#include<bits/stdc++.h>
using namespace std;
#define D(x)    cout << #x " = " << (x) << endl
#define MAX     200
typedef long long int LL;

const double eps = 1e-10;
const double pi = acos(-1.0);

int dcmp(double x){
    return fabs(x) < eps ? 0 : (x > 0 ? 1 : -1);
}

double eq(double u, double v) {return fabs(u - v) < eps;}

struct point{
    double x, y;
    point(){}
    point(double x, double y):x(x), y(y){}

    bool operator < (const point &e)const{
        return dcmp(x - e.x) < 0 || (dcmp(x - e.x) == 0 && dcmp(y - e.y) < 0);
    }
    int read(){
        return scanf("%lf %lf", &x, &y);
    }
} p[3];

point operator + (const point &u, const point &v) {return point(u.x + v.x, u.y + v.y); }
point operator - (const point &u, const point &v) {return point(u.x - v.x, u.y - v.y); }
point operator * (const point &u, double v) {return point(u.x * v, u.y * v);}
point operator * (double v, const point &u) {return point(u.x * v, u.y * v);}
point operator / (const point &u, double v) {if(dcmp(v) == 0) {while(true);} return point(u.x / v, u.y / v); }
point operator / (double v, const point &u) {if(dcmp(v) == 0) {while(true);} return point(u.x / v, u.y / v); }
double dotp(point u, point v) {return u.x * v.x + u.y * v.y;}
double norm(point u) {return sqrt(dotp(u, u));}
double crsp(point u, point v) {return u.x * v.y - u.y * v.x;}
point unit_vector(point u) {return u / norm(u);}
point projection(point p, point st, point ed) { return dotp(ed - st, p - st) / norm(ed - st) * unit_vector(ed - st) + st;}
double arg(point u) {return atan2(u.y , u.x);}

double distancePointLine(point P, point st, point ed){
    return norm(projection(P, st, ed) - P);
}

int side(point u, point v, point q){
    return dcmp(crsp(v - u, q - u));
}

struct circle{
    double x, y, r;
    circle(double x, double y, double r): x(x), y(y), r(r){}

    void read(){
        scanf("%lf %lf %lf", &x, &y, &r);
        D(x);
        D(y);
        D(r);
        /// r += 10 ?
    }

    point center(){
        return point(x, y);
    }

    point Point(double a){

        point ret = point(x + r * cos(a), y + r * sin(a));
        assert(!dcmp(norm(ret - point(x, y)) - r));
        return ret;
    }

    bool contains(circle ano){
        double d = norm(point(x, y) - point(ano.x, ano.y));
        if( d + ano.r <= r + eps) return true;
        return false;
    }

    double getmax(){return max(max(x, y), r);}
};

double circleLineDistance(circle C, point u, point v){
    return distancePointLine(point(C.x, C.y), u, v);
}

int getTangents(circle A, circle B, point *a, point *b)
{
    int cnt = 0;
    if(dcmp(A.r - B.r) < 0){
        swap(A, B);
        swap(a, b);
    }
    double d = sqrt((A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y));
    double rdiff = A.r - B.r;
    double rsum = A.r + B.r;
    if(dcmp(d - rdiff) < 0) return 0;
    double base = atan2(B.y - A.y, B.x - A.x);
    if(dcmp(d) == 0) return -1;
    if(dcmp(d - rdiff) == 0)
    {
        a[cnt] = b[cnt] = A.Point(base);
        cnt++;
        return 1;
    }
    double ang = acos((A.r - B.r) / d);
    a[cnt] = A.Point(base + ang); b[cnt] = B.Point(base + ang); cnt++;
    a[cnt] = A.Point(base - ang); b[cnt] = B.Point(base - ang); cnt++;
    return cnt;
}

point a[10], b[10];

vector < circle > C;

struct tang{
    point st, ed;
    int outGoing;
    tang(point _st, point _ed, int out = false){
        st = _st;
        ed = _ed;
        outGoing = out;
    }
};

vector < tang > imp_tang[MAX + 5];
map < tuple < int , int , int >, int > M;
int invalid[MAX+5];

point origin;
bool cmp(tang u, tang v){
    return arg(u.st - origin) + eps < arg(v.st - origin);
}

double angle1(point l, point m, point r){
    return abs(remainder(arg(l - m) - arg(r - m), 2.0 * pi));
}

double angle(point l, point m, point r){
    double ret = crsp(l - m, r - m);
    if(ret < eps) return angle1(l, m, r);
    return 2 * pi - angle1(l, m, r);
}

int glb;

int main()
{
//    freopen("in.txt", "r", stdin);
//    freopen("12.in", "r", stdin);


    int n, x, y, r, i, j, k;
    double len = 0;

    scanf("%d", &n);
    for(i = 0; i < n; i++){
        scanf("%d %d %d", &x, &y, &r);
        tuple <int,int,int> t = make_tuple(x, y, r);
        if(M.find(t) == M.end()){
            C.push_back(circle(x, y, r + 10.0));
            M[t] = 1;
        }
    }

    n = C.size();
    for(i = 0; i < n; i++)
    {
        int counter = 0;
        for(j = 0; j < n; j++)
            if(i != j && C[i].contains(C[j]))
            {
                invalid[j] = true;
                counter++;
            }

        if(counter == n - 1){
            printf("%0.10f\n", 2 * pi * C[i].r);
            return 0;
        }
    }

    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++){
            if(i == j) continue;

            if(invalid[i] || invalid[j]) continue;
            int c = getTangents(C[i], C[j], a, b);
            assert(c == 2);

            for(int t = 0; t < c; t++){
                point st = a[t];
                point ed = b[t];

                bool valid = true;


                for(k = 0; k < n; k++)
                    if(dcmp(side(st, ed, point(C[k].x, C[k].y)) >= 0))  valid = false;

                for(k = 0; k < n; k++){
                    if(i == k || j == k || invalid[k]) continue;
                    double d = circleLineDistance(C[k], st, ed);
                    if(d + eps < C[k].r){valid = false;}
                    else if(eq(d, C[k].r)){
                        double ij = sqrt( norm(C[j].center() - st) * norm(C[j].center() - st) - C[j].r * C[j].r);
                        double ik = sqrt( norm(C[k].center() - st) * norm(C[k].center() - st) - C[k].r * C[k].r);
                        double jk = sqrt( norm(C[k].center() - ed) * norm(C[k].center() - ed) - C[k].r * C[k].r);

                        if(eq(ij + jk, ik)) valid = false;
                        if(eq(ik + ij, jk)) valid = false;

                    }
                }

                if(valid) {
                    imp_tang[i].push_back(tang(st, ed, true));
                    imp_tang[j].push_back(tang(ed, st, false));
                    len += norm(ed - st);
                }
            }
        }

    for(i = 0; i < n; i++)
        if(imp_tang[i].size()){
            origin = point(C[i].x, C[i].y);

            sort(imp_tang[i].begin(), imp_tang[i].end(), cmp);
            reverse(imp_tang[i].begin(), imp_tang[i].end());

            for(j = 0; j < (int) imp_tang[i].size(); j++){
                k = (j + 1) % imp_tang[i].size();

                if(imp_tang[i][j].outGoing == false)
                {
                    if(imp_tang[i][k].outGoing == false){
                        for(auto tn : imp_tang[i]){
                            D(glb);
                            D(tn.st.x);
                            D(tn.st.y);
                            D(tn.ed.x);
                            D(tn.ed.y);
                            D(tn.outGoing);
                            puts("");
                        }
                        assert(false);
                        return 0;
                    }
                    assert(imp_tang[i][k].outGoing == true);
                    double theta = angle(imp_tang[i][j].st, C[i].center(), imp_tang[i][k].st);
                    len += C[i].r * theta;
                }
            }
        }


    printf("%0.10f\n", len);
    return 0;
}
