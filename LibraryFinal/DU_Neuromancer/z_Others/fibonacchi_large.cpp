
///Fibonacci_large
#define MOD 1000000007
map<LL, LL> Fib;
void init(){Fib[0] = Fib[1] = 1;}
LL f(LL n)  //will return (n-1)th Fibonacci number
{
    if(n == -1) return 0;
	if (Fib.count(n)) return Fib[n];
	long k=n/2;
	if (!(n&1)) return Fib[n] = (f(k)*f(k) + f(k-1)*f(k-1)) % MOD;
	else return Fib[n] = (f(k)*f(k+1) + f(k-1)*f(k)) % MOD;
}
