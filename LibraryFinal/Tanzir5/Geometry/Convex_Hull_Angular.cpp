Convex Hull (Graham Scan) O(nlogn):
// compare Function for qsort in convex hull
point Firstpoint;
int cmp(const void *a,const void *b) {
	double x,y;
	point aa,bb;
	aa = *(point *)a;
	bb = *(point *)b;
	x = isleft( Firstpoint, aa, bb );
	if( x > eps ) return -1;
	else if( x < -eps ) return 1;
	x = sq_Distance( Firstpoint, aa );
	y = sq_Distance( Firstpoint, bb );
	if( x + eps < y ) return -1;
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

