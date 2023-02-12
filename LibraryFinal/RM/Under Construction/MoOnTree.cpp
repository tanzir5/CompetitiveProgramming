
///MO's On Tree
[ smallest missing edge on the path (u, v) ]

#include<bits/stdc++.h>
using namespace std;
#define D(x)    cout << #x " = " << (x) << endl
#define MAX     200000 /// MUST BE AT LEAST 2 * N

vector<int> edge[MAX+5];
vector<int> cost[MAX+5];
int edge_cost[MAX+5];
int disc[MAX+5], fin[MAX+5], rep[MAX+5];
int __tm;

//Sparse Table
#define MAXLG   17
int Tab[MAXLG+2][MAX+2], par[MAX+2], lev[MAX+2], stp; // par->parent, lev = level;

void init_st(int n)
{
    int idx;

    for(idx = 1; idx <= n; idx++)
        Tab[0][idx] = par[idx];

    for(stp = 1; (1 << stp) < n; stp++)
        for(idx = 1; idx <= n; idx++)
            if(Tab[stp-1][idx] == -1) Tab[stp][idx] = -1;
            else Tab[stp][idx] = Tab[stp-1][Tab[stp-1][idx]];
    stp--;
}

int go(int cur, int gap, int pos)
{
    if(!gap) return cur;
    if(gap&1) return go(Tab[pos][cur], gap/2, pos+1);
    return go(cur, gap/2, pos+1);
}

int LCA(int u, int v)
{
    if(lev[u] > lev[v]) swap(u,v);
    v = go(v, lev[v]-lev[u], 0);
    if(u == v) return v;

    int i;
    for(i = stp; i >= 0; i--)
        if(Tab[i][u] != Tab[i][v])
            u = Tab[i][u], v = Tab[i][v];

    assert(Tab[0][u] > 0);
    return Tab[0][u];
}


void dfs(int idx, int p, int ec, int dpt){
    par[idx] = p;
    edge_cost[idx] = ec;
    lev[idx] = dpt;
    disc[idx] = ++__tm;
    rep[__tm] = idx;

    for(int i = 0; i < (int) edge[idx].size(); i++){
        int x = edge[idx][i];
        int w = cost[idx][i];
        if(x == p) continue;

        dfs(x, idx, w, dpt + 1);
    }

    fin[idx] = ++__tm;
    rep[__tm] = idx;
}


const int BUK = 317;

struct query{
    int l, r, m, idx;
};

vector<query> Q;
bool operator < (const query &u, const query &v){
    if(u.l/BUK == v.l/BUK) return u.r < v.r;
    return u.l < v.l;
}

/*
    solution starts
*/

#define NOT_COUNTED         0
#define COUNTED             1

int mex[MAX+5];
int state[MAX+5];

int freq[MAX+5];
int segFreq[MAX+5];
int cur_L = 0, cur_R = 0;

void __insert(int ec){
    if(ec == -1) return; ///root is orphan :(
    freq[ec]++;
    if(freq[ec] == 1) segFreq[ ec/BUK ]++;
}

void __erase(int ec){
    if(ec == -1) return; ///root is orphan :(
    if(freq[ec] == 1) segFreq[ ec/BUK ]--;
    freq[ec]--;
}

void change(int idx){
    if(!idx) return;

    if(state[idx] == NOT_COUNTED) __insert(edge_cost[idx]);
    else __erase(edge_cost[idx]);
    state[idx] = 1 - state[idx];
}

void solve(){
    int i;
    for(i = 0; i < (int) Q.size(); i++){
        int l = Q[i].l;
        int r = Q[i].r;
        int m = Q[i].m;

        while(cur_L > l){
            cur_L--;
            change(rep[cur_L]);
        }
        while(cur_R < r){
            cur_R++;
            change(rep[cur_R]);
        }

        while(cur_L < l){
            change(rep[cur_L]);
            cur_L++;
        }

        while(cur_R > r){
            change(rep[cur_R]);
            cur_R--;
        }

        ///should LCA be counted? If not then change.
        bool flip = false;
        if(state[m] == COUNTED) {
            change(m);
            flip = true;
        }

        for(int b = 0; ; b++){
            int st = b * BUK;
            int ed = st + BUK - 1;
            if(segFreq[b] < (ed - st + 1)){
                for(int j = st; j <= ed; j++){
                    if(!freq[j]){
                        mex[Q[i].idx] = j;
                        break;
                    }
                }
                break;
            }
        }

        if(flip) change(m);
    }
}

void __clear(int n){
    Q.clear();
    __tm = 0;
    for(int i = 1; i <= n; i++) edge[i].clear();
    for(int i = 1; i <= n; i++) cost[i].clear();
    memset(freq, 0, sizeof(freq));
    memset(segFreq, 0, sizeof(segFreq));
    memset(state, 0, sizeof(state));
    cur_L = 0, cur_R = 0;
}

/*
    solution ends
*/

int main(){
//    freopen("in.txt", "r", stdin);

    int i, n, t, u, v, w;
    query q;

    scanf("%d %d", &n, &t);
    for(i = 1; i < n; i++){
        scanf("%d %d %d", &u, &v, &w);
        if(w > MAX) w = MAX;

        edge[u].push_back(v);
        edge[v].push_back(u);

        cost[u].push_back(w);
        cost[v].push_back(w);
    }

    dfs(1, -1, -1, 0);
    init_st(n);

    for(i = 1; i <= t; i++){
        scanf("%d %d", &u, &v);
        if(disc[u] > disc[v]) swap(u, v);

        if(LCA(u, v) == u){
            q.l = disc[u];
            q.r = disc[v];
            q.m = u;
        }
        else{
            q.l = fin[u];
            q.r = disc[v];
            q.m = LCA(u, v);
        }
        q.idx = i;
        Q.push_back(q);
    }

    sort(Q.begin(), Q.end());
    solve();

    for(i = 1; i <= t; i++)
        printf("%d\n", mex[i]);

    __clear(n);
    return 0;
}
