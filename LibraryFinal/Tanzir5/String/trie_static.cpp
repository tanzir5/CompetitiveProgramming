/*
    Static memory allocation.
    Will need O(total number of characters in all the input strings) memory at most.
    Find returns true if a string has been previously inserted into the trie.
*/

#define MAX     total number of characters in all the input strings ?
int total;
struct node{
    bool end_mark;
    int nxt[26];
}trie[MAX+10];

void init()
{
    total = 0;
    mem(trie,0);
}

void add(char s[])
{
    int len = strlen(s);
    int cur = 0;
    for(int i = 0; i<len; i++)
    {
        int nw = s[i] - 'a';
        if(trie[cur].nxt[nw] == 0)
            trie[cur].nxt[nw] = ++total;
        cur = trie[cur].nxt[nw];
    }
    trie[cur].end_mark = true;
}

bool Find(char s[])
{
    int len = strlen(s);
    int cur = 0;
    for(int i = 0; i<len; i++)
    {
        int nw = s[i] - 'a';
        if(trie[cur].nxt[nw] == 0)
            return false;
        cur = trie[cur].nxt[nw];
    }
    return trie[cur].end_mark;
}
