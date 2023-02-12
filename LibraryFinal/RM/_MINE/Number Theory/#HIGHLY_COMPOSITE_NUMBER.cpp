
#include<bits/stdc++.h>
using namespace std;
#define D(x)        cout << #x " = " << (x) << endl
typedef long long int LL;

int arr[33];
LL n;
LL mxDv, mnAns;

void backTrack(int pos, int prv, LL mul, LL cnt)
{
    if(pos > 12){
        if(cnt > mxDv){
            mxDv = cnt;
            mnAns = mul;
        }
        else if(cnt == mxDv){
            mnAns = min(mnAns, mul);
        }
        return;
    }

    if( mul > n / arr[pos]) return backTrack(pos + 1, 0, mul, cnt);
    backTrack(pos + 1, 0, mul, cnt);

    LL curr = 1;
    for(int i = 1; i <= prv; i++)
    {
        if(curr > n / arr[pos]) break;
        curr = curr * arr[pos];

        if(mul > n / curr) break;
        backTrack(pos + 1, i, mul * curr, cnt * (i + 1));
    }

}

void solve(){
    if(n == 1) puts("1 1");
    else{
        mxDv = 0;
        mnAns = numeric_limits<LL>::max();
        backTrack(1, 70, 1, 1);
        printf("%lld %lld\n", mnAns, mxDv);
    }
}

int main()
{
    //freopen("in.txt", "r", stdin);

    int i, j, idx = 0, t;
    for(i = 2; idx < 12; i++)
    {
        for(j = 2; j < i; j++)
            if(i % j == 0) break;
        if(j == i) arr[++idx] = i;
    }

    scanf("%d", &t);
    while(t--)
    {
        scanf("%lld", &n);
        solve();
    }
    return 0;
}
