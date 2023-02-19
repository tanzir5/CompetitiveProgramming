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


namespace EE{
/*
    Find the number of integer solutions to the problem:
        Ax + By = C
    x1<=x<=x2 and y1<=y<=y2
    Note:
    1.  Number of points with integer co-ordinates between (x,y) and (_x,_y) is:
        gcd(dx,dy)+1 ( Including both the terminal points )
    2.  Next point of(_x, _y) with integer co-ordinates on the straight line Ax+By=C
        (_x+b/g, _y-a/g).
*/

struct triple{
    LL x, y, g;
};

triple egcd(LL a, LL b)
{
    if(b == 0)
        return {1, 0, a};
    triple tmp = egcd(b, a%b);
    triple ret;
    ret.x = tmp.y;
    ret.y = (tmp.x - (a/b)*tmp.y);
    ret.g = tmp.g;
    return ret;
}

LL myCeil(LL a, LL b)
{
    LL ret = (a/b);
    if((a >= 0 && b>= 0) || (a < 0 && b < 0))
    {
        if(a%b)
            ret++;
    }
    return ret;
}

LL myFloor(LL a, LL b)
{
    LL ret = (a/b);
    if((a > 0 && b < 0) || (a < 0 && b > 0))
    {
        if(a%b)
            ret--;
    }
    return ret;
}

/// x1 <= _x + t*(b/g) <= x2
pll get_range(LL x1, LL x2, LL _x, LL b, LL g)
{
    if((b/g) < 0)
        swap(x1, x2);

    LL low = myCeil(((x1 - _x) * g), b);
    LL high = myFloor(((x2 - _x) * g), b);

    return {low, high};
}

/// ax + by = c
LL solve(LL a, LL b, LL c, LL x1, LL x2, LL y1, LL y2)
{
    triple sltn = egcd(a,b);
    LL ret;

    if(a == 0 && b == 0)
    {
        if(c == 0) ret = (x2 - x1 + 1) * (y2 - y1 + 1);
        else ret = 0;
    }
    else if(a == 0)
    {
        if(c%b) ret = 0;
        else
        {
            LL y = (c/b);
            if(y1 <= y && y <= y2)
                ret = (x2 - x1 + 1);
            else
                ret = 0;
        }
    }
    else if(b == 0)
    {
        if(c%a) ret = 0;
        else
        {
            LL x = (c/a);
            if(x1 <= x && x <= x2)
                ret = (y2 - y1 + 1);
            else
                ret = 0;
        }
    }
    else
    {
        if(c%sltn.g) ret = 0;
        else
        {
            sltn.x *= (c/sltn.g);
            sltn.y *= (c/sltn.g);
            pll rangeX = get_range(x1,x2,sltn.x,b,sltn.g);
            pll rangeY = get_range(y1,y2,sltn.y,-a,sltn.g);
            pll range;
            range = {max(rangeX.xx, rangeY.xx), min(rangeX.yy, rangeY.yy)};
            ret = range.yy - range.xx + 1;
            ret = max(0LL, ret);
        }
    }
    return ret;
}
}

int r, s, n;
LL A[60], B[60], train[110];
LL a_total = 0, b_total = 0;

int ee_done[2000010];
bool diophontine(LL a, LL b, LL c)
{
  if (ee_done[c] != -1)
    return ee_done[c];

  LL x1, x2, y1, y2;
  x1 = y1 = 0;
  if(a == 0)
    x2 = 0;
  else
    x2 = (c/a)+1;
  if(b == 0)
    y2 = 0;
  else
    y2 = (c/b)+1;
  LL ways = EE::solve(a, b, c, x1, x2, y1, y2);
  //DDD(a,b,c);
  //D(ways);
  bool result = (ways > 0);
  ee_done[c] = result;
  return result;
}

inline int add(int a, int b, int mod){
  a += b;
  if(a >= mod)
    a -= mod;
  return a;
}
int dp[110][60][60];
bool call(int t_idx, int a_idx, int b_idx)
{
  if(t_idx == n)
    return true;
  auto &ret = dp[t_idx][a_idx][b_idx];
  if(ret != -1)
    return ret;
  ret = false;
  LL a_things = 0;
  int cur_a_idx = a_idx, nxt_a_idx = a_idx;
  for(int i = 0; i<=r; i++){
    int cur_b_idx = b_idx, nxt_b_idx = b_idx;
    LL b_things = 0;
    if(i != 0){
      a_things += A[cur_a_idx];
      nxt_a_idx = add(cur_a_idx, 1, r);
      if(a_things > train[t_idx])
        break;
    }
    for(int j = 0; j<=s; j++){
      if(j != 0){
        b_things += B[cur_b_idx];
        nxt_b_idx = add(cur_b_idx, 1, s);
        if((a_things + b_things) > train[t_idx])
          break;
      }
      
      LL rem = train[t_idx] - (a_things + b_things);
      if (diophontine(a_total, b_total, rem))
        ret |= call(t_idx+1, nxt_a_idx, nxt_b_idx);
        if(ret)
          break;
      if(j != 0){
        cur_b_idx = add(cur_b_idx, 1, s);
      }
    }
    if(ret)
      break;
    if(i != 0)
      cur_a_idx = add(cur_a_idx, 1, r);
  }
  //DDD(t_idx, a_idx, b_idx);
  //D(ret);
  return ret;
}

int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    //D(diophontine(0, 1, 1));
    //exit(0);
    mem(dp, -1);
    mem(ee_done, -1);
    sfff(r, s, n);
    for(int i = 0; i<r; i++){
      sl(A[i]);
      a_total += A[i];
    }
    for(int i = 0; i<s; i++){
      sl(B[i]);
      b_total += B[i];
    }
    for(int i = 0; i<n; i++)
      sl(train[i]);
    bool is_possible = call(0,0,0);
    if(is_possible)
      puts("Yes");
    else
      puts("No");
    return 0;
}

