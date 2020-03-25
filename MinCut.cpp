#include <bits/stdc++.h>

using namespace std;

const int MAXN=5050;
const int S=MAXN-2;
const int E=MAXN-1;
const int INF=1e9;

struct Edge{
    int to, c, f;
    Edge *dual;
    Edge(): Edge(-1, -1){}
    Edge(int to1, int c1): to(to1), c(c1), f(0), dual(nullptr){}
    int spare(){
        return c-f;
    }
    void addFlow(int f1){
        f += f1;
        dual->f -= f1;
    }
};

vector<Edge*> adj[MAXN], edge;

void add_edge(int u, int v, int c){
	if(c==0)
		c=INF;
    Edge *e1 = new Edge(v, c), *e2 = new Edge(u, 0);
    e1->dual = e2;
    e2->dual = e1;
    adj[u].push_back(e1);
    adj[v].push_back(e2);
    edge.push_back(e1);
    edge.push_back(e2);
}


int MinCut(){
	int result = 0;
    while(1){
        Edge *prev[MAXN] = {nullptr};
        queue<int> Q;
        Q.push(S);

        while(!Q.empty() && !prev[E]){
            int curr = Q.front();
            Q.pop();
            for(Edge *e: adj[curr]){
                int next = e->to;
                if(e->spare() > 0 && !prev[next]){
                    prev[next] = e->dual;
                    Q.push(next);
                }
            }
        }
        if(!prev[E]) break;

        int f = INF;
        for(int i = E; i != S; i = prev[i]->to)
            f = min(prev[i]->dual->spare(), f);
        for(int i = E; i != S; i = prev[i]->to)
            prev[i]->dual->addFlow(f);
        result += f;
    }
	return result;
}

int main(){
	add_edge(S,1,2);
	add_edge(S,2,4);
	add_edge(1,E,5);
	add_edge(2,E,1);

	printf("%d", MinCut());
}
