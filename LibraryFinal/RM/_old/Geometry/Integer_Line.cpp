
//Geo_Line
struct Line{
    LL a, b, c;
    Line(){}
    Line(LL x, LL y, LL z){
        a = x;
        b = y;
        c = z;
    }
    Line(pii p1, pii p2) //ax+by+c=0
    {
        *this = Line(p1.yy-p2.yy, p2.xx-p1.xx, -(LL)p1.xx *(p1.yy-p2.yy) + (LL)p1.yy * (p1.xx-p2.xx));
        LL g = __gcd(__gcd(a,b),c);

        assert(g);
        if(a < 0 || (!a && b < 0) || (!(a || b) && c < 0))g = -abs(g);
        else if(g < 0) g = -g;

        a /= g; b /= g; c /= g;
    }
};
