#include<bits/stdc++.h>
using namespace std;
#define D(x)	cout << #x " = " << (x) << endl
#define MAX 	1000000

#define ALPHABET_SIZE	26

struct aho_corasick{

	vector< int > visit;
	vector < vector < int > > f_tree;
	vector < int > patMark;
	vector < int > ocr;
	vector < int > dp;

	struct trie{
		int fail, idx;
		vector<int> endCounter;
		trie *nxt[ALPHABET_SIZE];
		int fail_nxt[ALPHABET_SIZE];

		trie(int _idx){
			fail = 0;
			idx = _idx;
			memset(nxt, 0, sizeof(nxt));
			memset(fail_nxt, -1,sizeof(fail_nxt));
		}
	};

	vector< trie * > node;

	aho_corasick(){
		node.push_back(new trie(0));
		visit.push_back(0);
		f_tree.push_back(vector<int>());
		dp.push_back(-1);
	}

	int rank(char ch){return ch - 'a';}

	void insert(char *pat, int number){ ///NUMBERS MUST START FROM 0 AND INCREASE BY 1
		trie *cur = node[0];
		for(int i = 0; pat[i]; i++){
			int v = rank(pat[i]);
			if(!cur->nxt[v]){
				cur->nxt[v] = new trie(node.size());
				node.push_back(cur->nxt[v]);
				visit.push_back(0);
				f_tree.push_back(vector<int>());
				dp.push_back(-1);
			}
			cur = cur->nxt[v];
		}
		cur->endCounter.push_back(number);
		patMark.push_back(cur->idx);
		ocr.push_back(0);
	}

	void build(){
		int i;
		queue<trie *> Q;

		for(i = 0; i < ALPHABET_SIZE; i++)
			if(node[0] -> nxt[i]){
				trie *p = node[0] -> nxt[i];
				p -> fail = 0;
				f_tree[0].push_back(p->idx);
				Q.push(p);
			}

		while(!Q.empty()){
			trie *u = Q.front(); Q.pop();
			for(i = 0; i < (int) ALPHABET_SIZE; i++){
				if(u -> nxt[i]){
					int f = u -> idx;
					trie *v = u -> nxt[i];

					while(true){
						f = node[f] -> fail;
						if(node[f] -> nxt[i]) {
							v -> fail = node[f] -> nxt[i] -> idx;
							break;
						}
						else if(!f) break;
					}

					f_tree[v -> fail].push_back( v -> idx);
					Q.push(u->nxt[i]);
				}
			}
		}
	}

	vector<int> nodeList;
	int dfs(int idx){
		if(dp[idx] != -1) return dp[idx];
		nodeList.push_back(idx);

		int ret = visit[idx];

		for(int i = 0; i < (int) f_tree[idx].size(); i++)
			ret += dfs(f_tree[idx][i]);

		return dp[idx] = ret;

	}

	inline int transition(int idx, int v){
        if(node[idx] -> fail_nxt[v] != -1) return node[idx] -> fail_nxt[v];
        if(node[idx] -> nxt[v]) return node[idx] -> fail_nxt[v] = node[idx] -> nxt[v] -> idx;
        int f = node[idx] -> fail;
        if(node[f] -> nxt[v]) return node[idx] -> fail_nxt[v] = node[f] -> nxt[v] -> idx;
        if(!f) return node[idx] -> fail_nxt[v] = node[f] -> idx;
        return node[idx] -> fail_nxt[v] = transition(f, v);
	}

	vector < int > path;
	void traverse(char *text){
		assert(path.empty());

		trie *current = node[0];
		path.push_back(0);

		for(int i = 0; text[i]; i++){
			int v = rank(text[i]);
			current = node[transition(current->idx, v)];
			path.push_back(current -> idx);
		}

		for(int i = 0; i < (int) path.size(); i++) visit[path[i]]++;

		for(int i = 0; i < (int) patMark.size(); i++)
			ocr[i] = dfs(patMark[i]);

		for(int i = 0; i < (int) nodeList.size(); i++) dp[nodeList[i]] = -1;
		nodeList.clear();

		for(int i = 0; i < (int) path.size(); i++) visit[path[i]]--;
		path.clear();
	}

	void clear(){
		for(int i = 0; i < (int) node.size(); i++) { node[i] -> endCounter.clear(); delete(node[i]); }
		node.clear();
		visit.clear();
		f_tree.clear();
		patMark.clear();
		ocr.clear();
		dp.clear();

		node.push_back(new trie(0));
		visit.push_back(0);
		f_tree.push_back(vector<int>());
		dp.push_back(-1);
	}

};

aho_corasick ac;
char txt[MAX+5], pat[MAX+5];

int main()
{
	//freopen("in.txt", "r", stdin);

	int i, n, t, cs;

	scanf("%d", &t);
	for(cs = 1; cs <= t; cs++){
		scanf("%d", &n);
		scanf("%s", txt);
		for(i = 0; i < n; i++){
			scanf("%s", pat);
			ac.insert(pat, i);
		}
		ac.build();
		ac.traverse(txt);
		printf("Case %d:\n", cs);
		for(i = 0; i < n; i++) printf("%d\n", ac.ocr[i]);

		ac.clear();
	}
	return 0;
}
