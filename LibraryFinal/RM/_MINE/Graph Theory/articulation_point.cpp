
//Articulation Point
VI edge[MAX+10];
int AP[MAX+10], d[MAX+10], vis[MAX+10],tm, low[MAX+10];
// tm = 0, memset(AP,0), memset(vis,0)
// call for every not visited not with dfs(index,-1)

void dfs(int idx,int par)
{
	int i, cur, child = 0;
	vis[idx] = true;
	low[idx] = d[idx] = ++tm;

	for(i = 0; i < (int) edge[idx].size(); i++)
	{
		cur = edge[idx][i];
		if(cur == par) continue;

		if(vis[cur]) low[idx] = min(low[idx], d[cur]);
		else
		{
			child++;
			dfs(cur,idx);
			low[idx] = min(low[idx], low[cur]);
			if(par != -1 && low[cur] >= d[idx]) AP[idx]++;
		}
	}
	if(par == -1 && child > 1) AP[idx] = child;
}
