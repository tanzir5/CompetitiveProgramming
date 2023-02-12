
struct lazy{
    LL lz;

    //Initialize here
    lazy(){
        lz = 0;
    }

    //Merge two lazies
    void impose(lazy ano){
        lz += ano.lz;
    }
};


bool notCleared(lazy L){ //Returns true if the lazy needs to be propagated
    return (bool)  L.lz;
}


struct node{
    //Insert the attributes here
    LL sum;
    lazy L;

    //The range it holds
    int l, r;

    //Initialize here
    node(){
        sum = l = r = 0;
    }

    //Applies the given lazy on the attributes and imposes the lazy with its own lazy
    void apply(lazy ano){
        sum += ano.lz * (r - l + 1);
        L.impose(ano);
    }

    void clearLazy(){
        L.lz = 0;
    }
} tree[MAX << 2];


void propagate(int idx)
{
    int l = 2*idx, r = l + 1;

    tree[l].apply(tree[idx].L);
    tree[r].apply(tree[idx].L);

    tree[idx].clearLazy();
}

void build_tree(int idx, int st, int ed)
{
    tree[idx].l = st;
    tree[idx].r = ed;
    tree[idx].clearLazy();

    if(st == ed){
        //Base Case
        tree[idx].sum = 0;
        return;
    }
    int mid = (st+ed)/2, l = 2*idx, r = l + 1;
    build_tree(l, st, mid);
    build_tree(r, mid+1, ed);


    //Merge the attributes here
    tree[idx].sum = tree[l].sum + tree[r].sum;
}

void update(int idx, int st, int ed, int i, int j, lazy &curr)
{
    if(st == i && ed == j)
    {
        tree[idx].apply(curr);
        return;
    }

    int mid = (st+ed)/2, l = 2*idx, r = l+1;
    if( notCleared(tree[idx].L) ) propagate(idx);

    if(j <= mid) update(l , st, mid, i, j, curr);
    else if(i > mid) update(r, mid+1, ed, i, j, curr);
    else update(l, st, mid, i, mid, curr), update(r, mid+1, ed, mid+1, j, curr);

    //Merge the attributes here
    tree[idx].sum = tree[l].sum + tree[r].sum;
}

LL query(int idx, int st, int ed, int i, int j)
{
    if(st == i && ed == j) return tree[idx].sum;
    int mid = (st+ed)/2, l = 2*idx, r = l + 1;

    if( notCleared(tree[idx].L) ) propagate(idx);

    if(j <= mid) return query(l, st, mid, i, j);
    if(i > mid) return query(r, mid+1, ed, i, j);
    return (query(l,st,mid,i,mid) + query(r,mid+1,ed,mid+1,j));
}




