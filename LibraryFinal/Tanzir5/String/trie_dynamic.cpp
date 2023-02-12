/*
    Dynamic memory allocation.
    Will need O(total number of characters in all the input strings) memory at most.
    Find returns true if a string has been previously inserted into the trie.
*/

struct node{
    bool end_mark;
    node *nxt[26];
    node()
    {
        end_mark = false;
        for(int i = 0; i<26; i++)
            nxt[i] = NULL;
    }
}*root;

void del(node *cur)
{
    for(int i = 0; i<26; i++)
    {
        if(cur->nxt[i] != NULL)
            del(cur->nxt[i]);
    }
    delete(cur);
}
void init()
{
    if(root != NULL)
        del(root);
    root = new node();
}

void add(string s)
{
    node *current = root;
    for(int i = 0; i<s.size(); i++)
    {
        int nw = s[i] - 'a';
        if(current->next[nw] == NULL)
            current->next[nw] = new node();
        current = current->next[nw];
    }
    current->end_mark = true;
}

bool Find(string s)
{
    node *current = root;
    for(int i = 0; i<s.size(); i++)
    {
        int nw = s[i] - 'a';
        if(current->next[nw] == NULL)
            return 0;
        current = current->next[nw];
    }
    return current->end_mark;
}
