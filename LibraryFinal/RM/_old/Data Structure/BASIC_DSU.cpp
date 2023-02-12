int color[MAX+5];
vector<int> edge[MAX+5];
int subsize[MAX+5];

int init(int idx, int p = -1){
    int ret = 1;
    for(auto x : edge[idx])
        if(x != p)
            ret += init(x, idx);
    return subsize[idx] = ret;
}

int freq[MAX+5];
LL sum[MAX+5];
/*
    freq[i] = number of times the color 'i' appeared
    sum[i] = sum of colors which appeared 'i' times
*/

void insert_all(int idx, int p){
    sum[freq[color[idx]]] -= color[idx];
    freq[color[idx]]++;
    sum[freq[color[idx]]] += color[idx];

    for(auto x : edge[idx])
        if(x != p)
            insert_all(x, idx, r);
}

void remove_all(int idx, int p){
    sum[freq[color[idx]]] -= color[idx];
    freq[color[idx]]--;
    sum[freq[color[idx]]] += color[idx];

    for(auto x : edge[idx])
        if(x != p)
            remove_all(x, idx);
}

void dfs(int idx, int p, bool keep){ ///returns the maximum frequency
    int bigchild = -1, mx = 0, ret = 0;
    for(auto x : edge[idx])
        if(x != p && subsize[x] > mx){
            mx = subsize[x];
            bigchild = x;
        }

    for(auto x : edge[idx])
        if(x != p && x != bigchild)
            dfs(x, idx, false);

    if(bigchild != -1) dfs(bigchild, idx, true);
    for(auto x : edge[idx])
        if(x != p && x != bigchild)
            insert_all(x, idx, ret);

    ///INSERTING IDX
    sum[freq[color[idx]]] -= color[idx];
    freq[color[idx]]++;
    sum[freq[color[idx]]] += color[idx];

    ///Answer your queries here
    if(!keep) remove_all(idx, p);
}
