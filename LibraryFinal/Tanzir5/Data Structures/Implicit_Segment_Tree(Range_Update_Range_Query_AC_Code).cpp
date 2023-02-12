///Implicit Seg Tree
///For long range
/// Range update, Range query AC code
/// When indices can be negative,
/// int mid = floor((st+ed)/2.00);
/// will be useful. That's why it's written like this

struct node{
    LL sum, lazy;
    node *lft,*rght;
    node()
    {
        sum = lazy = 0;
        lft = rght = NULL;
    }
};

void propagate(node *nd, int st, int ed)
{
    int mid = floor((st+ed)/2.00);
    nd->lft->sum += (mid-st+1)*nd->lazy;
    nd->rght->sum += (ed-mid)* nd->lazy;
    nd->lft->lazy += nd->lazy;
    nd->rght->lazy += nd->lazy;
    nd->lazy = 0;
}

void update(node *nd, int st, int ed, int i, int j, LL v)
{
    if(st >= i && ed <= j)
    {
        nd->sum+= (ed-st+1)*v;
        nd->lazy+= v;
        return;
    }

    if(nd->lft == NULL)
        nd->lft = new node();
    if(nd->rght == NULL)
        nd->rght = new node();

    if(nd->lazy)
        propagate(nd, st, ed);

    int mid = floor((st+ed)/2.00);


    if(i <= mid)
        update(nd->lft, st, mid, i, j, v);

    if(j > mid)
        update(nd->rght, mid+1, ed, i, j, v);
    nd->sum = nd->lft->sum + nd->rght->sum;
}

LL query(node *nd, int st, int ed, int i, int j)
{
    if(st >= i && ed <= j)
        return nd->sum;

    if(nd->lft == NULL)
        nd->lft = new node();
    if(nd->rght == NULL)
        nd->rght = new node();

    if(nd->lazy)
        propagate(nd, st, ed);

    int mid = floor((st+ed)/2.00);
    LL ret = 0;
    if(i <= mid)
        ret+= query(nd->lft, st, mid, i, j);

    if(j > mid)
        ret+= query(nd->rght, mid+1, ed, i, j);

    return ret;
}

void rmv(node *cur)
{
    if(!cur) return;
    rmv(cur->lft);
    rmv(cur->rght);
    delete(cur);
}


int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int i, j, cs, t, type, n, q, v;
    sf(t);
    FRE(cs,1,t)
    {
        sff(n,q);
        node *root = new node();
        while(q--)
        {
            sfff(type, i, j);
            if(type == 0)
                sf(v), update(root, 1, n, i, j, v);
            else
                printf("%lld\n",query(root, 1, n, i, j));
        }
        rmv(root);
    }
    return 0;
}
