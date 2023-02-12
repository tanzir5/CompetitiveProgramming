#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <queue>
#include <deque>
#include <bitset>
#include <iterator>
#include <list>
#include <stack>
#include <map>
#include <set>
#include <functional>
#include <numeric>
#include <utility>
#include <limits>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include<cctype>
#include<fstream>
#include<set>
#include<sstream>

using namespace std;

#define mem(t, v)           memset ((t) , v, sizeof(t))
#define all(x)              x.begin(),x.end()
#define un(x)               x.erase(unique(all(x)), x.end())
#define sf(n)               scanf("%d", &n)
#define sff(a,b)            scanf("%d %d", &a, &b)
#define sfff(a,b,c)         scanf("%d %d %d", &a, &b, &c)
#define sl(n)               scanf("%lld", &n)
#define sll(a,b)            scanf("%lld %lld", &a, &b)
#define slll(a,b,c)         scanf("%lld %lld %lld", &a, &b, &c)
#define D(x)                cerr << __LINE__ << ": " << #x " = " << (x) << '\n'
#define DD(x, y)            cerr << __LINE__ << ": " << #x " = " << (x) << ", " << #y " = " << (y) << '\n' 
#define DDD(x, y, z)        cerr << __LINE__ << ": " << #x " = " << (x) << ", " << #y " = " << (y) << ", " << #z " = " << (z) << '\n'

#define DBG         cerr << __LINE__ << ": " <<  "Hi" << '\n'
#define PI          acos(-1.00)
#define xx          first
#define yy          second
#define eps         1e-9

typedef long long int LL;
typedef double db;
typedef pair<int,int> pii;
typedef pair<LL,LL> pll;

#define MAX   17

long long fact[20];
long long dp[20][2][20];
long long call(int n, bool k1, int k2)
{
  if(n < 0 or k2 < 0)
    return 0;
  if(k1+k2 == 0)
    return fact[n];
  long long &ret = dp[n][k1][k2];
  if(ret !=-1)
    return ret;
  ret = 0;
  if(k1)
  {
    if(k2)
      ret += k2 * call(n-1, 1, k2-1);
    ret += (n-k2) * call(n-1, 0, k2);
  }
  else
  {  
    ret += (k2-1) * call(n-1, 1, k2-2);
    ret += (n-k2) * call(n-1, 0, k2-1);
  }
  return ret; 
}

int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    fact[0] = 1;
    for(int i = 1; i<=MAX; i++)
      fact[i] = fact[i-1]*i;
    memset(dp, -1, sizeof(dp));
    int t;
    sf(t);
    for(int cs = 1; cs<=t; cs++)
    {
      int bla, n, k;
      sfff(bla, n, k);
      printf("%d %lld\n",bla,call(n,0,k));
    }
    return 0;
}

