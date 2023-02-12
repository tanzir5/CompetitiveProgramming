
///Closest Pair
struct point{
    int x, y;
};

double Distance(point a, point b){return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));}

point p[MAX+11], s1[MAX+11], s2[MAX+11];
bool sortX(point a, point b) {return ( fabs(a.x-b.x) < eps ) ? a.y + eps < b.y : a.x + eps < b.x;}
bool sortY(point a, point b) {return ( fabs(a.y-b.y) < eps ) ? a.x + eps < b.x : a.y + eps < b.y;}

double closestPair( int k1, int k2, point &p1, point &p2)
{
	double d, d2 ,d3;
	point p3, p4;

	if(k2-k1+1 == 1) {p1 = p2 = p[k1]; return 0;}
	if(k2-k1+1 == 2) {p1 = p[k1], p2 = p[k2]; return Distance(p[k1], p[k2]);}
	if(k2-k1+1 == 3) {
		d  = Distance( p[k1], p[k1+1] );
		d2 = Distance( p[k1+1], p[k1+2]);
		d3 = Distance( p[k1+2], p[k1]);

		if(d + eps < min(d2, d3)) p1 = p[k1], p2 = p[k1+1];
		else if(d2 + eps < min(d,d3)) p1 = p[k1+1], p2 = p[k1+2];
		else p1 = p[k1+2], p2 = p[k1];
		return min( min(d, d2), d3 );
	}
	int k, i, j, ns1, ns2;
	k = (k1 + k2) / 2;
	d  = closestPair(k1 , k, p1, p2);
	d2 = closestPair(k+1 , k2, p3, p4);
	if(d > d2 + eps)	p1 = p3, p2 = p4, d = d2;
	ns1 = ns2 = 0;
	for(i = k; i>=k1 ; i--) {
		if( p[k].x - p[i].x  >  d + eps) break;
		s1[ ns1++ ] = p[i];
	}
	sort(s1, s1+ns1, sortY);
	for(i = k+1; i<=k2 ; i++) {
		if( p[i].x - p[k].x  >  d + eps) break;
		s2[ ns2++ ] = p[i];
	}
	sort(s2, s2+ns2, sortY);
	for(i=0;i<ns1;i++) {
		for(j=0;j<ns2;j++) {
			if(s2[j].y - s1[i].y > d + eps) break;
			if(d > Distance(s1[i], s2[j]) + eps)
            {
                d = Distance( s1[i], s2[j] );
                p1 = s1[i];
                p2 = s2[j];
            }
		}
	}
	return d;
}


//sort( p, p+n, sortX );
//closestPair(0,n-1);
