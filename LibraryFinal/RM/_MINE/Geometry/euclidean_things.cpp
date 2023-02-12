
//Euclidean things:
const double eps = 1e-11, pi = 2 * acos( 0.0 );

struct point { // Creates normal 2D point
	double x, y;
	point() {}
	point( double xx, double yy ) { x = xx, y = yy; }
};
struct point3D { // Creates normal 3D point
	double x, y, z;
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
struct circle { // Creates a circle with point 'center' as center and r as radius
	point center;
	double r;
	circle() {}
	circle( point P, double rr ) { center = P; r = rr; }
};
struct segment { // Creates a segment with two end points -> A, B
	point A, B;
	segment() {}
	segment( point P1, point P2 ) { A = P1, B = P2; }
};

inline bool eq(double a, double b) { return fabs( a - b ) < eps; } //two numbers are equal

//Distance - Point, Point:
inline double Distance( point a, point b ) {
	return sqrt( ( a.x - b.x ) * ( a.x - b.x ) + ( a.y - b.y ) * ( a.y - b.y ) );
}

//Distance^2 - Point, Point:
inline double sq_Distance( point a, point b ) {
	return ( a.x - b.x ) * ( a.x - b.x ) + ( a.y - b.y ) * ( a.y - b.y );
}

//Distance - Point, Line:
inline double Distance( point P, line L ) {
	return fabs( L.a * P.x + L.b * P.y + L.c ) / sqrt( L.a * L.a + L.b * L.b );
}

inline double isleft( point p0, point p1, point p2 ) {
	return( ( p1.x - p0.x ) * ( p2.y - p0.y ) - ( p2.x - p0.x ) * ( p1.y - p0.y ) );
}

//Intersection - Line, Line:
inline bool intersection( line L1, line L2, point &p ) {
	double det = L1.a * L2.b - L1.b * L2.a;
	if( eq ( det, 0 ) ) return false;
	p.x = ( L1.b * L2.c - L2.b * L1.c ) / det;
	p.y = ( L1.c * L2.a - L2.c * L1.a ) / det;
	return true;
}

//Intersection - Segment, Segment:
inline bool intersection( segment L1, segment L2, point &p ) {
	if( !intersection( line( L1.A, L1.B ), line( L2.A, L2.B ), p) ) {
		return false; // can lie on another, just check their equations, and check overlap
	}
	return(eq(Distance(L1.A,p)+Distance(L1.B,p),Distance(L1.A,L1.B)) &&
		eq(Distance(L2.A,p)+Distance(L2.B,p),Distance(L2.A,L2.B)));
}

//Perpendicular Line of a Given Line Through a Point:
inline line findPerpendicularLine( line L, point P ) {
	line res; //line perpendicular to L, and intersects with P
	res.a = L.b, res.b = -L.a;
	res.c = -res.a * P.x - res.b * P.y;
	return res;
}

//Distance - Point, Segment:
inline double Distance( point P, segment S ) {
	line L1 = line(S.A,S.B), L2; point P1;
	L2 = findPerpendicularLine( L1, P );
	if( intersection( L1, L2, P1 ) )
		if( eq ( Distance( S.A, P1 ) + Distance( S.B, P1 ), Distance( S.A, S.B ) ) )
			return Distance(P,L1);
	return min ( Distance( S.A, P), Distance( S.B, P) );
}

//Area of a 2D Polygon:
double areaPolygon( point P[], int n ) {
	double area = 0;
	for( int i = 0, j = n - 1; i < n; j = i++ ) area += P[j].x * P[i].y - P[j].y * P[i].x;
	return fabs(area)/2;
}

//Point Inside Polygon:
bool insidePoly( point &p, point P[], int n ) {
	bool inside = false;
	for( int i = 0, j = n - 1; i < n; j = i++ )
		if( (( P[i].x < p.x ) ^ ( P[j].x < p.x )) &&
(P[i].y - P[j].y) * abs(p.x - P[j].x) < (p.y - P[j].y) * abs(P[i].x - P[j].x) )
			inside = !inside;
	return inside;
}

//Intersection - Circle, Line:
inline bool intersection(circle C,line L,point &p1,point &p2) {
	if( Distance( C.center, L ) > C.r + eps ) return false;
	double a, b, c, d, x = C.center.x, y = C.center.y;
	d = C.r*C.r - x*x - y*y;
	if( eq( L.a, 0) ) {
		p1.y = p2.y = -L.c / L.b;
		a = 1;
		b = 2 * x;
		c = p1.y * p1.y - 2 * p1.y * y - d;
		d = b * b - 4 * a * c;
		d = sqrt( fabs (d) );
		p1.x = ( b + d ) / ( 2 * a );
		p2.x = ( b - d ) / ( 2 * a );
	}
	else {
		a = L.a *L.a + L.b * L.b;
		b = 2 * ( L.a * L.a * y - L.b * L.c - L.a * L.b * x);
		c = L.c * L.c + 2 * L.a * L.c * x - L.a * L.a * d;
		d = b * b - 4 * a * c;
		d = sqrt( fabs(d) );
		p1.y = ( b + d ) / ( 2 * a );
		p2.y = ( b - d ) / ( 2 * a );
		p1.x = ( -L.b * p1.y -L.c ) / L.a;
		p2.x = ( -L.b * p2.y -L.c ) / L.a;
	}
	return true;
}

//Find Points that are r1 unit away from A, and r2 unit away from B:
inline bool findpointAr1Br2(point A,double r1,point B, double r2,point &p1,point &p2) {
	line L;
	circle C;
	L.a = 2 * (B.x - A.x );
	L.b = 2 * (B.y - A.y );
	L.c = A.x * A.x + A.y * A.y - B.x * B.x - B.y * B.y + r2 * r2 - r1 * r1;
	C.center = A;
	C.r = r1;
	return intersection( C, L, p1, p2 );
}

//Intersection Area between Two Circles:
inline double intersectionArea2C( circle C1, circle C2 ) {
	C2.center.x = Distance( C1.center, C2.center );
	C1.center.x = C1.center.y = C2.center.y = 0;
	if( C1.r < C2.center.x - C2.r + eps ) return 0;
	if( -C1.r + eps > C2.center.x - C2.r ) return pi * C1.r * C1.r;
	if( C1.r + eps > C2.center.x + C2.r ) return pi * C2.r * C2.r;
	double c, CAD, CBD, res;
	c = C2.center.x;
	CAD = 2 * acos( (C1.r * C1.r + c * c - C2.r * C2.r) / (2 * C1.r * c) );
	CBD = 2 * acos( (C2.r * C2.r + c * c - C1.r * C1.r) / (2 * C2.r * c) );
	res=C1.r * C1.r * ( CAD - sin( CAD ) ) + C2.r * C2.r * ( CBD - sin ( CBD ) );
	return .5 * res;
}

//Circle Through Thee Points:
circle CircleThrough3points( point A, point B, point C) {
	double den; circle c;
	den = 2.0 *((B.x-A.x)*(C.y-A.y) - (B.y-A.y)*(C.x-A.x));
	c.center.x = ( (C.y-A.y)*(B.x*B.x+B.y*B.y-A.x*A.x-A.y*A.y) -(B.y-A.y)*(C.x*C.x+C.y*C.y-A.x*A.x-A.y*A.y) );
	c.center.x /= den;
	c.center.y =( (B.x-A.x)*(C.x*C.x+C.y*C.y-A.x*A.x-A.y*A.y) - (C.x-A.x)*(B.x*B.x+B.y*B.y-A.x*A.x-A.y*A.y) );
	c.center.y /= den;
	c.r = Distance( c.center, A );
	return c;
}

//Rotating a Point anticlockwise by 'theta' radian w.r.t Origin:
inline point rotate2D( double theta, point P ) {
	point Q;
	Q.x = P.x * cos( theta ) - P.y * sin( theta );
	Q.y = P.x * sin( theta ) + P.y * cos( theta );
	return Q;
}


// Checks whether ractangle with sides (a, b) fits into rectangle with sides (c, d)
bool fits( int a, int b, int c, int d ) {
	double X, Y, L, K, DMax;
	if( a < b ) swap( a, b );
	if( c < d ) swap( c, d );
	if( c <= a && d <= b ) return true;
	if( d >= b ) return false;
	X = sqrt( a*a + b*b );
	Y = sqrt( c*c + d*d );
	if( Y < b ) return true;
	if( Y > X ) return false;
	L = ( b - sqrt( Y*Y - a*a) ) /2;
	K = ( a - sqrt( Y*Y - b*b) ) /2;
	DMax = sqrt(L * L + K * K);
	if( d >= DMax ) return false;
return true;
}

//Covex Hull
// compare Function for qsort in convex hull
point Firstpoint;
int cmp(const void *a,const void *b) {
	double xx,yy;
	point aa,bb;
	aa = *(point *)a;
	bb = *(point *)b;
	xx = isleft( Firstpoint, aa, bb );
	if( xx > eps ) return -1;
	else if( xx < -eps ) return 1;
	xx = sq_Distance( Firstpoint, aa );
	yy = sq_Distance( Firstpoint, bb );
	if( xx + eps < yy ) return -1;
	return 1;
}
// 'P' contains all the points, 'C' contains the convex hull
// 'nP' = total points of 'P', 'nC' = total points of 'C'
void ConvexHull( point P[], point C[], int &nP, int &nC ) {
	int i, j, pos = 0; // Remove duplicate points if necesary
	for( i = 1; i < nP; i++ )
		if( P[i].y < P[pos].y || ( eq( P[i].y, P[pos].y ) && P[i].x > P[pos].x + eps ) )
			pos = i;
	swap( P[pos], P[0] );
	Firstpoint = P[0];
	qsort( P + 1, nP - 1, sizeof( point ), cmp );
	C[0] = P[0]; C[1] = P[1];
	i = 2, j = 1;
	while( i < nP ) {
		if( isleft( C[j-1], C[j], P[i] ) > -eps ) C[++j] = P[i++];
		else j--;
	}
	nC = j + 1;
}

