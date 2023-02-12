
#include<bits/stdc++.h>
using namespace std;
#define D(x)    cout << #x " = " << (x) << endl
#define MAX     100000
#define MOD     663224321
typedef long long int LL;

inline int add(int u, int v){
    int ret = u + v;
    if(ret >= MOD) ret -= MOD;
    return ret;
}

inline int mul(LL u, LL v) {return (u * v) % MOD;}

///Number Theoretic Transformation
const int mod = 663224321;
const int root_pw = 1<<19;          /// mod = c * 2^k + 1 => root_pw = 2^k
const int root = 1489;                /// set it equal to get_root
const int root_1 = 296201594;          /// set it to ip(root, mod - 2)


LL ip(LL a, LL p){
    if(!p) return 1;
    if(p & 1) return ( a * ip(a, p - 1)) % mod;
    LL ret = ip(a, p/2);
    return (ret * ret) % mod;
}

int get_root(){
    int r, q;
    for(r = 2; r < mod; r++){
        if(ip(r, root_pw) == 1){
            for(q = 1; q < root_pw; q++)
                if(ip(r, q) == 1) break;

            if(q == root_pw) return r;
        }
    }
    return -1;
}

void fft (vector<int> & a, bool invert) {
	int n = (int) a.size();

	for (int i=1, j=0; i<n; ++i) {
		int bit = n >> 1;
		for (; j>=bit; bit>>=1)
			j -= bit;
		j += bit;
		if (i < j)
			swap (a[i], a[j]);
	}

	for (int len=2; len<=n; len<<=1) {
		int wlen = invert ? root_1 : root;
		for (int i=len; i<root_pw; i<<=1)
			wlen = int (wlen * 1ll * wlen % mod);
		for (int i=0; i<n; i+=len) {
			int w = 1;
			for (int j=0; j<len/2; ++j) {
				int u = a[i+j],  v = int (a[i+j+len/2] * 1ll * w % mod);
				a[i+j] = u+v < mod ? u+v : u+v-mod;
				a[i+j+len/2] = u-v >= 0 ? u-v : u-v+mod;
				w = int (w * 1ll * wlen % mod);
			}
		}
	}
	if (invert) {
		int nrev = ip(n, mod - 2);
		for (int i=0; i<n; ++i)
			a[i] = int (a[i] * 1ll * nrev % mod);
	}
}

void multiply (const vector<int> & a, const vector<int> & b, vector<int> & res) {
	vector<int> fa (a.begin(), a.end()),  fb (b.begin(), b.end());
	size_t n = 1;
	while (n < max (a.size(), b.size()))  n <<= 1;
	n <<= 1;
	fa.resize (n),  fb.resize (n);

	fft (fa, false),  fft (fb, false);
	for (size_t i=0; i<n; ++i)
		fa[i] = ((LL) fa[i] * fb[i]) % mod;
	fft (fa, true);

	res.resize (n);
	for (size_t i=0; i<n; ++i)
		res[i] = fa[i];
}


/*
    G is known
    F is yet to know
*/

vector<int> A, B, C;
vector<int> F, G;
void convolve(int l1, int r1, int l2, int r2){
    A.clear(); B.clear();

    int i;
    for(i = l1; i <= r1; i++) A.push_back(F[i]);
    for(i = l2; i <= r2; i++) B.push_back(G[i]);
    multiply(A, B, C);
    for(i = 0; i < (int) C.size(); i++)
        if(l1 + l2 + 1 > 2) /// Not touching the base case
            F[l1 + l2 + i] = add(F[l1 + l2 + i], C[i]);
}

/*
    1 BASED INDEXING
    SHIFT THE POLYNOMIALS TO WORK IT FOR 0-BASED CASES
    DO NOT TRY TO CHANGE THE CODE

    n = Smallest power of 2 greater or equal to N
*/
void online_FFT(int n){
    int i;
    assert(G.size() >= 2 * n);
    assert(F.size() >= 2 * n);

    for(i = 1; i < n; i++){
        ///We have computed till F_i correctly and now want to add it's contribution
        if(i + 1 > 2) F[i + 1] = add(F[i + 1], mul(F[i] , G[1])); /// Not touching the base cases
        if(i + 2 > 2) F[i + 2] = add(F[i + 2], mul(F[i] , G[2])); /// Not touching the base cases

        for(int pw = 2; i % pw == 0 && pw + 1 <= n; pw = pw * 2)
            convolve(i - pw, i - 1, pw + 1, min(2 * pw, n));
    }
}

int S(int n){
    if(n == 0) return 1;
    return ip(n, n - 1);
}

int H(int n){
    if(n <= 1) return 1;

    int ret = 0;
    for(int r = 1; r <= n; r++)
        ret = add( ret, mul( S(r - 1) , H(n - r) ));

    return ret;
}

int main()
{
    int n = 2, i;
    while(n <= MAX) n = n * 2;
    G.resize(2 * n);
    F.resize(2 * n);

    for(i = 0; i + 1 < n; i++){
        if(!i) G[i + 1] = 1;
        else G[i + 1] = S(i);
    }
    F[1] = 1, F[2] = 1;
    online_FFT(n);

    int t;
    scanf("%d", &t);
    while(t--){
        scanf("%d", &i);
        printf("%d\n", F[i + 1]);
//        D(H(i));
    }
    return 0;
}
