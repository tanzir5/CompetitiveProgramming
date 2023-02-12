#include<bits/stdc++.h>
using namespace std;


struct Node
{
    int sz, label; /* size, label */
    bool flip;
    Node *p, *pp, *l, *r; /* parent, path-parent, left, right pointers */
    Node()
    {
        p = pp = l = r = 0;
        flip = false;
    }
};

void update(Node *x)
{
    x->sz = 1;
    if(x->l) x->sz += x->l->sz;
    if(x->r) x->sz += x->r->sz;
}

void normalize(Node *x){ ///PUSH THE LAZY DOWN
	if(x->flip){
		if(x->l){
			x->l->flip ^= 1;
			swap(x->l->l, x->l->r);
		}
		if(x->r){
			x->r->flip ^= 1;
			swap(x->r->l, x->r->r);
		}
		x->flip = 0;
	}
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
    while(x->l) x = x->l;
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

void make_root(Node *x){
	access(x);
	x->flip = true;
	swap(x->l, x->r);

}

class LinkCut
{
    Node *x;

public:
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

    void link(int u, int v)
    {
		::make_root(&x[u]);
        ::link(&x[u], &x[v]);
    }

    void cut(int u, int v)
    {
		if(depth(u) > depth(v)) ::cut(&x[u]);
		else ::cut(&x[v]);
    }

    int root(int u)
    {
        return ::root(&x[u])->label;
    }

    int depth(int u)
    {
        return ::depth(&x[u]);
    }

    int lca(int u, int v)
    {
        return ::lca(&x[u], &x[v])->label;
    }
}*lctree;

char str[11];

int main(){
	//freopen("in.txt", "r", stdin);
	int n, m, u, v;

	scanf("%d %d", &n, &m);
	lctree = new LinkCut(n);

	while(m--){
		scanf("%s", str);
		if(str[0] == 'a'){
			scanf("%d %d", &u, &v);
			lctree -> link(u, v);
		}
		else if(str[0] == 'r'){
			scanf("%d %d", &u, &v);
			lctree -> cut(u, v);
		}
		else{
			scanf("%d %d", &u, &v);
			if(lctree->root(u) == lctree->root(v)) puts("YES");
			else puts("NO");
		}
	}
	return 0;
}

///11111
