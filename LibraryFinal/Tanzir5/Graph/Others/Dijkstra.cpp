/// O((V+E)log2(V))
/*
    Min Priority queue
    priority_queue<int, vector<int>, greater <int> > q;
*/

/*
    In dijkstra, always remember this optimization.
    if(dist[pq.front().xx] < pq.front().yy)
        continue;
    You don't need to re-check with a worse distance for the same node
*/
