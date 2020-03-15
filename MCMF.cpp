#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1020;
const int S = MAXN-2;
const int E = MAXN-1;

struct MCMF {
    struct Edge {
        int v, c, d;
        int rev;
        Edge() {}
        Edge(int vv, int rr, int cc, int dd) :v(vv), rev(rr), c(cc), d(dd) {}
    };
    MCMF(int N) :size(N) { edge.resize(N); }
    int size;
    vector<vector<Edge> > edge;
    void add_edge(int u, int v, int c, int d) {
        edge[u].push_back(Edge(v, edge[v].size(), c, d));
        edge[v].push_back(Edge(u, edge[u].size() - 1, 0, -d));
    }
    pair<int,int> solve(const int src,const int sink) {
        int ret = 0;
        int tf=0;
        while(1){
            queue<int> q;
            vector<int> par(size, -1);
            vector<int> paridx(size, -1);
            vector<int> dist(size, 0x3f3f3f3f);
            vector<bool> inQ(size, false);

            dist[src] = 0;
            inQ[src] = true;
            q.push(src);
            while (!q.empty()) {
                int here = q.front(); q.pop();
                inQ[here] = false;
                
                for (int n = 0;n < edge[here].size();++n) {
                    int next = edge[here][n].v;
                    if (edge[here][n].c && dist[next] > dist[here] + edge[here][n].d) {
                        dist[next] = dist[here] + edge[here][n].d;
                        par[next] = here;
                        paridx[next] = n;
                        if (!inQ[next]) {
                            inQ[next] = true;
                            q.push(next);
                        }
                    }
                }
            }
            if (par[sink] == -1) break;
            int flow = 0x3f3f3f3f;
            for (int i = sink;i != src;i = par[i]) {
                flow = min(flow, edge[par[i]][paridx[i]].c);
            }
            for (int i = sink;i != src;i = par[i]) {
                edge[par[i]][paridx[i]].c -= flow;
                edge[i][edge[par[i]][paridx[i]].rev].c += flow;
                ret += (flow * edge[par[i]][paridx[i]].d);
            }
            tf += flow;
        }
        return make_pair(ret,tf);
    }
};

int main(){
	int v,e;
	scanf("%d%d",&v,&e);
	MCMF mcmf(MAXN+2);
	while(e--){
		int from,to,cost;
		scanf("%d%d%d",&from,&to,&cost);
		mcmf.add_edge(from,to,1,cost);
		mcmf.add_edge(to,from,1,cost);
	}
	mcmf.add_edge(S,1,2,0);
	mcmf.add_edge(v,E,2,0);
	//first는 비용 second는 유량
	pair<int,int> sss=mcmf.solve(S,E);
	printf("%d\n",sss.first);

}
