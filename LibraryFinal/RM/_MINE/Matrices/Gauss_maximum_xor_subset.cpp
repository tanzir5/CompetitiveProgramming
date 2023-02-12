
#include<bits/stdc++.h>
using namespace std;
#define D(x)    cout << #x " = " << (x) << endl
typedef long long int LL;

const int N = 101;
/*
    COMPLEXITY: min(eqn, var) * eqn * var

    Size of the bitsets HAS TO BE constant.
    So we need to use the max value.

    Code works for signed 64 bit non-negative integer
    MUST CALL CLEAR BEFORE CALLING RESIZE on A
*/

const int INF = numeric_limits<int>::max();

int gauss(vector < bitset < N > > A, vector < bool > &ret, int nVar){

    if(!A.size()) return 1;
    int eqn = A.size();
    int var = nVar, i, j;
    int free_var = 0;
    bool c;
    vector<int> where;
    where.assign(var, -1);


    for(int clm = 0, row = 0; clm < var && row < eqn; clm++){
        if(!A[row][clm])
            for(i = row + 1; i < eqn; i++)
                if(A[i][clm]) {
                    for(j = 0; j <= var; j++)
                    {
                        bool tmp = A[i][j];
                        A[i][j] = A[row][j];
                        A[row][j] = tmp;
                    }
                    break;
                }

        if(!A[row][clm]) {continue;}

        where[clm] = row;
        for(i = 0; i < clm; i++) assert(!A[row][i]);

        for(i = 0; i < eqn; i++)
            if(i == row) continue;
            else{
                /*
                    If the input file consists of multiple test case tweak here
                    As the size of bitset may be a lot bigger, think about looping replacing the xor operation
                */
                c = A[i][clm];
                if(c) A[i] = A[i] ^ A[row];
            }

        row++;
    }

    ret.assign(var, 0);

    for(i = 0; i < var; i++)
        if(where[i] != -1) ret[i] = A[where[i]][var];
        else free_var++;

    for(i = 0; i < eqn; i++){
        bool sum = 0;
        for(j = 0; j < var; j++)
            sum ^= A[i][j] * ret[j];

        if(sum != A[i][var]) return 0;
    }

    if(free_var) return INF;
    return 1;
}

char str[66];
vector < bitset < N > > A;
vector < bool > tmp;

bool can_make(vector<LL> &input, int idx){ // Is it possible to make the prefix from idx to 62?
    A.clear();
    A.resize(62 - idx + 1);

    for(int pos = 62, eqn = 0; pos >= idx; pos--, eqn++){
        for(int i = 0; i < (int) input.size(); i++){
            if(input[i] & (1LL << pos)) A[eqn][i] = true;
        }

        A[eqn][input.size()] = (str[pos] == '1') ? true : false;
    }

    if(!gauss(A, tmp, input.size())) return false;
    return true;
}

LL max_xor_subset(vector <LL> &input)
{
    LL ret = 0;
    memset(str, 0, sizeof(str));
    for(int pos = 62; pos >= 0; pos--){
        str[pos] = '1';
        if(can_make(input, pos) == false) str[pos] = '0';
        else ret += (1LL << pos);
    }

    return ret;
}

int main()
{
    //freopen("in.txt", "r", stdin);

    int i, n, t, cs;
    vector<LL> seq;
    LL v;

    scanf("%d", &t);
    for(cs = 1; cs <= t; cs++)
    {
        seq.clear();

        scanf("%d", &n);
        for(i = 1; i <= n; i++)
        {
            scanf("%lld", &v);
            seq.push_back(v);
        }

        printf("Case %d: %lld\n", cs, max_xor_subset(seq));
    }
    return 0;
}
