
#include<bits/stdc++.h>
using namespace std;
#define D(x)	cout << #x " = " << (x) << endl
#define MAX		300000

int lct_par[MAX+5];
int n;

struct Node
{
    int sz, label, value, lazy; /* size, label */
    Node *p, *pp, *l, *r; /* parent, path-parent, left, right pointers */
    Node()
    {
        p = pp = l = r = 0;
        lazy = value = 0;
    }
};

void normalize(Node *x){ ///PUSH THE LAZY DOWN
	if(x->lazy){
		if(x->l){
			x->l->lazy += x->lazy;
			x->l->value += x->lazy;
		}
		if(x->r){
			x->r->lazy += x->lazy;
			x->r->value += x->lazy;
		}

		x->lazy = 0;
	}
}

void update(Node *x)
{
    assert(!x->lazy);
    x->sz = 1;
    if(x->l) x->sz += x->l->sz;
    if(x->r) x->sz += x->r->sz;
}

void set_value(Node *x, int v){
	x->value = v;
}

void rotr(Node *x)
{
    Node *y, *z;
    y = x->p, z = y->p;
    normalize(y);
    normalize(x);

    if((y->l = x->r)) y->l->p = y;
    x->r = y, y->p = x;
    if((x->p = z))
    {
        if(y == z->l) z->l = x;
        else z->r = x;
    }
    x->pp = y->pp;
    y->pp = 0;
    update(y);
}

void rotl(Node *x)
{
    Node *y, *z;
    y = x->p, z = y->p;
    normalize(y);
    normalize(x);

    if((y->r = x->l)) y->r->p = y;
    x->l = y, y->p = x;
    if((x->p = z))
    {
        if(y == z->l) z->l = x;
        else z->r = x;
    }
    x->pp = y->pp;
    y->pp = 0;
    update(y);
}

void splay(Node *x)
{
    Node *y, *z;
    while(x->p)
    {
        y = x->p;
        if(y->p == 0)
        {
            if(x == y->l) rotr(x);
            else rotl(x);
        }
        else
        {
            z = y->p;
            if(y == z->l)
            {
                if(x == y->l) rotr(y), rotr(x);
                else rotl(x), rotr(x);
            }
            else
            {
                if(x == y->r) rotl(y), rotl(x);
                else rotr(x), rotl(x);
            }
        }
    }
    normalize(x);
    update(x);
}

Node *access(Node *x)
{
    splay(x);
    if(x->r)
    {
        x->r->pp = x;
        x->r->p = 0;
        x->r = 0;
        update(x);
    }

    Node *last = x;
    while(x->pp)
    {
        Node *y = x->pp;
        last = y;
        splay(y);
        if(y->r)
        {
            y->r->pp = y;
            y->r->p = 0;
        }
        y->r = x;
        x->p = y;
        x->pp = 0;
        update(y);
        splay(x);
    }
    return last;
}

Node *root(Node *x)
{
    access(x);
    while(x->l)
    {
		x = x->l;
	}
    splay(x);
    return x;
}

void cut(Node *x)
{
    access(x);
    x->l->p = 0;
    x->l = 0;
    update(x);
}

void link(Node *x, Node *y)
{
    access(x);
    access(y);
    x->l = y;
    y->p = x;
    update(x);
}

Node *lca(Node *x, Node *y)
{
    access(x);
    return access(y);
}

int depth(Node *x)
{
    access(x);
    return x->sz - 1;
}

int query(Node *x){
	access(x);
	return x->value;
}

void range_update(Node *x, int lz){
	access(x);
	x->lazy += lz;
	x->value += lz;
}

int special_root(Node *x){
	access(x);
	Node *r = root(x);
	splay(r);
	r = r->r;
	while(r->l) r = r->l;
	return r->label;
}

class LinkCut
{
public:
    Node *x;

    LinkCut(int n)
    {
        x = new Node[n+5];
        for(int i = 1; i <= n; i++)
        {
            x[i].label = i;
            update(&x[i]);
        }
    }

    virtual ~LinkCut()
    {
        delete[] x;
    }

    void set_value(int u, int v){
		::set_value(&x[u], v);
	}

    void link(int u, int v)
    {
		lct_par[u] = v;

		int sz = ::query(&x[u]);
		::range_update(&x[v], +sz);

		assert(u);
		assert(v);
        ::link(&x[u], &x[v]);
    }

    void cut(int u)
    {
		assert(u);
		int sz = ::query(&x[u]);
		if(lct_par[u]){
			::range_update(&x[lct_par[u]], -sz);
		}
        ::cut(&x[u]);
    }

    int root(int u)
    {
        int ret = ::root(&x[u])->label;
        if(ret <= n) return ret;
        return ::special_root(&x[u]);
    }

    int depth(int u)
    {
        return ::depth(&x[u]);
    }

    int lca(int u, int v)
    {
        return ::lca(&x[u], &x[v])->label;
    }

    int query(int u){
		return ::query(&x[u]);
	}
}*lctree;

#define BLACK		0
#define WHITE		1

vector<int> edge[MAX+5];
int same[MAX+5], dif[MAX+5], running, par[MAX+5], color[MAX+5];

int dfs(int idx, int p = -1){
	assert(idx);

	same[idx] = ++running;
	dif[idx] = ++running;
	color[idx] = BLACK;
	par[idx] = p;


	int ret = 1;
	for(auto x : edge[idx])
		if(x != p)
			ret += dfs(x, idx);

	if(p != -1) lctree -> link(idx, same[p]);
	lctree->link(same[idx], idx);


	lctree->set_value(idx, ret);
	lctree->set_value(same[idx], ret - 1);
	return ret;
}

void toggle(int idx){

	lctree->cut(same[idx]);
	lctree->link(dif[idx], idx);

	int p = par[idx];

	if(p != -1){
		if(color[par[idx]] == color[idx]){
			lctree-> cut(idx);
			lctree ->link(idx, dif[par[idx]]);
		}
		else{
			lctree-> cut(idx);
			lctree->link(idx, same[par[idx]]);
		}
	}

	swap(same[idx], dif[idx]);
	color[idx] = 1 - color[idx];

}

bool vis[MAX+5];
int brute(int idx){
	if(vis[idx]) return 0;
	int ret = 1;

	vis[idx] = true;
	for(auto x: edge[idx])
		if(color[x] == color[idx])
			ret += brute(x);

	return ret;
}

int main(){
	//freopen("in.txt", "r", stdin);

	int i, u, v, q, tp, idx, ans;
	scanf("%d", &n);
	lctree = new LinkCut(n * 3);
	running = n;

	for(i = 1; i < n; i++){
		scanf("%d %d", &u, &v);
		edge[u].push_back(v);
		edge[v].push_back(u);
	}

	dfs(1);


	scanf("%d", &q);
	while(q--){
		scanf("%d %d", &tp, &idx);
		if(tp == 0){
			printf("%d\n", ans = lctree->query(lctree->root(idx)));
			//memset(vis, false, sizeof(vis));
			//assert(ans == brute(idx));
		}
		else{
			toggle(idx);
		}
	}
	return 0;
}
