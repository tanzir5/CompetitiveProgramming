
//3_point_orientation
LL triArea2(pii a, pii b, pii c) // includes sign
{
    LL ret = 0;
    ret += (LL) a.xx*b.yy + (LL) b.xx*c.yy + (LL) c.xx*a.yy - (LL) a.xx*c.yy - (LL) c.xx*b.yy - (LL) b.xx*a.yy;
    return ret;
}


//Angle between 3 points + Dot product
double ang(pii L, pii mid, pii R)
{
    double dot = (LL) (L.xx - mid.xx) * (R.xx - mid.xx) + (LL) (L.yy - mid.yy) * (R.yy - mid.yy);
    dot /= sqrt((L.xx - mid.xx) * (L.xx - mid.xx) + (L.yy - mid.yy) * (L.yy - mid.yy));
    dot /= sqrt((R.xx - mid.xx) * (R.xx - mid.xx) + (R.yy - mid.yy) * (R.yy - mid.yy));
    return acos(dot);
}


//height of trapezium_from_sides
double tri_area(double a,double b,double c)
{
    double s=(a+b+c)/2;
    return sqrt(s*(s-a)*(s-b)*(s-c));
}
double height_of_trapezium_from_sides(double a,double b, double c, double d)
{
    double h;
    if(a<c) swap(a,c);
    h=2*tri_area(a,b,d)/(a-c);
    return h;
}
