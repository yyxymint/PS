#include <bits/stdc++.h>

using namespace std;

vector<vector<int> > adj(105);
int aMatch[105],bMatch[105];
int visited[105];
int left_nodes,right_nodes;	

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
	for(int i=0;i<left_nodes;i++) aMatch[i]=-1;
	for(int i=0;i<right_nodes;i++) bMatch[i]=-1;
	for(int i=0;i<left_nodes;i++){
		for(int j=0;j<left_nodes;j++) visited[j]=0;
		if(dfs(i)) size++; 
	}
	return size;
}

//왼쪽 정점들의 크기 left_nodes, 오른쪽 right_nodes
//0번~left_nodes번이 0번~right_nodes번으로 최대매칭

int main(){
	int q;
	scanf("%d%d",&left_nodes,&q);
	right_nodes=left_nodes;
	while(q--){
		int a,b;
		scanf("%d%d",&a,&b);
		adj[a-1].push_back(b-1);		
	}
	printf("%d",BM());
}
