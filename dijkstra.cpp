#include <bits/stdc++.h>

#define INF 987654321

using namespace std;

int MAXN=50005;

vector<vector<pair<int,int> > > adj(MAXN);

vector<int> djk(int start){
	priority_queue<pair<int,int> ,vector<pair<int,int> >,greater<pair<int,int> > > pq;
	pq.push(make_pair(0,start));
	vector<int> dist(MAXN+1,INF);
	while(pq.size()){
		int cost=pq.top().first;
		int here=pq.top().second;
		pq.pop();
		if(dist[here]<cost) continue;
		for(int i=0;i<adj[here].size();i++){
			int next_cost=cost+adj[here][i].second;
			int next_visit=adj[here][i].first;
			if(dist[next_visit]>next_cost){
				dist[next_visit]=next_cost;
				pq.push(make_pair(next_cost,next_visit));
			}
		}
	}
	return dist;
}

int n,m;

int main(){
	scanf("%d%d",&n,&m);
	while(m--){
		int from,to,cost;
		scanf("%d%d%d",&from,&to,&cost);
		adj[from].push_back(make_pair(to,cost));
		adj[to].push_back(make_pair(from,cost));
	}
	int start,dest;
	scanf("%d%d",&start,&dest);
	vector<int> dist=djk(start);
	printf("%d",dist[dest]);
}
