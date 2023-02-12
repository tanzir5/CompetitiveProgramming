
// Minimizes |X| + |Y|
// Breaks tie with X <= Y
LL exEuclid(LL a, LL b, LL &x, LL &y)
{
    if(b == 0){
        x = 1;
        y = 0;
        return a;
    }

    LL nx, ny, g, r;
    g = exEuclid(b, a % b, nx, ny);
    x = ny;
    y = nx - a / b * ny;

    return g;
}

/*
    x0 -> Initial value
    dx -> Value which is going to be added with x0 in every step

    Returns the minimum number of steps needed to:
        1. make x0 > x
        2. get as close as possible to the value x maintaining the 1st constraint
*/

LL __lower_bound(LL x0, LL dx, LL x)
{
    LL d = x - x0;
    if(d > 0 && d % dx)
    {
        if(dx > 0) return d/dx + 1;
        return d/dx - 1;
    }
    return d/dx;
}

// Ax + By + C = 0
LL number_of_solution(LL A, LL B, LL C, LL x1, LL x2, LL y1, LL y2)
{
    LL g, x0, y0, dx, dy, stp, st1, st2, ed1, ed2, st, ed,x , y;

    if(A && B){
        g = exEuclid(A, B, x0, y0);
        if(C % g) return 0;
        else{
            x0 *= -C/g;
            y0 *= -C/g;
            dx = B/g;
            dy = A/g;

            if(dx < 0) dx *= -1, dy *= -1;

            stp = __lower_bound(x0, dx, -10000000000000LL);
            x0 += dx * stp;
            y0 -= dy * stp;

            st1 = __lower_bound(x0, dx, x1);
            ed1 = __lower_bound(x0, dx, x2 + 1) - 1;

            if(y0 > 0){
                ed2 = __lower_bound(y0, -dy, y1);
                st2 = __lower_bound(y0, -dy, y2 + 1) + 1;
            }
            else{
                st2 = __lower_bound(y0, -dy, y1);
                ed2 = __lower_bound(y0, -dy, y2 + 1) - 1;
            }

            st = max(st1, st2);
            ed = min(ed1, ed2);
            if(st <= ed) return ed - st + 1;
            return 0;
        }
    }
    else if(A){
        // Ax + C = 0
        // x = - C / A
        if( C % A ) return 0;
        else if( x1 <= -C / A && -C / A <= x2) return y2 - y1 + 1;
        else return 0;
    }
    else if(B){
        // By + C = 0
        // y = - C / B
        if(C % B) return 0;
        if( y1 <= -C / B && -C / B <= y2) return x2 - x1 + 1;
        return 0;
    }
    else{
        // C = 0
        if(C) return 0;
        return (x2 - x1 + 1) * (y2 - y1 + 1);
    }
}
