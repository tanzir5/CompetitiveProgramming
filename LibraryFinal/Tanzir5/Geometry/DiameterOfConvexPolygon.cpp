
double find_diameter(vector<point>&A)
{
    sort(all(A));
    un(A);
    if(A.size() == 1)
        return 0;
    else if(A.size() == 2)
        return dist_point_point(A[0], A[1]);

    vector<point> hull;
    convex_hull(A, hull);
    int n = hull.size();

    int idx = 1;
    line nw = line(hull.back(),hull[0]);
    double mx = -inf;
    int i = 1;
    while(true)
    {
        double dist = dist_point_line(hull[i], nw);
        if(dist > mx)
            mx = dist, idx = i, i++;
        else
            break;
    }

    double ans = 0;
    for(i = 0; i<hull.size(); i++)
    {
        if(i == n-1)
            nw = line(hull[i], hull[0]);
        else
            nw = line(hull[i], hull[i+1]);

        double mx = -inf;
        for(int j = idx; ;j++)
        {
            if(j == n) j = 0;
            double dist = dist_point_line(hull[j], nw);
            if(dist > mx)
                mx = dist, idx = j, ans = max(ans, dist_point_point(hull[i], hull[j]));
            else
                break;
        }
    }
    return ans;
}
