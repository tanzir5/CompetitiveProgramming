/*
    1 based indexing
    can link or cut edge of rooted trees in O(logn). Usually has a constant factor equal to 2*constant factor of segment tree or similar.
    Change the update function as you need. Remember the node has only information about the BBST ( splay tree here ) it is part of.
    It cannot store anything related to its subtree in the original tree.
    Call Access(u) to make a splay tree with the nodes from the root to u. u will also be made the root of the splay tree.
    Whenever you need to change a node, access it and then update it. Since it will be at the root of its splay tree, updating its value
    will not affect anyone else. You can also just splay it to get the same effect. But it is better to access it.
    create an object of the class link cut tree to use it. Alternatively, to make the code faster you can change the code for dynamically allocating memory for
    the node pointers in that class and erase the function overloading default destructor.
    ***The link function makes u a child of v. It must be the case that u is a root of a tree.Also u and v
    must be in different trees.
    Don't write your own functions completely inside the class. Rather write the complete function globally with pointers as
    parameters and write helper function inside class where you send only the node ids and call the global function from there.
    Just like how link is written here.
*/
struct Node
{
    int sz, label; /* size, label */ /// keep additional information here as you need
    Node *p, *pp, *l, *r; /* parent, path-parent, left, right pointers in splay tree*/
    Node()
    {
        p = pp = l = r = 0; /// initialize some of the custom variables here if needed. ( like mx)
    }
};

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

Node *root(Node *x)
{
    access(x);
    while(x->l) x = x->l;
    splay(x);
    return x;
}

void cut(Node *x)
{
    access(x);
    x->l->p = 0;
    x->l = 0;
    update(x);
}

void link(Node *x, Node *y)
{
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

int depth(Node *x)
{
    access(x);
    return x->sz - 1;
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

    void cut(int u)
    {
        ::cut(&x[u]);
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
