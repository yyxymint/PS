#include <bits/stdc++.h>

using namespace std;

int V,E;
vector<pair<int,int> > adj[505];

vector<int> BF(int src){
	vector<int> upper(V+1, 987654321);
	upper[src] = 0;
	bool updated;
	for(int iter=0;iter<V;iter++){
		updated = false;
		for(int here=1;here<=V;here++)
			for(int i=0;i<adj[here].size();i++){
				int there = adj[here][i].first;
				int cost = adj[here][i].second;
				if(upper[here]!=987654321 && upper[there] > upper[here] + cost){
					upper[there] = upper[here] + cost;
					updated = true;
				}
			}
		if(!updated) break;
	}
	if(updated) upper.clear();
	return upper; 
}
 
int main(){
	scanf("%d%d",&V,&E);
	while(E--){
		int A,B,C;
		scanf("%d %d %d",&A,&B,&C);
		adj[A].push_back(make_pair(B,C));
		//A에서 B로 비용 C
	}
	vector<int> dist = BF(1);
	if(!dist.size()) return !printf("-1");
	for(int i=2;i<V+1;i++) printf("%d\n",dist[i]!=987654321?dist[i]:-1);
	//음수 사이클이 존재해서 무한히 감소 가능하면 INF

}
