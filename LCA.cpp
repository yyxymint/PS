#include <bits/stdc++.h>

using namespace std;

int par[100005][18],d[100005];
int visited[100005];
vector<int> tree[100005];

void dfs(int now){
	visited[now]=1;
	for(int i=0;i<tree[now].size();i++){
		int next = tree[now][i];
		if(visited[next]) continue;
		par[next][0] = now;
		d[next] = d[now]+1;
		dfs(next);
	}
}

int lca(int u, int v){
	if(d[u]<d[v]) swap(u,v);
	for(int i=18-1;i>=0;i--)
		if(d[u]-d[v] >= (1<<i))
			u = par[u][i];
	if(u == v) return u;
	for(int i=18-1;i>=0;i--)
		if(par[u][i]!=par[v][i])
			u = par[u][i], v = par[v][i];
	return par[u][0];
}

int main(){
	int n,m;
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		int a,b;
		scanf("%d%d",&a,&b);
		tree[a].push_back(b);
		tree[b].push_back(a);
	}
	dfs(1);

	for(int j=0;j<18-1;j++)
		for(int i=2;i<n+1;i++)
			par[i][j+1]=par[par[i][j]][j];
	scanf("%d",&m);
	while(m--){
		int a,b;	
		scanf("%d%d",&a,&b);
		printf("%d\n",lca(a,b));
	}
}
