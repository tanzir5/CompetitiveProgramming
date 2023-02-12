
///Time_Efficient
// Static TrieTree
// AS => Alphabet Size

#define MAXNODE     1000000
#define AS          26
#define scale(x)    (x-'a')

int nxt[MAXNODE+2][AS+2];
int ep[MAXNODE+2];

struct TrieTree{
    int idx, rt;
    TrieTree()
    {
        rt = idx = 0;
        memset(nxt[rt], -1, sizeof(nxt[rt]));
        memset(ep, false, sizeof(ep));
    }
    void insert(char *s);
    bool find(char *s);
};

void TrieTree::insert(char *s)
{
    int i, cur, len = strlen(s), v;

    cur = rt;
    FRL(i,0,len)
    {
        v = scale(s[i]);
        if(nxt[cur][v] == -1)
        {
            idx++;
            memset(nxt[idx], -1, sizeof(nxt[idx]));
            nxt[cur][v] = idx;
        }
        cur = nxt[cur][v];
    }
    ep[cur]++;
}

bool TrieTree::find(char *s)
{
    int i, cur, len = strlen(s), v;

    cur = rt;
    FRL(i,0,len)
    {
        v = scale(s[i]);
        if(nxt[cur][v] == -1) return false;
        cur = nxt[cur][v];
    }
    return ep[cur];
}
