
vector<int> edge[MAX+5];
vector<int> cost[MAX+5];
int par[MAX+5];
int far_subtree[MAX+5];
int upside[MAX+5];

const int INF = (MAX << 1);

void dfs(int idx, int p = -1){
    par[idx] = p;

    int i, x, w;
    for(i = 0; i < (int) edge[idx].size(); i++){
        x = edge[idx][i];
        if(x == p) continue;

        w = cost[idx][i];
        dfs(x, idx);
        far_subtree[idx] = max(far_subtree[idx], far_subtree[x] + w);
    }

    int mx = 0;
    for(i = 0; i < (int) edge[idx].size(); i++){
        x = edge[idx][i];
        if(x == p) continue;

        w = cost[idx][i];        upside[x] = max(upside[x], mx + w);
        mx = max(mx, far_subtree[x] + w);
    }

    mx = 0;
    for(i = (int) edge[idx].size() - 1; i >= 0; i--){
        x = edge[idx][i];
        if(x == p) continue;

        w = cost[idx][i];        upside[x] = max(upside[x], mx + w);
        mx = max(mx, far_subtree[x] + w);
    }
}

int dfs1(int idx, int p = -1){
    int i, x, w;

    for(i = 0; i < (int) edge[idx].size(); i++){
        x = edge[idx][i];
        if(x == p) continue;

        w = cost[idx][i];
        upside[x] = max(upside[x], upside[idx] + w);
        dfs1(x, idx);
    }
}
