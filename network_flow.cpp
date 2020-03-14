#include <bits/stdc++.h>

using namespace std;

const int MAXV = 400;
int S=MAXV-3;
int E=MAXV-5;

struct Edge {
	int t,c,f;
	Edge* rev;
	int r() const { return c - f; }
	void push(int amt){
		f += amt;
		rev->f -= amt;
	}
};

vector<Edge*> adj[MAXV];
void addEdge(int u, int v, int c){
	Edge* uv = new Edge(), *vu = new Edge();
	uv->t = v; uv->c = c; uv->f = 0; uv->rev = vu;
	vu->t = u; vu->c = 0; vu->f = 0; vu->rev = uv;
	adj[u].push_back(uv);
	adj[v].push_back(vu);
}

int networkflow(int s, int e){
	int ret = 0;
	while(1){
		vector<int> par(MAXV,-1);
		Edge* path[MAXV];
		queue<int> q;
		par[s] = s;
		q.push(s);
		while(!q.empty() && par[e] == -1){
			int here = q.front(); q.pop();
			for(int i=0; i<adj[here].size();i++){
				Edge* ed = adj[here][i];
				int there = ed->t;
				if(ed->r() > 0 && par[there] == -1) {
					q.push(there);
					par[there] = here;
					path[there] = ed;
				}
			}
		}
		if(par[e] == -1) break;
		int amt = 987654321;
		for(int p = e; p != s; p = par[p])
			amt = min(amt,path[p]->r());
		for(int p = e; p != s; p = par[p])
			path[p]->push(amt);
		ret += amt;
	}
	return ret;
}


int main(){
	addEdge(S,i,1);
	int p=networkflow(S,E);
}
