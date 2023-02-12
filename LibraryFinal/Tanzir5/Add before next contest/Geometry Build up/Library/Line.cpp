struct line{
    LL a, b, c;
    line(point p1, point p2)
    {
        a = (p1.y - p2.y);
        b = -(p1.x - p2.x);
        c = (p1.x - p2.x)*p1.y - (p1.y - p2.y)*p1.x;
    }
    LL eval(point p)
    {
        return a*p.x + b*p.y + c;
    }
};
