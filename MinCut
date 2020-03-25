#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f;
const int CMAX = 1e7;
const int MAXN = 5050;

const int S=MAXN-4;
const int E=MAXN-2;

struct Edge{
	int to, c, f;
	Edge *dual;
	Edge(): Edge(-1, -1){}
	Edge(int to1, int c1): to(to1), c(c1), f(0), dual(nullptr){}
	int spare(){ return c-f; }
	void addFlow(int f1){
		f += f1;
		dual->f -= f1;
	}
};

vector<Edge*> adj[MAXN];

void add_edge(int u,int v,int d){
	if(d==0) d=INF;
	else d+=CMAX;
	Edge *e1 = new Edge(v,d), *e2 = new Edge(u, 0);
	e1->dual = e2; e2->dual = e1;
	adj[u].push_back(e1);
	adj[v].push_back(e2);
}

int MinCut(){
	int result = 0;
	while(1){
		bool visited[MAXN] = {0};
		visited[S] = true;
		Edge* path[MAXN];
		queue<int> Q;
		Q.push(S);

		while(!Q.empty()){
			int curr = Q.front();
			Q.pop();
			if(curr == E) break;
			for(Edge *e: adj[curr]){
				int next = e->to;
				if(!visited[next] && e->spare() > 0){
					visited[next] = true;
					path[next] = e;
					Q.push(next);
				}
			}
		}
		if(!visited[E]) break;

		int flow =  0x3f3f3f3f;
		for(int i=E; i!=S; i=path[i]->dual->to)
			flow = min(flow, path[i]->spare());
		for(int i=E; i!=S; i=path[i]->dual->to)
			path[i]->addFlow(flow);
		result += flow;
	}
	return result%CMAX;
}

int main(){
	add_edge(S,3,4);
	add_edge(3,E,2);
	printf("%d", MinCut());
}
