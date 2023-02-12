double areaFromMedians(double a, double b, double c)
{
    a *= 2.0/3.0;
    b *= 2.0/3.0;
    c *= 2.0/3.0;
    double s = (a+b+c)/2.00;
    double area = s*(s-a)*(s-b)*(s-c);
    if(area <= 0)
        return -1;
    area = sqrt(area);
    area *= 3;
    return area;
}
