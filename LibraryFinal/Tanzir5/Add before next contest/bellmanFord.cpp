/*
    Detects in O(VE) if there is a negative cycle reachable from given source.
    Run bellman taking every node as source to find if there exists any negative cycle in the graph in O(V^2*E).
    Also finds shortest distance to each node from the given source.
*/
#define MAX         ?
const double INF = 1e80;

struct edgeData{
    int u, v;
    double cost;
};
vector<edgeData>edge;
double dist[MAX+10];

/// cycleNodes will contain at least one node from a negative cycle if there is any after bellman finishes.

bool bellmanFord(int n, int source, vector<edgeData>&edge, vector<int>&cycleNodes)
{
    for(int i = 1; i<=n; i++)
        dist[i] = INF;
    dist[source] = 0;
    bool ret = false;
    for(int i = 1; i<=n; i++)
    {
        for(auto e: edge)
        {
            int u = e.u, v = e.v;
            LL cost = e.cost;
            if(dist[v] > dist[u] + e.cost + eps)
            {
                if(i == n)
                {
                    ret = true;
                    cycleNodes.push_back(v);
                }
                dist[v] = dist[u] + e.cost;

            }
        }
    }
    return ret;
}
