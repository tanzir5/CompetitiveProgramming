
//Minimum Enclosing Sphere

struct point3D{
    double x, y, z;
    point3D(){}
    point3D(double xx, double yy, double zz):x(xx),y(yy),z(zz){}
}P[MAX+5];

struct sphere{
    point3D center;
    double r;
    sphere(){}
    sphere(point3D p, double rr):center(p), r(rr){}
};

double abs(double x, double y, double z)
{
    return (x*x+y*y+z*z);
}

sphere minimumEnclosingSphere(point3D arr[], int n) // 1 based indexing
{
    point3D piv = point3D(0,0,0);

    int i, j;
    for(i = 1; i <= n; i++)
    {
        piv.x += arr[i].x;
        piv.y += arr[i].y;
        piv.z += arr[i].z;
    }

    piv.x /= n;
    piv.y /= n;
    piv.z /= n;

    double p = 0.1, e, d;

	for (i = 0; i < 70000; i++) // better to have 50K+
    {
		int f = 0;
		d = numeric_limits<double>::min();
		for (j = 1; j <= n; j++)
		{
			e = abs(piv.x - arr[j].x, piv.y - arr[j].y, piv.z - arr[j].z);
			if (d < e) {
				d = e;
				f = j;
			}
		}

		piv.x += (arr[f].x - piv.x)*p;
		piv.y += (arr[f].y - piv.y)*p;
		piv.z += (arr[f].z - piv.z)*p;
		p *= 0.998;
	}

    return sphere(piv, sqrt(d));
}
