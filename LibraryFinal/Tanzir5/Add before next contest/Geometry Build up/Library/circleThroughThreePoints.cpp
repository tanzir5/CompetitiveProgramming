circle CircleThrough3points( point A, point B, point C)
{
    double den;
    circle c;
    den = 2.0 *((B.x-A.x)*(C.y-A.y) - (B.y-A.y)*(C.x-A.x));
    c.center.x =( (C.y-A.y)*(B.x*B.x+B.y*B.y-A.x*A.x-A.y*A.y) –
                  (B.y-A.y)*(C.x*C.x+C.y*C.y-A.x*A.x-A.y*A.y) );
    c.center.x /= den;
    c.center.y =( (B.x-A.x)*(C.x*C.x+C.y*C.y-A.x*A.x-A.y*A.y) –
                  (C.x-A.x)*(B.x*B.x+B.y*B.y-A.x*A.x-A.y*A.y) );
    c.center.y /= den;
    c.r = Distance( c.center, A );
    return c;
}


