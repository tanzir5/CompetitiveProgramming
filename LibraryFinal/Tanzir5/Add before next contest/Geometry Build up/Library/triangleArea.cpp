double getTriangleArea(point a, point b, point c)
{
    return 0.5 * ( a.x*b.y + b.x * c.y + c.x * a.y - b.x*a.y - c.x*b.y - a.x*c.y);
}
