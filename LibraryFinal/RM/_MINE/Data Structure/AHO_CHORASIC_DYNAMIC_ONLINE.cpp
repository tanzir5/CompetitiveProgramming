
#include<bits/stdc++.h>
using namespace std;
#define D(x)    cout << #x " = " << (x) << endl
#define MAX     300000
typedef long long int LL;

#define ALPHABET_SIZE	26
#define MAXL			300000

struct aho_corasick{

	struct trie{
		int fail, idx, endCounter, dp;
		trie *nxt[ALPHABET_SIZE];

		trie(int _idx){
			fail = 0;
			idx = _idx;
			endCounter = dp = 0;
			memset(nxt, 0, sizeof(nxt));
		}
	};

	vector< trie * > node;

	aho_corasick(){
		node.push_back(new trie(0));
	}

	int rank(char ch){return ch - 'a';}

	void insert(char *pat, int sign){
		trie *cur = node[0];
		for(int i = 0; pat[i]; i++){
			int v = rank(pat[i]);
			if(!cur->nxt[v]){
				cur->nxt[v] = new trie(node.size());
				node.push_back(cur->nxt[v]);
			}
			cur = cur->nxt[v];
		}
		assert(sign == -1 || sign == +1);
		cur->endCounter += sign;
	}

	void build(){
		int i;
		queue<trie *> Q;

		for(i = 0; i < ALPHABET_SIZE; i++)
			if(node[0] -> nxt[i]){
				trie *p = node[0] -> nxt[i];
				p -> fail = 0;
				p -> dp = p -> endCounter;
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

					Q.push(u->nxt[i]);
					v -> dp = v -> endCounter + node[v -> fail] -> dp;
				}
			}
		}
	}


	LL traverse(char *text){
        LL ret = 0;
		trie *current = node[0];

		for(int i = 0; text[i]; i++){
			int v = rank(text[i]);
			if(current -> nxt[v]) current = current -> nxt[v];
			else{
				int f = current -> idx;
				while(true){
					f = node[f] -> fail;
					if(node[f] -> nxt[v]){
						current = node[f] -> nxt[v];
						break;
					}
					else if(!f) {current = node[f]; break;}
				}
			}

			ret += (current -> dp);//path.push_back(current -> idx);
		}
		return ret;
	}

	void clear(){
		for(int i = 0; i < (int) node.size(); i++) { delete(node[i]); }
		node.clear();
		node.push_back(new trie(0));
	}
};

#define LOG     23
struct dynamic_ac{
    aho_corasick ac[LOG];
    vector< pair<string,int> > input[LOG];

    void insert(char *str, int sign){
        int i, k;
        for(k = 0; k < LOG; k++) if(input[k].size() == 0) break;
        input[k].push_back(make_pair(string(str), sign));
        ac[k].insert(str, sign);
        for(i = 0; i < k; i++){
            ac[i].clear();
            for(auto s : input[i]) {
                ac[k].insert((char *) s.first.c_str(), s.second);
                input[k].push_back(s);
            }
            input[i].clear();
        }
        ac[k].build();
    }

    LL query(char *str){
        LL ret = 0;
        for(int i = 0; i < LOG; i++)
                ret += ac[i].traverse(str);

        return ret;
    }
} d_ac;

char str[MAX+5];

int main()
{
//    freopen("in.txt", "r", stdin);

    int q, tp;
    scanf("%d", &q);

    while(q--){
        scanf("%d", &tp);
        scanf("%s", str);

        if(tp == 1) d_ac.insert(str, 1);
        else if(tp == 2) d_ac.insert(str, -1);
        else {printf("%lld\n", d_ac.query(str)); fflush(stdout);}
    }
    return 0;
}
