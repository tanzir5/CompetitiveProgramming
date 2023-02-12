
//Circle Rectangle Intersection
double areaArc( double r, double x1, double y1 )
{
    double x2 = sqrt( r*r - y1*y1 );
    double y2 = sqrt( r*r - x1*x1 );
    double theta = acos( ( 2*r*r - (x2-x1)*(x2-x1) - (y2-y1)*(y2-y1) ) / ( 2*r*r ) );
    return (theta*r*r - y1 * (x2 - x1) - x1 * (y2 - y1)) / 2;
}

double circleRectangleIntersection( int r, int x1, int y1, int x2, int y2 )
{
    if( x1 < 0 && x2 > 0 ) return circleRectangleIntersection( r, 0, y1, x2, y2 ) + circleRectangleIntersection( r, x1, y1, 0, y2 );
    if( y1 < 0 && y2 > 0 ) return circleRectangleIntersection( r, x1, 0, x2, y2 ) + circleRectangleIntersection( r, x1, y1, x2, 0 );
    if( x1 < 0 ) return circleRectangleIntersection( r, -x2, y1, -x1, y2 );
    if( y1 < 0 ) return circleRectangleIntersection( r, x1, -y2, x2, -y1 );
    if( x1 >= r || y1 >= r ) return 0.0;
    if( x2 > r ) return circleRectangleIntersection( r, x1, y1, r, y2 );
    if( y2 > r ) return circleRectangleIntersection( r, x1, y1, x2, r );
    if( x1*x1 + y1*y1 >= r*r ) return 0.0;
    if( x2*x2 + y2*y2 <= r*r ) return (x2 - x1) * (y2 - y1);
    int outCode = ( x2*x2 + y1*y1 >= r*r ) + 2 * ( x1*x1 + y2*y2 >= r*r );

    if( outCode == 3 ) return areaArc( r, x1, y1 );
    else if( outCode == 1 )
    {
        double x = sqrt( r*r - y2*y2 + 0.0 );
        return (x - x1) * (y2 - y1) + areaArc( r, x, y1 );
    }
    else if( outCode == 2 )
    {
        double y = sqrt( r*r - x2*x2 + 0.0 );
        return (x2 - x1) * (y - y1) + areaArc( r, x1, y );
    }
    else
    {
        double x = sqrt( r*r - y2*y2 + 0.0 );
        double y = sqrt( r*r - x2*x2 + 0.0 );
        return (x2 - x1) * (y - y1) + (x - x1) * (y2 - y) + areaArc( r, x, y );
    }
}

const double pi = 2 * acos(0.0);

int cases, caseno;

struct circle
{
    int x, y, r;
};

double circleRectangleIntersection( circle C, int x1, int y1, int x2, int y2 )
{
    return circleRectangleIntersection( C.r, x1 - C.x, y1 - C.y, x2 - C.x, y2 - C.y );
}
