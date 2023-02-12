
#include<bits/stdc++.h>
using namespace std;
#define D(x)        cout << #x " = " << (x) << endl
#define MOD         1000000007
#define MAX         1000000
typedef long long int LL;

int fact[2*MAX+5];
int inv[2*MAX+5];

int add(int u, int v){
    int ret = u + v;
    if(ret >= MOD) ret -= MOD;
    return ret;
}

int sub(int u, int v){
    int ret = u - v;
    if(ret < 0) ret += MOD;
    return ret;
}

int mul(LL u, LL v){return (u * v) % MOD;}

int ip(int a, int p){
    if(!p) return 1;
    if(p & 1) return mul(a, ip(a, p - 1));
    int ret = ip(a, p/2);
    return mul(ret, ret);
}

int nCr(int n, int r){
    if( r > n ) return 0;
    if(n == r || r == 0) return 1;

    int ret = fact[n];
    ret = mul(ret, inv[r]);
    ret = mul(ret, inv[n - r]);
    return ret;
}

void init(){ // Don't forget to call me
    fact[0] = inv[0] = 1;
    for(int i = 1; i <= MAX * 2; i++){
        fact[i] = mul(i, fact[i - 1]);
        inv[i] = ip(fact[i], MOD - 2);
    }
}

/*
    #number of ways to place
        - "ttl" number of things
        - into "slot places
    #Every place may contain any non-negative number of things
*/
int ways(int slot, int ttl){
    assert(slot > 0);
    return nCr(ttl + slot - 1, ttl);
}

/*
    #number of ways to place
        - "ttl" number of things
        - into "slot" places
        - where every place has a capacity equal to "limit"

    #Every place may contain any non-negative number of things
*/
int ways(int slot, int ttl, int limit){
    int ret = ways(slot, ttl);

    for(int invalid = 1; invalid <= slot; invalid++){
        LL rem = ttl - (LL) invalid * (limit + 1);
        if(rem < 0) break;

        if(invalid & 1) ret = sub(ret, mul(nCr(slot, invalid), ways(slot, rem)));
        else ret = add(ret, mul(nCr(slot, invalid), ways(slot, rem)));
    }
    return ret;
}

int main()
{
    init();

    int R, W, D;
    scanf("%d %d %d", &R, &W, &D);
    printf("%d\n", ways(W + 1, R, D));

    return 0;
}
