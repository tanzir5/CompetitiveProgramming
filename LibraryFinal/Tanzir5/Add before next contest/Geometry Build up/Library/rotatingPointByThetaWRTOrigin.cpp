/// rotates anticlockwise
inline point rotate2D( double theta, point P ) {
	point Q;
	Q.x = P.x * cos( theta ) - P.y * sin( theta );
	Q.y = P.x * sin( theta ) + P.y * cos( theta );
	return Q;
}

