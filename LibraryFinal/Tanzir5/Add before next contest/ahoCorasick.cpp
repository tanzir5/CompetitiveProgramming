/// Call initRank() before doing anything
/// O(nlogn) for inserting n characters as pattern dynamically in the dynamic aho corasick
/// Look at init() inside ahoCorasick if you need

/// NEVER FORGET TO CALL BUILD()

/// After build() is done, trie[i].edge[j] will contain an original edge if the character j is
/// reachable directly from i.
/// Otherwise, trie[i].edge[j] will contain an edge where you will go after traversing through failurelinks
/// till you reach a position where a node has an edge with character j or the node is root.
/// So trie will not remain a tree, it will become a DAG. Change inside build to keep it as a tree.
#define MAX     ?
#define ALPHABET_SIZE ?
const int LOG = log2(MAX)+5;
int Rank[300];
void initRank()
{
    for(char c = 'a'; c<='z'; c++)
        Rank[c] = c-'a';
}

struct ahoCorasick{
    struct node{
        int edge[ALPHABET_SIZE];
        int failLink;
        int counter; /// change this variable to whatever you need to do
    }dummy;

    bool alive;
    vector<node>trie;
    vector<string>dictionary;
    void Clear()
    {
        trie.clear();
        dictionary.clear();
        alive = false;
    }

    ahoCorasick()
    {
        alive = false;
    }

    void init()
    {
        alive = true;
        dummy.failLink = 0;
        dummy.counter = 0;  /// set the dummy's value appropriately
        mem(dummy.edge, -1);
        trie.push_back(dummy);
    }
    void add(string &s)
    {
        dictionary.pb(s);
        int len = s.length();
        int cur = 0;
        for(int i = 0; i<len; i++)
        {
            int nw = Rank[s[i]];
            if(trie[cur].edge[nw] == -1)
            {
                trie.pb(dummy);
                trie[cur].edge[nw] = trie.size()-1;
            }
            cur = trie[cur].edge[nw];
        }
        trie[cur].counter++;  /// change this line as you need
    }

    inline void build()
    {
        queue<int>Q;
        trie[0].failLink = 0;
        for(int i = 0; i<ALPHABET_SIZE; i++)
        {
            if(trie[0].edge[i] == -1)
                trie[0].edge[i] = 0;
            else
            {
                trie[trie[0].edge[i]].failLink = 0;
                Q.push(trie[0].edge[i]);
            }
        }
        while(!Q.empty())
        {
            int cur = Q.front();
            Q.pop();
            for(int i = 0; i<ALPHABET_SIZE; i++)
            {
                if(trie[cur].edge[i] != -1)
                {
                    int v = trie[cur].edge[i];
                    trie[v].failLink = trie[trie[cur].failLink].edge[i];
                    trie[v].counter += trie[trie[v].failLink].counter; /// change this line as you need
                    Q.push(v);
                }
                else
                {
                    trie[cur].edge[i] = trie[trie[cur].failLink].edge[i];
                }
            }
        }
    }

    /// The following traverse function checks if a text has at least one pattern as a substring
    /// change it as you need
    int traverse(string &text)
    {
        int len = text.length();
        int cur = 0;
        for(int i = 0; i<len; i++)
        {
            int nw = Rank[text[i]];
            cur = trie[cur].edge[nw];
            if(trie[cur].counter)
                return true;
        }
        return false;
    }

    int query(string &text)
    {
        return traverse(text);
        /// add whatever you need to do after traversing in the query
    }
};

struct dynamicAho{
    ahoCorasick ar[LOG];
    void add(string &pattern)
    {
        int myIdx = -1;
        for(int i = 0; i<LOG; i++)
        {
            if(ar[i].dictionary.size() == 0)
            {
                myIdx = i;
                break;
            }
        }
//        assert(myIdx != -1);
        ar[myIdx].init();
        ar[myIdx].add(pattern);
        for(int j = 0; j<myIdx; j++)
        {
            for(auto s: ar[j].dictionary)
                ar[myIdx].add(s);
            ar[j].Clear();
        }
        ar[myIdx].build();
    }

    int query(string &s)
    {
        for(int i=  0; i<LOG; i++)
        {
            if(ar[i].alive && ar[i].query(s))
                return true;
        }
        return false;
    }
}AC;
