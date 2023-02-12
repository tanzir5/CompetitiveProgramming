
#include<bits/stdc++.h>
using namespace std;

#define pi      acos(-1.00)
#define eps     1e-9
#define D(x)    cout << #x " = " << (x) << endl

const int inf = numeric_limits<int>::max();
bool eq(double a, double b) { return fabs( a - b ) < eps; } //two numbers are equal

/// *** CHANGING *** ///

int sgn(double value){
    if(eq(value, 0)) return 0;
    if(value + eps < 0) return -1;
    return +1;
}

/*
Good to know:
-> Cross product is distributive over addition: a x (b + c) = a x b + a x c
-> Cross product is anticommutative  a x b = -(b x a)
-> Cross product is not associative a x ( b x c ) != (a x b) x c
-> Dot product is distributive over addition: A.(B+C) = A.B + A.C.
-> Cross product is distributive over addition: A x (B+C) = A x B + A x C.
*/

/// *** CHANGING *** ///


struct point{
    double x, y;
    point(){}

    point(double xx, double yy) {x = xx, y = yy;} // NEVER USE xx = 0 or yy = 0 HERE
} origin = point(0, 0);

point operator+(const point &u, const point &v) {return point(u.x + v.x, u.y + v.y);} //OK
point operator-(const point &u, const point &v) {return point(u.x - v.x, u.y - v.y);} //OK
point operator*(const point &u, const point &v) {return point(u.x * v.x - u.y * v.y, u.x * v.y + v.x * u.y);} // multiplying two complex numbers
point operator*(const point &u, double v) {return point(u.x*v, u.y*v);} //OK
point operator*(double v, const point &u) {return point(u.x*v, u.y*v);} //OK
point operator/(const point &u, double v) {assert(abs(v) > eps); return point(u.x/v, u.y/v);} //OK
bool operator != (const point &u, const point &v) {return !(eq(u.x, v.x) && eq(u.y, v.y));} //OK

bool operator <(const point &u, const point &v){
    if(fabs(u.x - v.x ) < eps) return u.y + eps < v.y;
    return u.x + eps < v.x;
}

double norm(point u){return sqrt(u.x * u.x + u.y * u.y);} //OK
double arg(point u){ assert(u != origin); return atan2(u.y, u.x);} //OK
point polar(double r, double theta) {return point(r * cos(theta), r * sin(theta));} //OK

double dotp(point u, point v) {return u.x * v.x + u.y * v.y;} //OK
double crsp(point u, point v) {return u.x * v.y - u.y * v.x;} //OK

point univ(point u) { return u / norm(u); } //OK
point projection(point p, point st, point ed) { return dotp(ed - st, p - st) / norm(ed - st) * univ(ed - st) + st;} //OK

/// *** CHANGING *** ///


double sq(point u){return dotp(u, u);}
point perp(point u) {return {-u.y, u.x};}


point operator / (const point &u, const point &v){
    double a = u.x, b = u.y, c = v.x, d = v.y;
    return {(a * c + b * d) / (c * c + d * d), (b * c - a * d) / (c * c + d * d)};
}

point linearTransformation(point a, point b, point q, point fa, point fb){
    return fa + (q - a) * (fb - fa) / (b - a);
}

/*
    CAUTION: DIRECTED LINE, DIRECTION MATTERS
    To make the lines undirected:
        - make sure that the v vector lies in 1st or 4th quad
        - To make that sure reflect accordingly
*/

struct line {
    point v; double c; /// v = direction vector of the line, c = distance from origin to line * norm(v)

    line(double aa, double bb, double cc){ /// a * x + b * y = c [ notice here ]
        v = {bb, -aa};
        c = cc;
    }

    line(point vv, double cc){
        v = vv;
        c = cc;
    }

    line(point uu, point vv){
        v = vv - uu;
        c = crsp(v, uu);
    }

    //Preserves the direction
    point get_p1(){ return univ(perp(v)) * c / norm(v); }
    point get_p2(){ return get_p1() + v; }

    double side(point p){ return crsp(v, p) - c; }
    double singed_dist(point p){ return (side(p)) / norm(v); }
    double dist(point p){ return abs(singed_dist(p)); }

    line perpThrough(point p){ return {p, p + perp(v)}; }
    line translate(point t){return {v, c + crsp(v, t)};}
    line shiftLeft(double dlta) {return {v, c + dlta * norm(v)};}

    point project(point p){
        double d = singed_dist(p);
        return p - univ(perp(v)) * d;
    }

    point reflect(point p){
        double d = singed_dist(p);
        return p - 2 * univ(perp(v)) * d;
    }
};

bool intersection(line l1, line l2, point &out){
    double d = crsp(l1.v, l2.v);
    if(eq(d, 0)) return false;
    out = (l2.v * l1.c - l1.v * l2.c) / d;
    return true;
}

line bisector(line l1, line l2, bool interior) {
    assert(eq(crsp(l1.v, l2.v), 0) == false); // l1 and l2 cannot be parallel!
    double sign = interior ? 1 : -1;
    return {l2.v/norm(l2.v) + l1.v/norm(l1.v) * sign,
    l2.c/norm(l2.v) + l1.c/norm(l1.v) * sign};
}

