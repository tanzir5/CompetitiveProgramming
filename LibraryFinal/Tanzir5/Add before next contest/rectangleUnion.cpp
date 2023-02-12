/*
    Finding number of non-zero points in a range will only work if there is no update in any of the parent/ancestor nodes of the node of the range.
*/
struct nodeData{
    int command, on;
    nodeData *lft, *rght;
    nodeData()
    {
        command = on = 0;
        lft = rght = NULL;
    }
}*root;

void update(nodeData* node, int st, int ed, int i, int j, int v)
{
    int mid = (st+ed)/2;
    if(st >= i && ed <= j)
    {
        node->command+=v;
        if(node->command > 0)
            node->on = (ed-st+1);
        else
        {
            node->on = 0;
            if(node->lft != NULL)
                node->on += node->lft->on;
            if(node->rght != NULL)
                node->on += node->rght->on;
        }
        return;
    }

    if(i <= mid)
    {
        if(node->lft == NULL)
            node->lft = new nodeData();
        update(node->lft, st, mid, i, j, v);
    }
    if(j > mid)
    {
        if(node->rght == NULL)
            node->rght = new nodeData();
        update(node->rght, mid+1, ed, i, j, v);
    }
    if(node->command == 0)
    {
        node->on = 0;
        if(node->lft != NULL)
            node->on += node->lft->on;
        if(node->rght != NULL)
            node->on += node->rght->on;
    }
}

int query()
{
    return root->on;
}
struct segment{
    int ySt, yEd, x;
    bool st;
};

bool operator < (segment a, segment b)
{
    return a.x < b.x;
}

vector<segment>V;

LL rectangleUnion(vector<segment>&V)
{
    sort(V.begin(), V.end());
    int mx = 0;
    for(int i = 0; i<V.size(); i++)
        mx = max(mx, V[i].yEd);
    int n = mx;

    int last = -1;
    LL ret = 0;
    for(int i = 0; i<V.size(); i++)
    {
        if(last != -1)
            ret += (LL)(V[i].x - last)* query();
        last = V[i].x;
        if(V[i].st == true)
            update(root,1,n,V[i].ySt+1,V[i].yEd,1);
        else
            update(root,1,n,V[i].ySt+1,V[i].yEd,-1);
    }
    return ret;
}
