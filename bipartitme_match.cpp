#include <bits/stdc++.h>

using namespace std;

vector<vector<int> > adj(105);
int aMatch[105],bMatch[105];
int visited[105];
int n,m;	

int dfs(int a){
	if(visited[a]) return 0;
	visited[a]=1;
	for(int i=0;i<adj[a].size();i++){
		int b=adj[a][i];
		if(bMatch[b]==-1 || (!visited[bMatch[b]] && dfs(bMatch[b]))){
			aMatch[a]=b;
			bMatch[b]=a;
			return 1;
		}
	}
	return 0;
}

int BM(){
	int size=0;
	for(int i=0;i<n;i++) aMatch[i]=-1;
	for(int i=0;i<m;i++) bMatch[i]=-1;
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++) visited[j]=0;
		if(dfs(i)) size++; 
	}
	return size;
}

int main(){
	int q;
	scanf("%d%d",&n,&q);
	m=n;
	while(q--){
		int a,b;
		scanf("%d%d",&a,&b);
		adj[a-1].push_back(b-1);		
	}
	printf("%d",BM());
}
