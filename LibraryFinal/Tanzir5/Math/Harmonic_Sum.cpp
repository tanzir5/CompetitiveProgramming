/// Error is in the region of 2e-12 for values greater than 1000.
/// Run for loop for less than 1000.
const double Gamma = 0.5772156649;
double Hn(LL n)
{
     double r = 0;
     r = log(n) + Gamma + .5/n - (1/(12.0 * n*n));
     return r;
}
