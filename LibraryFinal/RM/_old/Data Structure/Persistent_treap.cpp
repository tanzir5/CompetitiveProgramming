void persistent_split(Treap *t, Treap *&l, Treap *&r, LL key)
{
    if(!t) l = r = NULL;
    else if(t->val <= key) {
        *l = *t;
        l->r = new Treap(0);
        persistent_split(t->r, l->r, r, key);
        upd_sz(l);
    }
    else {
        *r = *t;
        r->l = new Treap(0);
        persistent_split(t->l, l, r->l, key);
        upd_sz(r);
    }
}


void persistent_merge(Treap *&t, Treap *l, Treap *r){
    if(!l || !r) { t = l ? l : r; return ;}
    if(l->prior > r->prior){
        *t = *l;
        t->r = new Treap(0);
        persistent_merge(t->r, l->r, r);
    }
    else{
        *t = *r;
        t->l = new Treap(0);
        persistent_merge(t->l, l, r->l);
    }
    upd_sz(t);
}

void persistent_insert(Treap *&t, Treap *old, LL key, LL x = 0){
    t = new Treap(0);
    Treap *l = new Treap(0), *r = new Treap(0), *m = new Treap(0);
    persistent_split(old, l, r, key);
    persistent_merge(m, l, new Treap(key));
    persistent_merge(t, m, r);
}


void persistent_erase(Treap *&t, Treap *old, LL key)
{
    t = new Treap(0);
    if(!old) {t = 0; return;}
    Treap *l = new Treap(0), *m1 = new Treap(0), *m2 = new Treap(0), *r = new Treap(0);
    persistent_split(old, l, r, key);
    persistent_split(l, m1, m2, key - 1);
    persistent_merge(t, m1, r);
}
