
// Persistent segment tree
struct node{
    LL sum;
    node *l, *r;

    node(){
        l = r = 0;
        sum = 0;
    }
};

struct persistent_segment_tree{
    node *root[2*MAX+5];

    void build(node *cur, int st, int ed){
        if(st == ed) return;
        cur->l = new node;
        cur->r = new node;
        int mid = (st+ed)/2;
        build(cur->l, st, mid);
        build(cur->r, mid+1, ed);
    }

    persistent_segment_tree(int n = MAX+1){
        root[0] = new node;
        build(root[0], 1, n);
    }

    void update(node *cur, node *prv, int st, int ed, int pos, int val){
        if(st == ed){
            cur->sum = prv->sum + val;
            return;
        }

        int mid = (st+ed)/2;
        if(pos <= mid){
            cur->l = new node;
            cur->r = prv->r;
            update(cur->l, prv->l, st, mid, pos, val);
        }
        else{
            cur->l = prv->l;
            cur->r = new node;
            update(cur->r, prv->r, mid+1, ed, pos, val);
        }

        cur->sum = cur->l->sum + cur->r->sum;
    }

    LL query(node *cur, int st, int ed, int i, int j)
    {
        if(st == i && ed == j) return cur->sum;
        int mid = (st+ed)/2;
        if(j <= mid) return query(cur->l, st, mid, i, j);
        else if(i > mid) return query(cur->r, mid+1, ed, i, j);
        return query(cur->l, st, mid, i, mid) + query(cur->r, mid+1, ed, mid+1, j);
    }
};
