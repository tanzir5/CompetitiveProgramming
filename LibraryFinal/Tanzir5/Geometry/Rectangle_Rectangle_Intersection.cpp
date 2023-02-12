struct rectangle{
    point LB, RT;
    rectangle(){};
    rectangle(point a, point b)
    {
        LB = a;
        RT = b;
    }
    int area()
    {
        return (RT.x - LB.x) * (RT.y - LB.y);
    }
};

int rect_rect_intersection(rectangle Q, rectangle W)
{
    point LB, RT;
    LB.x = max(Q.LB.x,W.LB.x);
    LB.y = max(Q.LB.y,W.LB.y);
    RT.x = min(Q.RT.x,W.RT.x);
    RT.y = min(Q.RT.y,W.RT.y);

    if(LB.x >= RT.x || LB.y >= RT.y)
        return 0;
    return (RT.x - LB.x) * (RT.y - LB.y);
}
