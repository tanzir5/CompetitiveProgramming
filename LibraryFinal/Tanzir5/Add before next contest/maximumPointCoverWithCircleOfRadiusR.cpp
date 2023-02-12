/// solves problem C Phone Cells from here http://codeforces.com/gym/101095/attachments
/// code by DU_Resonance
struct point{
    int x, y;
};
point P[MAX+10];

LL sqdist(point a, point b)
{
    return (LL)(a.x - b.x) * (a.x - b.x) + (LL)(a.y - b.y) * (a.y - b.y);
}

bool invalid(int i,int j,double r)
{
    if( i == j ) return true;
    if( sqdist(P[ i ],P[ j ]) > eps + double (4*r*r) ) return true;
    return false;
}
double get_angle(point a, point b)
{
    if( a.x == b.x && b.y > a.y ) return PI/2;
    if( a.x == b.x && b.y < a.y ) return 3*PI/2;
    if( a.y == b.y && b.x > a.x ) return 0;
    if( a.y == b.y && b.x < a.x ) return PI;

    int dy = b.y - a.y, dx = b.x - a.x;
    return atan2((double)dy,(double)dx);
}
typedef pair <double, int> nd;
typedef pair <nd, int> node;
node V[ MAX*2+10 ];
bool bhitre( point a, point b, int r )
{
    LL s = sqdist(a,b);
    if( s <= (LL)r * r ) return true;
    return false;
}

int main()
{
//    freopen("in.txt", "r", stdin);
    int n, i, j, k, r, x, y;
    while( scanf("%d %d",&n,&r) != EOF && (n+r) )
    {
        for(int i = 0; i<n; i++) scanf("%d %d",&P[i].x, &P[i].y );
        int res = 0, cnt;
        for(int i = 0; i<n; i++)
        {
            k = 0, cnt = 0;
            for(int j = 0; j<n; j++)
            {
                if( invalid(i,j,r) ) continue;
                double ds = sqrt( sqdist(P[ i ],P[ j ]) );
                double ang = get_angle(P[ i ], P[ j ] );
                double ang1 = ang - acos(ds / ( 2.*(double)r ) ) - eps/10;
                double ang2 = ang + acos(ds / ( 2.*(double)r ) ) + eps/10;

                while( ang1 < 0 ) ang1 += 2*PI;
                while( ang1 >= 2*PI ) ang1 -= 2*PI;
                while( ang2 < 0 ) ang2 += 2*PI;
                while( ang2 >= 2*PI ) ang2 -= 2*PI;

                V[ k ++ ] = node( nd(ang1,-1), j);
                V[ k ++ ] = node( nd(ang2,1), j);
            }
            int cnt = 0;
            bool flag[ 2010 ] = { 0 };
            for(int j = 0; j<n; j++)
            {
                if( bhitre(  {P[ i ].x + r, P[ i ].y}, P[ j ], r ) )
                    cnt --, flag[ j ] = 1;
            }
            sort(V, V + k );
            int sz = k;
            if( -cnt > res ) res = -cnt;
            for(j = 0; j < sz; j ++ )
            {
                /// the following two are sanity checks. They should never happen and code gets ac with asserting false for them.
                if( flag[ V[ j ].second ] && V[ j ].first.second == -1) ;
                //bhitre ase and ekhon abar dhukaite chai, ignore
                else if( !flag[ V[ j ].second ] && V[ j ].first.second == 1) ;
                //bhitre nai and ekhon abar ber korte chai, ignore
                else cnt += V[ j ].first.second;								// normal
                if( V[ j ].first.second == 1) flag[ V[ j ].second ] = 0;
                // bair korle bhitre ase er flagag off
                if( V[ j ].first.second == -1) flag[ V[ j ].second ] = 1;
                // dhukaile bhitre ase er flagag on
                if( -cnt > res ) res = -cnt;
            }
        }
        printf("It is possible to cover %d points.\n",res);
    }
    return 0;
}



