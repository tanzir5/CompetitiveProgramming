
//Maintains Max Heap
struct Treap{
    int val, prior, cnt;
    Treap *l, *r;
    Treap(int v): l(NULL), r(NULL), val(v), prior((rand() << 15) + rand()), cnt(1) {}
}; // initialize the root if declared locally

int sz(Treap *t) {return (t == NULL) ? 0:t->cnt;}

void upd_sz(Treap *t){
    if(t) t->cnt = 1 + sz(t->l) + sz(t->r);
}

void split(Treap *t, Treap *&l, Treap *&r, int key)
{
    if(!t) l = r = NULL;
    else if(t->val <= key) {split(t->r, t->r, r, key); l = t;}
    else {split(t->l, l, t->l, key); r = t;}
    upd_sz(t);
}

void merge(Treap *&t, Treap *l, Treap *r) //needed to erase something
{
    if(!l || !r) t = l? l:r;
    else if(l->prior > r->prior) {merge(l->r, l->r, r); t = l;}
    else {merge(r->l, l, r->l);t = r;}
    upd_sz(t);
}

//don't insert duplicate and allocate memory before insertion
//inserts just a node, not a Treap
void insert(Treap *&t, Treap *it)
{
    if(!t) t = it;
    else if(it->prior > t->prior){split(t, it->l, it->r, it->val);t = it;}
    else if (it->val > t->val) insert(t->r, it);
    else insert(t->l, it);
    upd_sz(t);
}

void erase(Treap *&t, int key)
{
    if(!t) return;
    else if(t->val == key) {Treap *temp = t; merge(t,t->l, t->r); delete(temp);}
    else if(key > t->val) erase(t->r, key);
    else erase(t->l, key);
    upd_sz(t);
}

bool find(Treap *t, int key)
{
    if(!t) return false;
    if(t->val == key) return true;
    return (key > t->val)? find(t->r, key):find(t->l, key);
}

void rmv(Treap *u)
{
    if(!u) return;
    rmv(u->l);
    rmv(u->r);
    delete(u);
}

void shift(Treap *&u, Treap *v)
{
    if(!v) return;
    insert(u, new Treap(v->val));
    shift(u, v->l);
    shift(u, v->r);
}

Treap* join(Treap *u, Treap *v)
{
    if(sz(u) < sz(v)) swap(u,v);
    shift(u,v);
    rmv(v);
    return u;
}

int find_kth(Treap *cur, int k)
{
    if(sz(cur->l) < k)
    {
        k -= sz(cur->l);
        if(k == 1) return cur->val;
        return find_kth(cur->r, k-1);
    }
    return find_kth(cur->l, k);
}

int predecessor(Treap *cur, int key) //Greatest one smaller than key
{
    if(!cur) return -inf;
    if(cur->val >= key) return predecessor(cur->l, key);
    return max(cur->val, predecessor(cur->r,key));
}

int successor(Treap *cur, int key) //Smallest one greater than key
{
    if(!cur) return inf;
    if(cur->val <= key) return successor(cur->r,key);
    return min(cur->val, successor(cur->l, key));
}

int cntLessOrE(Treap *cur, int key)
{
    if(!cur) return 0;

    if(cur->val <= key) return 1 + sz(cur->l) + cntLessOrE(cur->r, key);
    return cntLessOrE(cur->l, key);
}

//Build Treap in O(N)
void build_treap(Treap *&t, int *arr, int st, int ed, int cnt = 1e9)
{
    if(st > ed) return void(t == NULL);

    if(st == ed)
    {
        t = new Treap(arr[st], cnt);
        return;
    }

    int mid = (st+ed) >> 1;
    t = new Treap(arr[mid], cnt);
    cnt >>= 1;

    build_treap(t->l, arr, st, mid-1, cnt);
    build_treap(t->r, arr, mid+1,ed, cnt);
    upd_sz(t);
}

void persistent_split(Treap *t, Treap *&l, Treap *&r, int key)
{
    if(!t) l = r = NULL;
    else if(t->val <= key) {
        *l = *t;
        l->r = new Treap(0);
        persistent_split(t->r, l->r, r, key);
        upd_sz(l);
    }
    else {
        *r = *t;
        r->l = new Treap(0);
        persistent_split(t->l, l, r->l, key);
        upd_sz(r);
    }
}


void persistent_merge(Treap *&t, Treap *l, Treap *r){
    if(!l || !r) { t = l ? l : r; return ;}
    if(l->prior > r->prior){
        *t = *l;
        t->r = new Treap(0);
        persistent_merge(t->r, l->r, r);
    }
    else{
        *t = *r;
        t->l = new Treap(0);
        persistent_merge(t->l, l, r->l);
    }
    upd_sz(t);
}

void persistent_insert(Treap *&t, Treap *old, int key){
    t = new Treap(0);
    Treap *l = new Treap(0), *r = new Treap(0), *m = new Treap(0);
    persistent_split(old, l, r, key);
    persistent_merge(m, l, new Treap(key));
    persistent_merge(t, m, r);
}
