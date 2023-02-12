
//Static Treap As Dynamic Array
const int inf = 1e9;
int indx, cur_rt;
struct Treap{
    int val, prior, cnt;
    int l, r;
    Treap(int v = inf): l(inf), r(inf), val(v), prior((rand() << 15) + rand()), cnt(1) {}
}Rt[MAX+11];

void init_treap(){
    indx = -1;
    cur_rt = inf;
}

int sz(int t) {return (t == inf) ? 0:Rt[t].cnt;}

void upd_sz(int t){
    if(t != inf) Rt[t].cnt = 1 + sz(Rt[t].l) + sz(Rt[t].r);
}

void split(int t, int &l, int &r, int pos, int add = 0)
{
    if(t == inf) return void(l = r = inf);
    int cur_pos = add + sz(Rt[t].l) + 1;
    if(cur_pos <= pos) split(Rt[t].r, Rt[t].r, r, pos, cur_pos), l = t;
    else split(Rt[t].l, l ,Rt[t].l, pos, add), r = t;
    upd_sz(t);
}


void merge(int &t, int l, int r) //needed to erase something
{
    if(l == inf || r == inf) t = (l != inf)? l:r;
    else if(Rt[l].prior > Rt[r].prior) {merge(Rt[l].r, Rt[l].r, r); t = l;}
    else {merge(Rt[r].l, l, Rt[r].l);t = r;}
    upd_sz(t);
}


void insert(int &t, int pos, int val)
{
    int l, r;
    Rt[++indx] = Treap(val);
    split(t, l, r, pos-1);
    merge(t, l, indx);
    merge(t, t, r);
}


void erase(int &t, int pos)
{
    int l, r, g;
    split(t, l, r, pos-1);
    split(r, g, r, 1);
    merge(t, l, r);
}


int find_kth(int t, int k, int add = 0)
{
    assert(t != inf);
    int cur_pos = add + sz(Rt[t].l) + 1;
    if(cur_pos == k) return Rt[t]. val;
    if(cur_pos < k) return find_kth(Rt[t].r, k, cur_pos);
    return find_kth(Rt[t].l, k, add);
}
