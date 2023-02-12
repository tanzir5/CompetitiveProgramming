typedef complex<long double> Complex;
long double PI = 2 * acos(0.0L);
// Decimation-in-time radix-2 FFT.
//
// Computes in-place the following transform:
// y[i] = A(w^(dir*i)),
// where
// w = exp(2pi/N) is N-th complex principal root of unity,
// A(x) = a[0] + a[1] x + ... + a[n-1] x^{n-1},
// dir \in {-1, 1} is FFT's direction (+1=forward, -1=inverse).
// Sizes of arrays should be 4 times the maximum degree
Complex A[MAX*4+10], B[MAX*4+10], C[MAX*4+10];
int it;
void fft(Complex *a, int N, int dir)
{
    int lgN;
    for (lgN = 1; (1 << lgN) < N; lgN++);
    assert((1 << lgN) == N);
    for (int i = 0; i < N; i++)
    {
        it++;
        int j = 0;
        for (int k = 0; k < lgN; k++)
            j |= ((i>>k)&1) << (lgN-1-k),it++;
        if (i < j) swap(a[i], a[j]);
    }
    for (int s = 1; s <= lgN; s++)
    {
        it++;
        int h = 1 << (s - 1);
        Complex t, w, w_m = exp(Complex(0, dir*PI/h));
        for (int k = 0; k < N; k += h+h)
        {
            it++;
            w = 1;
            for (int j = 0; j < h; j++)
            {
                it++;
                t = w * a[k+j+h];
                a[k+j+h] = a[k+j] - t;
                a[k+j] += t;
                if (dir == -1)
                    a[k+j+h] /= 2,  a[k+j] /= 2;
                w *= w_m;
            }
        }
    }
}

void multiply(Complex *a, Complex *b, Complex *c, int n)
{
    int nw = 1;
    for(; nw<n; nw<<=1);
    n = nw;
    for(int i = n; i<n*2; i++)
        a[i] = 0, b[i] = 0;
    n*=2;
    fft(a,n,1);
    fft(b,n,1);
    for(int i = 0; i<n; i++)
        c[i] = a[i] * b[i];
    fft(c,n,-1);
}
