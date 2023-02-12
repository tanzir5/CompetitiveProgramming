#include<bits/stdc++.h>
using namespace std;
#define D(x)        cout << #x " = " << (x) << endl
#define MAX         1000002
#define MOD         1000000007
typedef long long int LL;

LL ip(LL a, int p)
{
    if(a < 0) return ip(a + MOD, p);

    if(!p) return 1;
    if(p & 1) return (a * ip(a, p - 1)) % MOD;
    LL ret = ip(a, p/2);
    return (ret * ret) % MOD;
}

inline LL sub(LL u, LL v){
    LL ret = (u - v);
    if(ret < 0) ret += MOD;
    return ret;
}

inline LL add(LL u, LL v){
    LL ret = (u + v);
    if(abs(ret) >= MOD) ret %= MOD;
    return ret < 0 ? ret + MOD : ret;
}

inline LL mul(LL u, LL v){
    LL ret = (u * v);
    if(abs(ret) >= MOD) ret %= MOD;
    return ret < 0 ? ret + MOD : ret;
}

LL sum[MAX+5];

int main()
{
    //freopen("rm.txt", "r", stdin);

    int n, k, i;

    scanf("%d %d", &n, &k);
    for(i = 1; i <= k + 2; i++)
        sum[i] = (sum[i - 1] + ip(i, k)) % MOD;


    if(n <= k + 2){
        cout << sum[n] << endl;
        return 0;
    }

    LL term = sum[1], result;
    for(i = 2; i <= k + 2; i++)
        term = mul(term, mul(n - i, ip(1 - i, MOD - 2)));

    result = term;
    for(i = 1; i < k + 2; i++)
    {
        term = mul(term, sub(n , i));
        LL dwn = mul( sub(n , add(i , 1)) , i);

        dwn = mul(dwn , sum[i]);
        term = mul(term, ip(dwn, MOD - 2));
        term = mul(term, i - (k + 2));
        term = mul(term, sum[i + 1]);
        result = add(result,term);
    }

    cout << result << endl;
    return 0;
}
