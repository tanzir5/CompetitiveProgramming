

///NTT - By Zahin Vai

#define SGT_MAX 65536 /// 2 * MAX at least
typedef complex <double> complx; /// Replace double with long double if more precision is required

namespace fft{
    int len, last = -1, step = 0, rev[SGT_MAX];
    long long C[SGT_MAX], D[SGT_MAX], P[SGT_MAX], Q[SGT_MAX], tA[SGT_MAX], tB[SGT_MAX];
	complx u[SGT_MAX], v[SGT_MAX], f[SGT_MAX], g[SGT_MAX], dp[SGT_MAX], inv[SGT_MAX];

	inline complx conj(complx x){
        return {x.real(), -x.imag()};
    }

    inline long long round_half_even(long double x){
        long long res = abs(x) + 0.5;
        if (x < 0) res = -res;
        return res;
    }

    /// Pre-process roots, inverse roots and fft leaf index
    void build(int& a, long long* A, int& b, long long* B){
        while (a > 1 && A[a - 1] == 0) a--;
        while (b > 1 && B[b - 1] == 0) b--;

	    len = 1 << (32 - __builtin_clz(a + b) - (__builtin_popcount(a + b) == 1));
        for (int i = a; i < len; i++) A[i] = 0;
        for (int i = b; i < len; i++) B[i] = 0;

		if (!step++){
            dp[1] = inv[1] = complx(1);
            for (int i = 1; (1 << i) < SGT_MAX; i++){
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

        if (last != len){
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

    /// Modular multiplication
	int mod_multiply(int a, long long* A, int b, long long* B, int mod){
	    build(a, A, b, B);
	    for (int i = 0; i < len; i++) A[i] %= mod, B[i] %= mod;
	    for (int i = 0; i < len; i++) u[i] = complx(A[i] & 32767, A[i] >> 15);
	    for (int i = 0; i < len; i++) v[i] = complx(B[i] & 32767, B[i] >> 15);

		transform(u, f, dp);
		for (int i = 0; i < len; i++) g[i] = f[i];
		transform(v, g, dp);

		for (int i = 0; i < len; i++){
            int j = (len - 1) & (len - i);
            complx c1 = conj(f[j]), c2 = conj(g[j]);

            complx a1 = (f[i] + c1) * complx(0.5, 0);
			complx a2 = (f[i] - c1) * complx(0, -0.5);
			complx b1 = (g[i] + c2) * complx(0.5 / len, 0);
			complx b2 = (g[i] - c2) * complx(0, -0.5 / len);
			v[j] = a1 * b2 + a2 * b1;
			u[j] = a1 * b1 + a2 * b2 * complx(0, 1);
		}
		transform(u, f, dp);
		transform(v, g, dp);

        long long x, y, z;
		for (int i = 0; i < len; i++){
            x = f[i].real() + 0.5, y = g[i].real() + 0.5, z = f[i].imag() + 0.5;
            A[i] = (x + ((y % mod) << 15) + ((z % mod) << 30)) % mod;
		}
		return a + b - 1;
	}

	void multiply(vector<int> &a, vector <int> &b, vector<int> &res, int mod){
        int sA = a.size();
        for(int i = 0; i < sA; i++) tA[i] = a[i];

        int sB = b.size();
        for(int i = 0; i < sB; i++) tB[i] = b[i];
        int degree = mod_multiply(sA, tA, sB, tB, mod);

        res.resize(degree);
        for(int i = 0; i < degree; i++) res[i] = tA[i];
        while(!res.back()) res.pop_back();
	}
}
