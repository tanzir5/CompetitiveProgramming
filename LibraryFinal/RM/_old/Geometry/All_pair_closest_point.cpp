
#include<bits/stdc++.h>
using namespace std;
#define D(x)        cout<<#x " = "<<(x)<<endl
#define un(x)       x.erase(unique(x.begin(),x.end()), x.end())
#define sf(n)       scanf("%d", &n)
#define sff(a,b)    scanf("%d %d", &a, &b)
#define sfff(a,b,c) scanf("%d %d %d", &a, &b, &c)
#define pb          push_back
#define mp          make_pair
#define xx          first
#define yy          second
#define hp          (LL) 999983
#define MAX         100005
#define eps         1e-9
#define pi          acos(-1.00)
typedef long long int LL;
typedef pair<int,int> pii;
typedef vector<pii> vpii;

template<class T> void checkmin(T &a,T b){if(b<a) a=b;}
template<class T> void checkmax(T &a,T b){if(b>a) a=b;}

const int maxn = 100005;
int tx[maxn];
int ty[maxn];
bool divX[maxn];
pii key[maxn];

bool cmpX(const pii &a, const pii &b) {
	return a.first < b.first;
}

bool cmpY(const pii &a, const pii &b) {
	return a.second < b.second;
}

void buildTree(int left, int right, pii points[]) {
	if (left >= right)
		return;
	int mid = (left + right) >> 1;

	//sort(points + left, points + right + 1, divX ? cmpX : cmpY);
	int minx = INT_MAX;
	int maxx = INT_MIN;
	int miny = INT_MAX;
	int maxy = INT_MIN;
	for (int i = left; i < right; i++) {
		checkmin(minx, points[i].first);
		checkmax(maxx, points[i].first);
		checkmin(miny, points[i].second);
		checkmax(maxy, points[i].second);
	}
	divX[mid] = (maxx - minx) >= (maxy - miny);
	nth_element(points + left, points + mid, points + right, divX[mid] ? cmpX : cmpY);

	tx[mid] = points[mid].first;
	ty[mid] = points[mid].second;

	if (left + 1 == right)
		return;
	buildTree(left, mid, points);
	buildTree(mid + 1, right, points);
}

long long closestDist;
int closestNode;

void findNearestNeighbour(int left, int right, int x, int y) {
	if (left >= right)
		return;
	int mid = (left + right) >> 1;
	int dx = x - tx[mid];
	int dy = y - ty[mid];
	long long d = dx * (long long) dx + dy * (long long) dy;
	if (closestDist > d && d) {
		closestDist = d;
		closestNode = mid;
	}
	if (left + 1 == right)
		return;

	int delta = divX[mid] ? dx : dy;
	long long delta2 = delta * (long long) delta;
	int l1 = left;
	int r1 = mid;
	int l2 = mid + 1;
	int r2 = right;
	if (delta > 0)
		swap(l1, l2), swap(r1, r2);

	findNearestNeighbour(l1, r1, x, y);
	if (delta2 < closestDist)
		findNearestNeighbour(l2, r2, x, y);
}

void buildTree(int n, pii points[])
{
    for(int i = 0; i < n; i++)
        key[i] = points[i];

    buildTree(0, n, key);
}

int findNearestNeighbour(int n, int x, int y) {
	closestDist = LLONG_MAX;
	findNearestNeighbour(0, n, x, y);
	return closestNode;
}

pii pnt[MAX+5];

int main()
{
    //freopen("in.txt", "r", stdin);

    int i, j, k, t, cs;
    int n;

    scanf("%d", &t);
    while(t--)
    {
        scanf("%d", &n);
        for(i = 0; i < n; i++)
            scanf("%d %d", &pnt[i].xx, &pnt[i].yy);

        buildTree(n, pnt);
        for(i = 0; i < n; i++)
        {
            findNearestNeighbour(n, pnt[i].xx, pnt[i].yy);
            printf("%lld\n", closestDist);
        }
    }

    return 0;
}
