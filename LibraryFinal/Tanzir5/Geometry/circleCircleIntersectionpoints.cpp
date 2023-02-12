/// p1 and p2 are the points where the circles intersect.
/// Returns 0 if no intersection, inf if the circles are same, 1 if one, 2 if two intersections

int circle_circle_intersection(circle A, circle B, point *p1, point *p2)
{
    double x0, y0, r0, x1, y1, r1;
    double xi, yi, xi_prime,yi_prime;
    x0 = A.center.x;
    y0 = A.center.y;
    r0 = A.r;

    x1 = B.center.x;
    y1 = B.center.y;
    r1 = B.r;

    if((fabs(x0 -x1) < eps && fabs(y0 - y1) < eps && fabs(r0 - r1) < eps) )
        return inf;

    double a, dx, dy, d, h, rx, ry;
    double x2, y2;

    dx = x1 - x0;
    dy = y1 - y0;


    d = hypot(dx,dy);

    if (d > (r0 + r1))  return 0;

    if (d < fabs(r0 - r1))  return 0;

    a = ((r0*r0) - (r1*r1) + (d*d)) / (2.0 * d) ;

    x2 = x0 + (dx * a/d);
    y2 = y0 + (dy * a/d);

    h = sqrt((r0*r0) - (a*a));

    rx = -dy * (h/d);
    ry = dx * (h/d);

    p1->x = x2 + rx;
    p2->x = x2 - rx;
    p1->y = y2 + ry;
    p2->y = y2 - ry;

    if(fabs(p1->x - p2->x) < eps && fabs(p1->y - p2->y) < eps)
        return 1;

    return 2;
}

