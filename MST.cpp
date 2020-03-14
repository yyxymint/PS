#include <bits/stdc++.h>


using namespace std;

int V,E;
vector<vector<pair<int,int> > > adj(1005);
vector<pair<int,int> > edges;


struct DS{
	vector<int> par, rank, size;
	DS(int n) : par(n), rank(n,1), size(n,1){
		for(int i=0;i<n;i++)
			par[i]=i;
	}
	int find(int u){
		if(u == par[u]) return u;
		return par[u] = find(par[u]);
	}
	int merge(int u, int v){
		u = find(u); v = find(v);
		if(u == v) return size[v];
		if(rank[u] > rank[v]) swap(u,v);
		par[u] = v;
		if(rank[u] == rank[v]) ++rank[v];
		size[v] += size[u];
		return size[v];
	}
};

int kruskal(){
	int ret=0;
	edges.clear();
	vector<pair<int,pair<int,int> > > e;
	for(int u=1;u<V+1;u++){
		for(int i=0;i<adj[u].size();i++){
			int v = adj[u][i].first, cost = adj[u][i].second;
			e.push_back(make_pair(cost, make_pair(u,v)));
		}
	}
	sort(e.begin(),e.end());
	DS sets(V+1);
	for(int i=0;i<e.size();i++){
		int cost = e[i].first;
		int u = e[i].second.first, v = e[i].second.second;
		if(sets.find(u)==sets.find(v)) continue;
		sets.merge(u,v);
		edges.push_back(make_pair(u,v));
		ret += cost;
	}
	return ret;
}

int main(){		
	scanf("%d%d",&V,&E);
	for(int i=0;i<E;i++){
		int A,B,C;
		scanf("%d%d%d",&A,&B,&C);
		adj[A].push_back(make_pair(B,C));
	}
	printf("%d",kruskal()); 
}
