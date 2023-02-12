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

#define MAX   10000000

int f[MAX+10];
map<pair<int,int>, int>found;
int solve(int m)
{
  found.clear();
  f[1] = f[2] = 1;
  found[{1, 1}] = 1;
  for(int i = 3; i<=MAX; i++)
  {
    f[i] = f[i-1] + f[i-2];
    if(f[i] >= m)
      f[i] -= m; 
    pii current_pair = {f[i-1], f[i]};
    if(found.find(current_pair) != found.end())
      return i - found[current_pair] - 1;
    found[current_pair] = i;
  }
  return -1;
}

int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    D(pow(2,17)*17*18/1e8);
    int mx = 0;
    for(int m = 2; m<=100; m++)
    {
      if(m%10000 == 0)
        DD(m,mx);
      int ans = solve(m);
      mx = max(mx, ans);
      assert(ans != -1);
      DD(m, ans);
    }
    return 0;
}

