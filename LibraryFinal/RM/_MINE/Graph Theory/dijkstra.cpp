
//Dijkstra

vector<int> edge[MAX+10], cost[MAX+10];
int dist[MAX+10];

struct node{
    int idx, dt;
    node(){};
    node(int i, int d) {idx = i, dt = d;}
};

bool operator < (const node &a, const node &b) {return (a.dt > b.dt);}
priority_queue <node> Q;

void dijkstra(node src)
{
    memset(dist, -1, sizeof(dist));

    node nw;
    int i, u, v, c;

    dist[src.idx] = src.dt = 0;
    Q.push(src);
    while(!Q.empty())
    {
        nw = Q.top(); Q.pop();
        u = nw.idx;

        for(i = 0; i< (int) edge[u].size(); i++)
        {
            v = edge[u][i];
            c = cost[u][i];
            if(dist[v] == -1 || dist[v] > dist[u] + c) dist[v] = dist[u] + c, Q.push(node(v, dist[u]+c));
        }
    }

    return;
}
