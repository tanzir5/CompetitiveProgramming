
#include<bits/stdc++.h>
using namespace std;
#define D(x)    cout << #x " = " << (x) << endl
#define MAX     100000
#define xx      first
#define yy      second


#define MAXLG	16
#define MAXN	20000
#define BLACK	0
#define WHITE	1
#define dt		first
#define indx	second
typedef pair<int, int> pii;

namespace std{
    pii operator + (const pii &u, const pii &v) {return pii(u.xx + v.xx, u.yy + v.yy);}
    pii operator - (const pii &u, const pii &v) {return pii(u.xx - v.xx, u.yy - v.yy);}
}

const int inf = 1000000000;
int allowed_cost;

struct curve{
    set < pii > S;

    curve(){S.insert({0, 0});}

    bool BRE(pii u, pii v){
        assert(u.xx <= v.xx);
        return u.yy >= v.yy;
    }

    void insert(pii point){
        auto itr = S.upper_bound( pii(point.xx, inf) );
        if(itr == S.begin()) S.insert(point);
        else{
            itr--;
            if(BRE(*itr, point)) return;
            if(itr->xx == point.xx) S.erase(itr);
            S.insert(point);
        }

        while(true){
            itr = S.upper_bound(point);
            if(itr == S.end()) break;
            if(BRE(point, *itr)) S.erase(itr);
            else break;
        }
    }

    int query(int qx){
        pii point = pii(qx, inf);
        auto itr = S.upper_bound(point);
        if(itr == S.begin()){ /// No solution
            assert(false);
        }
        itr--;
        return itr->second;
    }

    void clear(){S.clear();}
};

///1 Based Indexing
struct centroid_tree{
	int par[MAXN+3], depth[MAXN+3], subsize[MAXN+3];
	vector<int> child[MAXN+3], edge[MAXN+3];
	vector< pii > cost[MAXN+3];
	bool vis[MAXN+3];
	pii tab[MAXLG+3][MAXN+3];

    void dfs1(int idx, int dr, bool updateFlag, curve &C, int &ret){
        if(updateFlag) C.insert(tab[dr][idx]);
        else{
            int rm = (allowed_cost - tab[dr][idx].xx);
            if(rm >= 0) ret = max(ret, tab[dr][idx].yy + C.query(rm));
        }

        for(auto x : child[idx])
            dfs1(x, dr, updateFlag, C, ret);
    }

	void dfs0(int idx, int &r, int p = -1){
		subsize[idx] = 1;
		for(auto x : edge[idx]){
			if(x == p) continue;
			if(vis[x]){
				if(r == -1) r = x;
				else if(depth[x] > depth[r]) r = x;
				continue;
			}
			dfs0(x, r, idx);
			subsize[idx] += subsize[x];
		}
	}

	void find(int idx, int &c, int n, int p = -1){
		int mx = 0;
		for(auto x : edge[idx]){
			if(x == p){
				mx = max(mx, n - subsize[idx]);
				continue;
			}
			else if(vis[x]) continue;
			mx = max(mx, subsize[x]);
			find(x, c, n, idx);
		}

		if(mx <= n/2) c = idx;
	}

	void preprocess(int idx, int r, pii d = {0, 0}, int p = -1){
		tab[depth[r]][idx] = d;
		int i, v;
		pii w;
		for(i = 0; i < (int) edge[idx].size(); i++){
			v = edge[idx][i];
			w = cost[idx][i];

			if(v == p) continue;
			if(vis[v]) continue;
			preprocess(v, r, d + w, idx);
		}
	}

	void build(int n){
		int iter = 1;

		while(iter <= n){
			if(vis[iter]) iter++;
			else{
				int r = -1, c = -1;
				dfs0(iter, r);
				find(iter, c, subsize[iter]);

				assert(c != -1);
				if(r != -1) {
					child[r].push_back(c);
					depth[c] = depth[r] + 1;
				}
				else depth[c] = 0;

				par[c] = r;
				vis[c] = true;
				preprocess(c, c);
			}
		}
	}


	int query(int idx){
        int mx = 0;
        curve C = curve();

        for(auto x : child[idx]){
            dfs1(x, depth[idx], false, C, mx);
            dfs1(x, depth[idx], true, C, mx);
        }

        C.clear();
        return mx;
	}

	void clear(int n){
        for(int i = 1; i <= n; i++){
            edge[i].clear();
            cost[i].clear();
        }
        memset(vis, 0, sizeof(vis));
	}
} ctree;


int main(){
//    freopen("rm.txt", "r", stdin);
    int i, t, n, u, v, a, b;

    scanf("%d", &t);

    while(t--){
        ctree = centroid_tree();

        scanf("%d", &n);
        for(i = 1; i < n; i++){
            scanf("%d %d %d %d", &u, &v, &a, &b);
            ctree.edge[u].push_back(v);
            ctree.edge[v].push_back(u);

            ctree.cost[u].push_back({a, b});
            ctree.cost[v].push_back({a, b});
        }

        scanf("%d", &allowed_cost);
        ctree.build(n);

        int mx = 0;
        for(i = 1; i <= n; i++)
            mx = max(mx, ctree.query(i));

        printf("%d\n", mx);
        ctree.clear(n);
    }
    return 0;
}
