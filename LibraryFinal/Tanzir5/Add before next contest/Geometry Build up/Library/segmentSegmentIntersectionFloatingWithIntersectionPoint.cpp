struct segment { // Creates a segment with two end points -> A, B
	point A, B;
	segment() {}
	segment( point P1, point P2 ) { A = P1, B = P2; }
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

bool eq(double a, double b)
{
    return fabs(a-b) < eps;
}

double dist(point a, point b)
{
    return sqrt( (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

inline bool intersection( line L1, line L2, point &p ) {
	double det = L1.a * L2.b - L1.b * L2.a;
	if( eq ( det, 0 ) ) return false;
	p.x = ( L1.b * L2.c - L2.b * L1.c ) / det;
	p.y = ( L1.c * L2.a - L2.c * L1.a ) / det;
	return true;
}


inline bool intersection( segment L1, segment L2, point &p ) {
	if( !intersection( line( L1.A, L1.B ), line( L2.A, L2.B ), p) ) {
		return false; // can lie on another, just check their equations, and check overlap
	}
	return(eq(dist(L1.A,p)+dist(L1.B,p),dist(L1.A,L1.B)) &&
		eq(dist(L2.A,p)+dist(L2.B,p),dist(L2.A,L2.B)));
}


