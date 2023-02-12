#include<bits/stdc++.h>
using namespace std;
#define D(x)        cout << #x " = " << (x) << endl
#define MAX         100000
#define MAXVAL      ((1<<16) - 1)
typedef long long int LL;
const double PI = acos(-1.0);

#define MAXN (1 << 17)
namespace fft{
    int len, last = -1, step = 0, rev[MAXN];
    long long C[MAXN], D[MAXN], P[MAXN], Q[MAXN];

	struct complx{
        double real, img;
        inline complx() { real = img = 0.0; }
        inline complx conjugate() { return complx(real, -img); }
        inline complx(long double x) { real = x, img = 0.0; }
        inline complx(long double x, long double y) { real = x, img = y; }
        inline complx operator + (complx other) { return complx(real + other.real, img + other.img); }
        inline complx operator - (complx other) { return complx(real - other.real, img - other.img); }
        inline complx operator * (complx other) {
            return complx((real * other.real) - (img * other.img), (real * other.img) + (img * other.real));
        }
    } u[MAXN], v[MAXN], f[MAXN], g[MAXN], dp[MAXN], inv[MAXN];

    /// Pre-process roots, inverse roots and fft leaf index
    void build(int& a, long long* A, int& b, long long* B){
        while (a > 1 && A[a - 1] == 0) a--;
        while (b > 1 && B[b - 1] == 0) b--;

	    len = 1 << (32 - __builtin_clz(a + b) - (__builtin_popcount(a + b) == 1));
        for (int i = a; i < len; i++) A[i] = 0;
        for (int i = b; i < len; i++) B[i] = 0;

		if (!step++) {
            dp[1] = inv[1] = complx(1);
            for (int i = 1; (1 << i) < MAXN; i++){
                double theta = (2.0 * acos(0.0)) / (1 << i);
                complx mul = complx(cos(theta), sin(theta));
                complx inv_mul = complx(cos(-theta), sin(-theta));

                int lim = 1 << i;
                for (int j = lim >> 1; j < lim; j++){
                    dp[2 * j] = dp[j], inv[2 * j] = inv[j];
                    inv[2 * j + 1] = inv[j] * inv_mul;
                    dp[2 * j + 1] = dp[j] * mul;
                }
            }
        }

        if (last != len) {
            last = len;
            int bit = (32 - __builtin_clz(len) - (__builtin_popcount(len) == 1));
            for (int i = 0; i < len; i++) rev[i] = (rev[i >> 1] >> 1) + ((i & 1) << (bit - 1));
        }
	}

    /// Fast Fourier Transformation, iterative divide and conquer
	void transform(complx *in, complx *out, complx* ar){
	    for (int i = 0; i < len; i++) out[i] = in[rev[i]];
	    for (int k = 1; k < len; k <<= 1){
            for (int i = 0; i < len; i += (k << 1)){
                for (int j = 0; j < k; j++){
                    complx z = out[i + j + k] * ar[j + k];
                    out[i + j + k] = out[i + j] - z;
                    out[i + j] = out[i + j] + z;
                }
            }
	    }
	}

    /// Multiplies two polynomials A and B and return the coefficients of their product in A
    /// Function returns degree of the polynomial A * B
	int multiply(int a, long long* A, int b, long long* B){
		build(a, A, b, B);
		for (int i = 0; i < len; i++) u[i] = complx(A[i], B[i]);
		transform(u, f, dp);
		for (int i = 0; i < len; i++){
            int j = (len - 1) & (len - i);
            u[i] = (f[j] * f[j] - f[i].conjugate() * f[i].conjugate()) * complx(0, -0.25 / len);
		}
		transform(u, f, dp);
		for (int i = 0; i < len; i++) A[i] = f[i].real + 0.5;
		return a + b - 1;
	}
}

long long P1[MAXN], P2[MAXN];
void multiply(const int a[], const int b[], LL res[]){
    for(int i = 0; i <= MAXVAL; i++) P1[i] = a[i];
    for(int i = 0; i <= MAXVAL; i++) P2[i] = b[i];
    int d = fft::multiply(MAXVAL + 1, P1, MAXVAL + 1, P2);
    for(int i = 0; i < d; i++) res[i] = P1[i];

}

const int buk = 2000;
int arr[MAX+5];
LL counter;

int sufx[MAX+5], prfx[MAX+5];
int inbucket[MAX+5];

inline void forget(int freq[], int st, int ed){
    int i;
    for(i = st; i <= ed; i++) freq[arr[i]]--;
}

inline void ack(int freq[], int st, int ed){
    int i;
    for(i = st; i <= ed; i++) freq[arr[i]]++;
}

LL M[MAXVAL * 2 + 5];

LL brute(int n){
    LL ret = 0;
    int i, j, k;
    for(i = 1; i <= n; i++)
        for(j = i + 1; j <= n; j++)
            for(k = j + 1; k <= n; k++)
                if(arr[i] + arr[j] == arr[k])
                    ret++;

    return ret;
}

int main()
{
//    freopen("rm.txt", "r", stdin);

    int t, i, n;
    scanf("%d", &t);

    while(t--){
        counter = 0;

        scanf("%d", &n);
        for(i = 1; i <= n; i++) scanf("%d", &arr[i]);
        ack(sufx, 1, n);

        /// case = 1 -> O( N / BUK  * V LOG V )
        for(int b = 1; ; b++){
            int st = (b - 1) * buk + 1;
            if(st > n) break;
            int ed = min(n, st + buk - 1);

            forget(sufx, st, ed);
            ack(inbucket, st, ed);

            if(b != 1 && ed != n)
            {
                memset(M, 0, sizeof(M));
                multiply(prfx, inbucket, M);

                for(i = 0; i <= MAXVAL ; i++)
                    counter += M[i] * sufx[i];
            }

            forget(inbucket, st, ed);
            ack(prfx, st, ed);
        }
        forget(prfx, 1, n);

        /// case = 3 -> O( N * BUK )
        for(int b = 1; ; b++){
            int st = (b - 1) * buk + 1;
            if(st > n) break;
            int ed = min(n, st + buk - 1);

            for(int mid = ed; mid >= st; mid--){
                for(int l = st; l < mid; l++){
                    if(arr[l] + arr[mid] > MAXVAL) continue;
                    counter += inbucket[arr[l] + arr[mid]];
                }
                ack(inbucket, mid, mid);
            }
            forget(inbucket, st, ed);
        }


        /// case = 2 -> O( N * BUK )
        for(int b = 1; ; b++){
            int st = (b - 1) * buk + 1;
            if(st > n) break;
            int ed = min(n, st + buk - 1);

            for(int mid = st; mid <= ed; mid++)
                for(int r = mid + 1; r <= ed; r++)
                    if(arr[r] < arr[mid]) continue;
                    else counter += prfx[arr[r] - arr[mid]];
            ack(prfx, st, ed);
        }
        forget(prfx, 1, n);

        ack(sufx, 1, n);
        for(int b = 1; ; b++){
            int st = (b - 1) * buk + 1;
            if(st > n) break;
            int ed = min(n, st + buk - 1);
            forget(sufx, st, ed);

            for(int mid = st; mid <= ed; mid++)
                for(int l = st; l < mid; l++)
                    if(arr[mid] + arr[l] > MAXVAL) continue;
                    else counter += sufx[arr[l] + arr[mid]];
        }

        cout << counter << endl;
//        assert(counter == brute(n));
    }
    return 0;
}
