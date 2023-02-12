
//Tangent of two Circles
const double eps = 1e-10;
const double pi = acos(-1);

int dcmp(double x){
    return fabs(x) < eps ? 0 : (x > 0 ? 1 : -1);
}

struct Point{
    double x;
    double y;
    Point(double x = 0, double y = 0):x(x), y(y){}

    bool operator < (const Point& e) const{
        return dcmp(x - e.x) < 0 || (dcmp(x - e.x) == 0 && dcmp(y - e.y) < 0);
    }
    int read(){
        return scanf("%lf%lf", &x, &y);
    }
}p[3];

typedef Point Vector;

Vector operator + (Point A, Point B)    { return Vector(A.x + B.x, A.y + B.y);}
Vector operator - (Point A, Point B)    { return Vector(A.x - B.x, A.y - B.y);}
Vector operator * (Point A, double p)   { return Vector(A.x * p, A.y * p);}
Vector operator / (Point A, double p)   { return Vector(A.x / p, A.y / p);}
double Dot(Vector A, Vector B)          { return A.x * B.x + A.y * B.y;}
double Cross(Vector A, Vector B)        { return A.x * B.y - B.x * A.y;}
double Length(Vector A)                 { return sqrt(Dot(A, A));}

struct Circle{
    double x, y;
    double r;
    Circle(double x = 0, double y = 0, double r = 0):x(x), y(y), r(r){}

    int read(){
        return scanf("%lf%lf%lf", &x, &y, &r);
    }
    Point point(double a){
        return Point(x + r * cos(a), y + r * sin(a));
    }
    double getmax(){return max(max(x,y),r); }
};
//returns -1 when infinite number of tangents
int getTangents(Circle A, Circle B, Point *a, Point *b)
{
    int cnt = 0;
    if(dcmp(A.r - B.r) < 0){
        swap(A, B);
        swap(a, b);
    }
    double d = sqrt((A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y));
    double rdiff = A.r - B.r;
    double rsum = A.r + B.r;
    if(dcmp(d - rdiff) < 0) return 0;
    double base = atan2(B.y - A.y, B.x - A.x);
    if(dcmp(d) == 0) return -1;
    if(dcmp(d - rdiff) == 0)
    {
        a[cnt] = b[cnt] = A.point(base);
        cnt++;
        return 1;
    }
    double ang = acos((A.r - B.r) / d);
    a[cnt] = A.point(base + ang); b[cnt] = B.point(base + ang); cnt++;
    a[cnt] = A.point(base - ang); b[cnt] = B.point(base - ang); cnt++;
    if(dcmp(d - rsum) == 0)
    {
        a[cnt] = b[cnt] = A.point(base);
        cnt++;
    }
    else if(dcmp(d - rsum) > 0)
    {
        double ang = acos((A.r + B.r) / d);
        a[cnt] = A.point(base + ang); b[cnt] = B.point(pi + base + ang); cnt++;
        a[cnt] = A.point(base - ang); b[cnt] = B.point(pi + base - ang); cnt++;
    }
    return cnt;
}
