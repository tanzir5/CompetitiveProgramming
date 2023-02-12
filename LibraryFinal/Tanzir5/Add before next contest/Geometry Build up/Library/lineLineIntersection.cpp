inline bool intersection( line L1, line L2, point &p ) {
	double det = L1.a * L2.b - L1.b * L2.a;
	if( eq ( det, 0 ) ) return false;
	p.x = ( L1.b * L2.c - L2.b * L1.c ) / det;
	p.y = ( L1.c * L2.a - L2.c * L1.a ) / det;
	return true;
}
