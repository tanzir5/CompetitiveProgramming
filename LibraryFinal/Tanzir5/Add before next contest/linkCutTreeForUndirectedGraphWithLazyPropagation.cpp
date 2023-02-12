/*
    1 based indexing
    can link or cut edge of unrooted trees in O(logn). You have a current root of a tree but you can make any node u, the root of its tree
    by calling makeroot(u). Makeroot uses lazy propagation technique. normalize is the function for propagating your lazy value
    to your right and left child in the splay tree. If you only need the lazy propagation part but not the undirected tree part
    of the code, write your normalize function and call it at the same places as here.
    When cut(a,b) is called it must be the case that a and b has a direct edge between them which will be cut.
*/
struct Node
{
    int sz, label, flip; /* size, label, flip for evert operation */ /// keep additional information here as you need
    Node *p, *pp, *l, *r; /* parent, path-parent, left, right pointers in splay tree*/
    Node()
    {
        p = pp = l = r = 0; /// initialize some of the custom variables here if needed. ( like mx)
        flip = 0;
    }
};

void normalize(Node *x)
{
    if(x->flip)
    {
        if(x->l)
        {
            x->l->flip ^= 1;
            swap(x->l->l, x->l->r);
        }
        if(x->r)
        {
            x->r->flip ^= 1;
            swap(x->r->l, x->r->r);
        }
        x->flip = 0;
    }
}



void update(Node *x) /// change here as you need.
{
    x->sz = 1;
    if(x->l) x->sz += x->l->sz;
    if(x->r) x->sz += x->r->sz;
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

void makeRoot(Node *x)
{
    access(x);
    x->flip ^= 1;
    swap(x->l, x->r);
}

int depth(Node *x)
{
    access(x);
    return x->sz - 1;
}

Node *root(Node *x)
{
    access(x);
    while(x->l) x = x->l;
    splay(x);
    return x;
}

void cut(Node *x, Node *y)
{
    if(depth(x) < depth(y))
        swap(x, y);
    access(x);
    x->l->p = 0;
    x->l = 0;
    update(x);
}

void link(Node *x, Node *y)
{
    makeRoot(x);
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



class LinkCut
{
public:
    Node *x;

    LinkCut(int n)
    {
        x = new Node[n+5];
        for(int i = 1; i <= n; i++)
        {
            x[i].label = i;
            update(&x[i]); /// initialize your custom variables here.
        }
    }

    virtual ~LinkCut()
    {
        delete[] x;
    }

    /// ***The link function makes u a child of v. It must be the case that u is a root of a tree.
    ///    Also u and v must be in different trees.
    void link(int u, int v)
    {
        ::link(&x[u], &x[v]);
    }

    void cut(int u, int v)
    {
        ::cut(&x[u], &x[v]);
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
    void access(int u)
    {
        ::access(&x[u]);
    }
};
