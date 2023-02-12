
/// num is the number of roots, if num = -1, then there are infinite roots.

struct root{
    int num;
    double sltn[2];
};

/// (-b (+-) sqrt(b^2 - 4ac))/2a
root find_root(LL A, LL B, LL C)
{
    root ret;
    if(A == 0 && B == 0)
    {
        if(C == 0) ret.num = -1;
        else ret.num = 0;
        return ret;
    }
    if(A == 0)
    {
        ret.num = 1;
        ret.sltn[0] = -C/(double)B;
        return ret;
    }
    LL discriminant = B*B - 4*A*C;
    if(discriminant < 0)
    {
        ret.num = 0;
        return ret;
    }

    ret.sltn[0] = (-1.0*B + sqrt(discriminant))/(2*A);
    if(discriminant == 0)
    {
        ret.num = 1;
        return ret;
    }
    ret.num = 2;
    ret.sltn[1] = (-1.0*B - sqrt(discriminant))/(2*A);
    return ret;
}

