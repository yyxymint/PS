#include <bits/stdc++.h>

using namespace std;

struct DS{
	vector<int> par, rank, size;
	DS(int n) : par(n), rank(n,1), size(n,1){
		for(int i=0;i<n;i++){
			par[i]=i;
			size[i]=1;
		}
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

int main(){
	DS ds(3005);
	ds.merge(1,2);
}
