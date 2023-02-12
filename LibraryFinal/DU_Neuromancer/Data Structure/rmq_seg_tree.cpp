
// Range Minimum Query = Structre of Segment Tree [ Single Point update, range query ]
struct node{
    int min;
};

node tree[4*MAX];

void update_single_node(int idx, int val) // change here
{
    tree[idx].min= val;
    return;
}

void update(int idx, int st, int ed, int pos, int val) // single point update
{
    if(pos < st || pos > ed) return;
    if(st == ed)
    {
        update_single_node(idx, val);
        return;
    }
    int mid = (st+ed)/2, l = 2*idx, r = l+1;
    update(l,st,mid,pos,val);
    update(r,mid+1,ed,pos,val);
    tree[idx].min = min(tree[l].min, tree[r].min);
}

int query(int idx, int st, int ed, int i, int j) // Range Query
{
    if(st == i && ed == j) return tree[idx].min;
    int mid = (st+ed)/2, l =2*idx, r = l+1;
    if(j <= mid) return query(l,st,mid,i,j);
    if(i > mid) return query(r,mid+1,ed,i,j);
    return min(query(l,st,mid,i,mid), query(r,mid+1,ed,mid+1,j));
}