/// *** CHANGING *** ///


double angle(point u, point v) { return acos( max(-1.0, min(1.0, dotp(u, v) / (norm(u) * norm(v)))) );}
point rtt(point piv, point u, double theta) {return (u - piv) * polar(1.00, theta) + piv;} //OK
point extend(point st, point ed, double len) { return ed + univ(ed-st) * len;} //OK

point segmentProjection(point p, point st, point ed)
{
    double d = dotp(p - st, ed - st) / norm(ed - st);
    if(d < 0) return st;
    if(d > norm(ed - st) + eps) return ed;
    return st + univ(ed - st) * d;
} //OK

double distancePointSegment(point p, point st, point ed) {return norm(p - segmentProjection(p, st, ed)); } //OK
double distancePointLine( point P, point st, point ed) { return norm( projection(P, st, ed) - P ); } //OK

point reflection(point p, point st, point ed){
    point proj = projection(p, st, ed);
    if(p != proj) return extend(p, proj, norm(p - proj));
    return proj;
} //OK

bool collinear(point p, point st, point ed) {return fabs(crsp(p - st, ed -st)) < eps; }

int lineLineIntersection(point a, point b, point p, point q, point &ret){
    if(fabs(crsp(b - a, p - q)) < eps){
        if(collinear(a, p, q)) { ret = a; return inf; }
        return 0;
    }
    else {
        ret = a + (b - a) * crsp(p - a, p - q) / crsp(b - a, p - q);
        return 1;
    }
}


bool segmentSegmentIntersection(point a, point b, point p, point q, point &ret)
{
    if( fabs(crsp(b - a, q - p)) < eps ) {
        if( eq(norm(a - p) + norm(q - a), norm(q - p) ) ) {ret = a; return true;}
        if( eq(norm(b - p) + norm(q - b), norm(q - p) ) ) {ret = b; return true;}
        return false;
    }

    double dir1 = crsp(b - a, p - a), dir2 = crsp(b - a, q - a);
    if( (dir1 + eps < 0 && dir2 + eps < 0) || (dir1 > eps && dir2 > eps) ) return false;

    dir1 = crsp(q - p, a - p), dir2 = crsp(q - p, b - p);
    if( (dir1 + eps < 0 && dir2 + eps < 0) || (dir1 > eps && dir2 > eps) ) return false;

    return lineLineIntersection(a, b, p, q, ret);
}

/// *** CHANGING *** ///

double distanceSegmentSegment(point a, point b, point p, point q){
    point dummy;
    if(segmentSegmentIntersection(a, b, p, q, dummy)) return 0;
    return min(distancePointSegment(a, p, q), min(distancePointSegment(b, p, q),
           min(distancePointSegment(p, a, b), distancePointSegment(q, a, b))));
}

/// *** CHANGING *** ///


point circumCircleCenter(point u, point v, point w)
{
    assert(collinear(u, v, w) == false);
    point vw_mid = (v + w) / 2;
    point uv_mid = (u + v) / 2;

    point ret;
    lineLineIntersection(vw_mid, rtt(vw_mid, extend(v, vw_mid, 1), pi/2),
                         uv_mid, rtt(uv_mid, extend(u, uv_mid, 1), pi/2), ret);

    return ret;
}

///OK?
bool inDisk(point a, point b, point p) { return dotp(a-p, b-p) <= eps;}
bool onSegment(point x, point l, point r){
    return eq(crsp(l - x, r - x), 0) && inDisk(l, r, x);
}


/// *** CHANGING *** ///

int circleLine(point o, double r, line l, pair<point, point> &ret){
    point p = l.project(o);
    if(norm(p - o) > r + eps) return 0;
    double h = sqrt(r * r - sq(p - o));
    ret = { p + univ(l.v) * h , p - univ(l.v) * h };

    return 1 + sgn(h);
}

int circleCircle(point o1, double r1, point o2, double r2, pair<point, point> &ret){
    point d = o2 - o1; double d2 = sq(o2 - o1);
    if(eq(d2, 0)){ //concentric circles
        assert(eq(r1, r2) == false);
        return 0;
    }

    double pd = (d2 + r1 * r1 - r2 * r2)/2;
    double h2 = r1 * r1 - pd * pd / d2;
    if(h2 + eps > 0){
        point p = o1 + d * pd/d2, h = univ(perp(d)) * sqrt(h2);
        ret = {p - h, p + h};
    }
    return 1 + sgn(h2);
}

int tangents(point o1, double r1, point o2, double r2, bool inner, vector< pair<point,point> > &ret) {
    if (inner) r2 = -r2;
    point d = o2-o1;
    double dr = r1-r2, d2 = sq(d), h2 = d2-dr*dr;
    if (eq(d2, 0) || h2 + eps < 0) {assert(eq(h2, 0) == false); return 0;}
    for (double sign : {-1,1}) {
        point v = (d*dr + perp(d)*sqrt(h2)*sign)/d2;
        ret.push_back({o1 + v*r1, o2 + v*r2});
    }
    return 1 + (h2 > 0);
}

/// *** CHANGING *** ///

vector< pair < point, point > > ret;

int main()
{

    return 0;
}

