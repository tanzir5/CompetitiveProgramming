/// 1 based indexing
/// MAX is the highest number of nodes
/// returns true if there exists a negative cycle
/// otherwise returns false and calculates shortest path from src to all nodes
/// O(N*E)

/// famous bellman ford recurrence:
/// dist[v][k] = min(dist[v][k], dist[u][k-1] + cost of edge from u to v)
/// dist[v][k] is the minimum distance from source to v using exactly k edges.
/// where k is the number of edges used
/// so bellman ford can give shortest path from src to any node using (at most/ at least ) k edges
/// O(K*E) for a particular source
/// O(V*K*E) for APSP
/// O(V^3*log2(K)) if matrix expo is used in place of bellman ford

vector<pii> E[MAX+10];
const int inf = 1.5e9;
int dist[MAX+10];
bool bellman_ford(int src, int n)
{
    for(int i = 1; i<=n; i++)
        dist[i] = inf;
    dist[src] = 0;
    for(int i = 1; i<=n; i++)
    {
        for(int u = 1; u<=n; u++)
        {
            for(int j = 0; j<E[u].size(); j++)
            {
                int v = E[u][j].xx;
                int c = E[u][j].yy;
                if(dist[v] > dist[u]+c)
                {
                    dist[v] = dist[u]+c;
                    if(i == n)
                        return true;
                }
            }
        }
    }
    return false;
}

