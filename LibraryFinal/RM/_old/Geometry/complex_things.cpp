
#include<bits/stdc++.h>
using namespace std;

#define pi      acos(-1.00)
#define eps     1e-9
#define D(x)    cout << #x " = " << (x) << endl

const int inf = numeric_limits<int>::max();
bool eq(double a, double b) { return fabs( a - b ) < eps; } //two numbers are equal

/*
Good to know:
-> Cross product is distributive over addition: a x (b + c) = a x b + a x c
-> Cross product is anticommutative  a x b = -(b x a)
-> Cross product is not associative a x ( b x c ) != (a x b) x c
-> Dot product is distributive over addition: A.(B+C) = A.B + A.C.
*/

struct point{
    double x, y;
    point(){}

    point(double xx, double yy) {x = xx, y = yy;} // NEVER USE xx = 0 or yy = 0 HERE
} origin = point(0, 0);

struct line { // Creates a line with equation ax + by + c = 0
	double a, b, c;
	point p1, p2;

	line() {}
	line(double _a, double _b, double _c){
	    a = _a, b = _b, c = _c;
        assert( !(eq(a, 0) && eq(b, 0) ) );

        if(eq(a, 0)) p1 = point(0, -c/b), p2 = point(1, -c/b);
        else if(eq(b, 0)) p1 = point( -c/a, 0), p2 = point( -c/a, 1);
        else p1 = point(0, -c/b), p2 = point(-c/a, 0);
	}
	line( point _p1,point _p2 ) {
	    p1 = _p1, p2 = _p2;

		a = p1.y - p2.y;
		b = p2.x - p1.x;
		c = p1.x * p2.y - p2.x * p1.y;
	}
};

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

double smlr_angle(point l, point m, point r) {return abs(remainder(arg(l-m) - arg(r-m), 2.0 * pi)); } //OK

point unit_vector(point u) { return u / norm(u); } //OK
point rtt(point piv, point u, double theta) {return (u - piv) * polar(1.00, theta) + piv;} //OK
point projection(point p, point st, point ed) { return dotp(ed - st, p - st) / norm(ed - st) * unit_vector(ed - st) + st;} //OK
point extend(point st, point ed, double len) { return ed + unit_vector(ed-st) * len;} //OK

point segmentProjection(point p, point st, point ed)
{
    double d = dotp(p - st, ed - st) / norm(ed - st);
    if(d < 0) return st;
    if(d > norm(ed - st) + eps) return ed;
    return st + unit_vector(ed - st) * d;
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

int lineLineIntersection(line L1, line L2, point &ret){
    return lineLineIntersection(L1.p1, L1.p2, L2.p1, L2.p2, ret);
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

double angle(point u, point v) { return acos(dotp(u, v) / (norm(u) * norm(v)));}


///OK?
bool inDisk(point a, point b, point p) { return dotp(a-p, b-p) <= eps;}
bool onSegment(point x, point l, point r){
    return eq(crsp(l - x, r - x), 0) && inDisk(l, r, x);
}

bool segSegIntersection(point u, point v, point a, point b){
    double ang1 = crsp(a - v, u - v);
    double ang2 = crsp(b - v, u - v);
    if(ang1 > eps && ang2 > eps) return false;
    if(ang1 < -eps && ang2 < -eps) return false;

    if(fabs(ang1) < eps || fabs(ang2) < eps)
    {
        if(fabs(ang1) < eps){
            if(onSegment(a, u, v)) return true;
        }
        if(fabs(ang2) < eps){
            if(onSegment(b, u, v)) return true;
        }

        return false;
    }

    swap(u, a);
    swap(v, b);
    ang1 = crsp(a - v, u - v);
    ang2 = crsp(b - v, u - v);
    if(ang1 > eps && ang2 > eps) return false;
    if(ang1 < -eps && ang2 < -eps) return false;

    if(fabs(ang1) < eps || fabs(ang2) < eps)
    {
        if(fabs(ang1) < eps){
            if(onSegment(a, u, v)) return true;
        }
        if(fabs(ang2) < eps){
            if(onSegment(b, u, v)) return true;
        }

        return false;
    }

    return true;
}

struct vline{
    point v;
    double c;

    vline(double a, double b, double _c){ /// a * x + b * y + _c = 0
        /*
            Let (-b, a) be a vector
            (-b, a) x (x, y) = -(_c) when (x, y) belongs to the line

            INVARIENT: v x (any_point_on_the_line) = c
        */
        v = point(-b, a);
        c = -(_c);
    }
    vline(point _v, double _c){
        v = _v;
        c = _c;
    }
    vline(point p, point q){
        v = q - p;
        c = crsp(v, p);
    }

    line get_line(){ return line(v.y, -v.x, -c); }
};

vline translate(vline l, point t) {return vline(l.v, l.c + crsp(l.v, t));}

vline angBisector(vline l1, vline l2, bool interior) {
    assert(!(eq(crsp(l1.v, l2.v), 0)));
    double sign = interior ? 1 : -1;
    return {l2.v/norm(l2.v) + sign * l1.v/norm(l1.v), l2.c/norm(l2.v) + sign * l1.c/norm(l1.v)};
}


int main()
{
    point p = point(0, 10);
    point q = point(10, 0);

    vline l1 = vline(origin, p);
    vline l2 = vline(origin, q);
    vline l = angBisector(l1, l2, true);
    line x = l.get_line();
    D(x.a);
    D(x.b);
    D(x.c);

    point r = point(5, 5);
    D(onSegment(r, p, q));

    return 0;
}
