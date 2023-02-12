// Dynamic Convex Hull
struct point{
    LL x, y;
    point(){}
    point(int xx, int yy){
        x = xx;
        y = yy;
    }
};

bool operator < (const point &u, const point &v){
    if(u.x == v.x) return u.y < v.y;
    return u.x < v.x;
}

LL signedArea(point a, point b, point c)
{
    LL ret = (LL) a.x* (b.y - c.y) + (LL) b.x*(c.y - a.y) + (LL) c.x*(a.y - b.y);
    if(ret < 0) return -1;
    if(ret > 0) return +1;
    return 0;
}

LL triArea(point a, point b, point c) { return abs((LL) a.x* (b.y - c.y) + (LL) b.x*(c.y - a.y) + (LL) c.x*(a.y - b.y)); }

struct Dynamic_Convex_Hull{

    deque< point > hull;
    int n;
    LL Area;

    Dynamic_Convex_Hull(){
        Area = 0;
        n = 0;
        hull.clear();
    }

    bool brute(point p)
    {
        if(n < 3){
            n++;
            hull.push_back(p);
            if(n == 3 && signedArea(hull[0], hull[1], hull[2]) < 0) swap(hull[0], hull[1]);
            if(n == 3) Area = triArea(hull[0], hull[1], hull[2]);
            return true;
        }
        return false;
    }

    void addPoint(point p)
    {
        while(true){
            if(brute(p)) return;
            if(signedArea(p, hull.back(), hull[hull.size() - 2]) > 0){
                hull.push_front(hull.back());
                hull.pop_back();
            }
            else  break;
        } //Went down to the lower Tangent


        point previous = hull.back();
        while(true){
            if(brute(p)) return;
            if(signedArea(p, hull[0], hull[1]) < 0)
            {
                Area += triArea(p, hull[0], previous);
                previous = hull.front();
                n--, hull.pop_front();
            }
            else break;
        }
        Area += triArea(p, hull[0], previous);

        n++;
        hull.push_back(p);
    }
}solver;
