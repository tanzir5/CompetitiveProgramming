
///Number Theoretic Transformation
const int mod = 7340033;
const int root = 71;                /// set it equal to get_root
const int root_1 = 413523;          /// set it to ip(root, mod - 2)
const int root_pw = 1<<20;          /// mod = c * 2^k + 1 => root_pw = 2^k

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
