
#include<bits/stdc++.h>
using namespace std;

#define pi      acos(-1.00)
#define eps     1e-11
#define D(x)    cout << #x " = " << (x) << endl

bool eq(double a, double b) { return fabs( a - b ) < eps; } //two numbers are equal

/*
Good to know:
-> Cross product is distributive over addition: a x (b + c) = a x b + a x c
-> Cross product is anticommutative  a x b = -(b x a)
-> Cross product is not associative a x ( b x c ) != (a x b) x c
*/

struct point{
    double x, y, z;
    point(){}
    point(double xx, double yy, double zz) {x = xx, y = yy, z = zz;} // NEVER USE xx = 0 or yy = 0 HERE

    void takeInput(){
        cin >> x >> y >> z;
    }

} origin = point(0, 0, 0); //OK

point operator+(const point &u, const point &v) {return point(u.x + v.x, u.y + v.y, u.z + v.z);} //OK
point operator-(const point &u, const point &v) {return point(u.x - v.x, u.y - v.y, u.z - v.z);} //OK
point operator*(const point &u, double v) {return point(u.x*v, u.y*v, u.z*v);} //OK
point operator*(double v, const point &u) {return point(u.x*v, u.y*v, u.z*v);} //OK

point operator/(const point &u, double v) {assert(abs(v) > eps); return point(u.x/v, u.y/v, u.z/v);}
bool operator != (const point &u, const point &v) {return !(eq(u.x, v.x) && eq(u.y, v.y) && eq(u.z, v.z));}

ostream &operator <<(ostream &os, const point &p) {
  os << "(" << p.x << "," << p.y << "," << p.z << ")";
}

double norm(point u){return sqrt(u.x * u.x + u.y * u.y + u.z * u.z);} //OK
double dotp(point u, point v) {return u.x * v.x + u.y * v.y + u.z * v.z;} //OK
point crsp(point u, point v) {return point(u.y*v.z-u.z*v.y, u.z*v.x-u.x*v.z, u.x*v.y-u.y*v.x);} //OK

struct plane{
	double a, b, c, d; //ax + by + cz + d = 0
	plane(){;}
	plane(point p1, point p2, point p3){
		point vtr = crsp(p2 - p1, p3 - p1);
		if(norm(vtr) < eps) {assert(false);} // doesn't define a plance
		a = vtr.x;
		b = vtr.y;
		c = vtr.z;
		d = -p1.x*vtr.x -p1.y*vtr.y - p1.z * vtr.z;
	}
};

double smlr_angle(point l, point m, point r)
{
    double d = dotp(l - m, r - m);
    return acos(d / (norm(l-m) * norm(r-m)));
}

point unit_vector(point u) { return u / norm(u); } //OK
point projection(point p, point st, point ed) { return dotp(ed - st, p - st) / norm(ed - st) * unit_vector(ed - st) + st;} //OK
point extend(point st, point ed, double len) { return ed + unit_vector(ed-st) * len;} //OK

point rtt(point axis, point p, double theta){
    axis = unit_vector(axis);
    return p * cos(theta) +  sin(theta) * crsp(axis, p) + axis * (1-cos(theta)) * dotp(axis, p);
} //OK

point segmentProjection(point p, point st, point ed)
{
    double d = dotp(p - st, ed - st) / norm(ed - st);
    if(d < 0) return st;
    if(d > norm(ed - st) + eps) return ed;
    return st + unit_vector(ed - st) * d;
} //OK

double distancePointSegment(point p, point st, point ed) {return norm(p - segmentProjection(p, st, ed)); } //OK
double distancePointLine( point P, point st, point ed) { return norm( projection(P, st, ed) - P ); } //OK

double pointPlaneDistance(plane P, point q){
	return fabs(P.a * q.x + P.b * q.y + P.c * q.z + P.d) / sqrt(P.a * P.a + P.b * P.b + P.c * P.c); //OK
}
double pointPlaneDistance(point p1, point p2, point p3, point q){ return pointPlaneDistance(plane(p1,p2,p3), q); } //OK

point reflection(point p, point st, point ed){
    point proj = projection(p, st, ed);
    if(p != proj) return extend(p, proj, norm(p - proj));
    return proj;
} //OK

bool coplanar(point p1, point p2, point p3, point q)
{
    p2 = p2-p1, p3 = p3-p1, q = q-p1;
    if( fabs( dotp(q, crsp(p2, p3)) ) < eps ) return true;
    return false;
}

int linePlaneIntersection(point u, point v, point l, point m, point r, point &x){
    /*
        -> l, m, r defines the plane
        -> u, v defines the line
        -> returns 0 when does not intersect
        -> returns 1 when there exists one unique common point
        -> returns -1 when there exists infinite number of common point
    */

    assert(l != m && m != r && l != r && u != v);
    if(coplanar(l, m, r, u) && coplanar(l, m, r, v)) return -1;
    l = l - m;
    r = r - m;
    u = u - m;
    v = v - m;

    point C = crsp(l, r);
    double denom = dotp(v - u, C);
    if(fabs(denom) < eps) return 0;

    double alpha = -dotp(C, u) / denom;
    x = u + (v - u) * alpha + m;

    return 1;
}

double angle(point u, point v) { return acos(dotp(u, v) / (norm(u) * norm(v)));}


int main()
{
    return 0;
}


