
//Static Basic BBST

int cur_rt;
int indx;
//Maintains Max Heap
struct Treap{
    int val, prior, cnt;
    int l, r;
    Treap(int v = 0): l(0), r(0), val(v), prior((rand() << 15) + rand()), cnt(1) {}
} rt[MAX+11]; // initialize the root if declared locally

void init_treap(){
    indx = cur_rt = 0;
    memset(rt, 0, sizeof(rt));
}

int sz(int t) {return (t == 0) ? 0:rt[t].cnt;}

void upd_sz(int t){
    if(t != 0) rt[t].cnt = 1 + sz(rt[t].l) + sz(rt[t].r);
}

void split(int t, int &l, int &r, int key)
{
    if(t == 0) l = r = 0;
    else if(rt[t].val <= key) {split(rt[t].r, rt[t].r, r, key); l = t;}
    else {split(rt[t].l, l, rt[t].l, key); r = t;}
    upd_sz(t);
}

void merge(int &t, int l, int r) //needed to erase something
{
    if(l == 0 || r == 0) t = (l == 0)? l:r;
    else if(rt[l].prior > rt[r].prior) {merge(rt[l].r, rt[l].r, r); t = l;}
    else {merge(rt[r].l, l, rt[r].l);t = r;}
    upd_sz(t);
}

//don't insert duplicate and allocate memory before insertion
//inserts just a node, not a Treap
void insert(int &t, Treap it)
{
    if(t == 0)
    {
        t = ++indx;
        rt[t] = it;
    }
    else if(it.prior > rt[t].prior){split(t, it.l, it.r, it.val); rt[++indx] = it; t = indx;}
    else if (it.val > rt[t].val) insert(rt[t].r, it);
    else insert(rt[t].l, it);
    upd_sz(t);
}

void erase(int &t, int key)
{
    if(t == 0) return;
    else if(rt[t].val == key) {int tmp = t; merge(t,rt[t].l, rt[t].r); rt[tmp] = 0;}
    else if(key > rt[t].val) erase(rt[t].r, key);
    else erase(rt[t].l, key);
    upd_sz(t);
}

bool find(int t, int key)
{
    if(t == 0) return false;
    if(rt[t].val == key) return true;
    return (key > rt[t].val)? find(rt[t].r, key):find(rt[t].l, key);
}

int find_kth(int cur, int k)
{
    if(sz(rt[cur].l) < k)
    {
        k -= sz(rt[cur].l);
        if(k == 1) return rt[cur].val;
        return find_kth(rt[cur].r, k-1);
    }
    return find_kth(rt[cur].l, k);
}
