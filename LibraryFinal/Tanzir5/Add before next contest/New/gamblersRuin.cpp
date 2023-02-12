
/// you are at co-ordinate x on a line with integer co-ordinates only
/// In one move, you have to go to (x+1) or (x-1). You cannot stay at x.
/// p is the probability of moving to (x+1) from x
/// (1-p) is the probability of moving to (x-1) from x
/// if you reach a or b you cannot move anymore.
/// MUST: a <= st <= b, a != b,  0 < p < 1
/// randomWalk returns the probability of ending at b if you start from st.
long double randomWalk(long double p, int a, int b, int st)
{
    if(isEq(p,0.5))
        return (st-a)/(long double)(b-a);
    assert(0 < p && p < 1);
    if(st == a)
        return 0;
    if(st == b)
        return 1;

    long double q = 1-p;
    long double c = q/p;
    long double up, down, ret;
    if(c > 1)
    {
        up = pow(c, st-b)-1;
        down = pow(c, a-b)-1;
        ret = 1 - (up/down);
    }
    else
    {
        up = pow(c, st-a)-1;
        down = pow(c, b-a) - 1;
        ret = (up/down);
    }
    return ret;
}

long double randomWalkExpLen(long double p, int a, int b, int st)
{
    if(isEq(p,0.5))
        return ((long double)(st-a)) * (b-st);
    long double win = randomWalk(p, a, b, st);
    long double ret = (win*(b-st) + (1-win) * (a-h))/(p-q);
    return ret;
}
