/// 2 SAT (1 based index for variables)
/// Each variable can have two possible values (true or false)
/// Variables must satisfy a system of constraints on pairs of variables

namespace sat{
    bool visited[MAX * 2];
    vector <int> adj[MAX * 2], rev[MAX * 2];
    int n, m, l, dfs_t[MAX * 2], order[MAX * 2], parent[MAX * 2];

    inline int neg(int x){
        return ((x) <= n ? (x + n) : (x - n));
    }

    /// Call init once
    void init(int nodes){
        n = nodes, m = nodes * 2;
        for (int i = 0; i < MAX * 2; i++){
            adj[i].clear();
            rev[i].clear();
        }
    }

    inline void add_edge(int a, int b){
        adj[neg(a)].push_back(b);
        rev[b].push_back(neg(a));
    }


    /// Adds constraint on a and b so that either a or b (or both) must be true
    /// Negative values means not

    /// For example:
    /// either a or b true: add_constraint(a, b)
    /// either a or b false: add_constraint(-a, -b)
    /// either a or b true but not both: add_constraint(a, b), add_constraint(-a, -b)

    inline void add_constraint(int a, int b){
        if (a < 0) a = n - a;
        if (b < 0) b = n - b;

        add_edge(a, b);
        add_edge(b, a);
    }

    inline void add_implication(int a, int b){
        add_constraint(-a, b);
    }


    /// a or b (-x implies !x)
    inline void add_or(int a, int b){
        add_constraint(a, b);
    }

    /// a xor b (-x implies !x)
    inline void add_xor(int a, int b){
        add_constraint(a, b);
        add_constraint(-a, -b);
    }

    /// a and b (-x implies !x)
    inline void add_and(int a, int b){
        add_constraint(a, b);
        add_constraint(a, -b);
        add_constraint(-a, b);
    }

    /// force variable a to be true (if a is negative, force !a to be true)
    inline void force_true(int a){
        if (a < 0) a = n - a;
        adj[neg(a)].push_back(a);
        rev[a].push_back(neg(a));
    }

    /// force variable a to be false (if a is negative, force !a to be false)
    inline void force_false(int a){
        if (a < 0) a = n - a;
        adj[a].push_back(neg(a));
        rev[neg(a)].push_back(a);
    }

    inline void topsort(int i){
        visited[i] = true;
        int j, x, len = rev[i].size();

        for (j = 0; j < len; j++){
            x = rev[i][j];
            if (!visited[x]) topsort(x);
        }
        dfs_t[i] = ++l;
    }

    inline void dfs(int i, int p){
        parent[i] = p;
        visited[i] = true;
        int j, x, len = adj[i].size();

        for (j = 0; j < len; j++){
            x = adj[i][j];
            if (!visited[x]) dfs(x, p);
        }
    }

    void build(){
        int i, x;
        clr(visited);
        for (i = m, l = 0; i >= 1; i--){
            if (!visited[i]){
                topsort(i);
            }
            order[dfs_t[i]] = i;
        }

        clr(visited);
        for (i = m; i >= 1; i--){
            x = order[i];
            if (!visited[x]){
                dfs(x, x);
            }
        }
    }

    /// Returns true if the system is 2-satisfiable and returns the solution (nodes set to true) in vector res
    bool satisfy(vector <int>& res){
        build();
        clr(visited);

        for (int i = 1; i <= m; i++){
            int x = order[i];
            if (parent[x] == parent[neg(x)]) return false;

            if (!visited[parent[x]]){
                visited[parent[x]] = true;
                visited[parent[neg(x)]] = false;
            }
        }

        for (int i = 1; i <= n; i++){
            if (visited[parent[i]]) res.push_back(i);
        }
        return true;
    }
}
