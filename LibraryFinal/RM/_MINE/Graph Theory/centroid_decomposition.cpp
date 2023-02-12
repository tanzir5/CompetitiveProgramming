

#define MAXLG	18
#define MAXN	100000
#define BLACK	0
#define WHITE	1
#define dt		first
#define indx	second
typedef pair<int, int> pii;

///1 Based Indexing
struct centroid_tree{
	int tab[MAXLG+3][MAXN+3], par[MAXN+3], depth[MAXN+3], subsize[MAXN+3], clr[MAXN+3];
	vector<int> child[MAXN+3], edge[MAXN+3], cost[MAXN+3];
	bool vis[MAXN+3];
	set < pii > available[MAXN+3];


	void dfs(int idx, int &r, int p = -1){
		subsize[idx] = 1;
		for(auto x : edge[idx]){
			if(x == p) continue;
			if(vis[x]){
				if(r == -1) r = x;
				else if(depth[x] > depth[r]) r = x;
				continue;
			}
			dfs(x, r, idx);
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

	void preprocess(int idx, int r, int d = 0, int p = -1){
		tab[depth[r]][idx] = d;
		int i, v, w;
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
				dfs(iter, r);
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


	void toggle(int idx){
		if(clr[idx] == BLACK){
			int c = idx;
			do{
				available[c].insert(pii(tab[depth[c]][idx], idx));
				c = par[c];
			}while(c != -1);
		}
		else{
			int c = idx;
			do{
				available[c].erase(pii(tab[depth[c]][idx], idx));
				c = par[c];
			}while(c != -1);
		}
		clr[idx] = 1 - clr[idx];
	}

	int query(int idx){
		if(clr[idx] == WHITE) return 0;
		int ret = numeric_limits<int>::max();

		int c = idx;
		do{
			if(available[c].size())  ret = min(ret, (*available[c].begin()).dt + tab[depth[c]][idx]);
			c = par[c];
		}while(c != -1);

		if(ret == numeric_limits<int>::max()) return -1;
		return ret;
	}

} ctree;


