
// Template Credit: dragoon

#define z_slice_eps 1e-5
#define SIMPSON_EPS 1e-9
#define SIMPSON_TERMINAL_EPS 1e-12

double F(double x) {
    return x;
}

double single_simpson(double miny, double maxy) {
    return (maxy - miny) / 6 * (F(miny) + 4 * F((miny + maxy) / 2.) + F(maxy));
}

double adaptive_simpson(double miny, double maxy, double c, double eps = SIMPSON_EPS) {
    if(maxy - miny < SIMPSON_TERMINAL_EPS) return 0;

    double midy = (miny + maxy) / 2;
    double a = single_simpson(miny, midy);
    double b = single_simpson(midy, maxy);

    if(fabs(a + b - c) < 15 * eps) return a + b + (a + b - c) / 15.0;

    return adaptive_simpson(miny, midy, a, eps / 2.) + adaptive_simpson(midy, maxy, b, eps / 2.);
}

double simpson(double minz, double maxz)
{
    double ans, last, z, temp;

    ans = 0;
    last = F(minz);
    for(z = minz; z<=maxz; z+=z_slice_eps)
    {
        if(z>(minz+maxz)/2)
            z = z;

        temp = F(z+z_slice_eps);
        ans += last + 4*F(z+z_slice_eps/2) + temp;
        last = temp;
    }

    ans *= z_slice_eps/6;

    return ans;
}

double Integrate(double x_st, double x_ed) { return adaptive_simpson(x_st, x_ed, single_simpson(x_st, x_ed));}
