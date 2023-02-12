
//Complex things:
struct point{
    double x, y;
    point(){}
    point(double xx, double yy) {x = xx, y = yy;} // NEVER USE xx = 0 or yy = 0 HERE
};

struct line { // Creates a line with equation ax + by + c = 0
	double a, b, c;
	line() {}
	line( point p1,point p2 ) {
		a = p1.y - p2.y;
		b = p2.x - p1.x;
		c = p1.x * p2.y - p2.x * p1.y;
	}
};

namespace std{
    point operator+(const point &u, const point &v) {return point(u.x + v.x, u.y + v.y);}
    point operator-(const point &u, const point &v) {return point(u.x - v.x, u.y - v.y);}
    point operator*(const point &u, const point &v) {return point(u.x * v.x - u.y * v.y, u.x * v.y + v.x * u.y);}
    point operator*(const point &u, double v) {return point(u.x*v, u.y*v);}
    point operator*(double v, const point &u) {return point(u.x*v, u.y*v);}
    point operator/(const point &u, double v) {assert(abs(v) > eps); return point(u.x/v, u.y/v);}
    bool operator <(const point &u, const point &v){
        if(fabs(u.x - v.x ) < eps) return u.y + eps < v.y;
        return u.x + eps < v.x;
    }
}

point conj(point u) {return point(u.x, -u.y);}
double norm(point u){return u.x * u.x + u.y * u.y;}
double abs(point u){return sqrt(norm(u));}
double arg(point u){return atan2(u.y, u.x);}
point polar(double r, double theta) {return point(r * cos(theta), r * sin(theta));}

bool eq(double a, double b) { return fabs( a - b ) < eps; } //two numbers are equal
double dotp(point u, point v) {return (conj(u) * v).x; }
double crsp(point u, point v) {return (conj(u) * v).y; }
double squared_dt(point u, point v) {return norm(u-v); }
double euclidean_dt(point u, point v) {return abs(u-v); }
double angle_of_elevation(point u, point v) {return arg(v-u);}
/*The angle of elevation of an object as seen by an observer
is the angle between the horizontal and the line from the object
to the observer's eye (the line of sight).*/
double slope_of_line(point u, point v) {return tan(arg(v - u)); }
double smlr_angle(point l, point m, point r) {return abs(remainder(arg(l-m) - arg(r-m), 2.0 * pi)); }
point unit_vector(point u) {return u / abs(u); }
point rtt(point piv, point u, double theta) {return (u - piv) * polar(1.00, theta) + piv;}
point proj_helper(point p, point Orgn) {return dotp(p, Orgn) / norm(Orgn) * Orgn; }
point projection(point p, point st, point ed) {return proj_helper(p-st, ed-st) + st; }
point extend(point st, point ed, double len) { return st + unit_vector(ed-st) * len;}
point reflection(point p, point st, point ed){
    point proj = projection(p, st, ed);
    return extend(p, proj, euclidean_dt(p, proj));
}
point intersection(point a, point b, point p, point q){
    double c1 = crsp(p - a, b - a), c2 = crsp(q - a, b - a);
    return (c1 * q - c2 * p) / (c1 - c2); // Undefined if parallel
}
double perpendicular_dt( point P, point st, point ed) { return abs(crsp(P-st, ed-st) / abs(P-st)); }
line findPerpendicularLine( line L, point P ) {
    line res;
	res.a = L.b, res.b = -L.a;
	res.c = -res.a * P.x - res.b * P.y;
	return res;
}

