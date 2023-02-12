
///Memory_Efficient
// Dynamic Trie
// Slower than static Trie
// have a root = new trie

#define AS          26
#define scale(x)    x-'a'

struct trie{
    trie *nxt[AS+2];
    int ep;

    trie()
    {
        int i;
        ep = 0;
        for(i = 0; i <= AS; i++)
            nxt[i] = NULL;
    }
};

void Insert(trie *rt, char *s)
{
    int i, v, len = strlen(s);
    for(i = 0; i < len; i++)
    {
        v = scale(s[i]);
        if(rt->nxt[v] == NULL)
            rt->nxt[v] = new trie;

        rt = rt->nxt[v];
    }
    rt->ep++;
}

bool Find(trie *rt, char *s)
{
    int i, v, len = strlen(s);
    for(i = 0; i < len; i++)
    {
        v = scale(s[i]);
        if(rt->nxt[v] == NULL) return false;
        rt = rt->nxt[v];
    }
    return rt->ep;
}

void rmv(trie *rt)
{
    int i;
    for(i = 0; i <= AS; i++)
        if(rt->nxt[i] != NULL)
            rmv(rt->nxt[i]);
    free(rt);
}
