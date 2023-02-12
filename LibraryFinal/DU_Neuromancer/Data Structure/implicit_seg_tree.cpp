
///Implicit Seg Tree
///For long range

struct node{
    int sum;
    node *l,*r;
    node():sum(0),l(0),r(0){}
};

void update(node *cur, int st, int ed, int pos, int val)
{
    if(st == ed)
    {
        cur->sum += val;
        return;
    }

    int mid = (st+ed)/2;
    if(!cur->l) cur->l = new node;
    if(!cur->r) cur->r = new node;

    if(pos <= mid) update(cur->l, st, mid, pos,val);
    else if(pos > mid) update(cur->r, mid+1,ed,pos,val);

    cur->sum = (cur->l)->sum + (cur->r)->sum;
}

int query(node *cur, int st, int ed, int i, int j)
{
    if(!cur) return 0;
    if(st == i && ed == j) return cur->sum;

    int mid=(st+ed)/2;
    if(j <= mid) return query(cur->l, st, mid, i,j);
    else if(i > mid) return query(cur->r, mid+1,ed,i,j);
    return query(cur->l,st,mid,i,mid) + query(cur->r,mid+1,ed,mid+1,j);
}

void rmv(node *cur)
{
    if(!cur) return;
    rmv(cur->l);
    rmv(cur->r);
    delete(cur);
}
