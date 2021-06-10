#include <bits/stdc++.h>
#define NUM_OF_VERTEX 10005

using namespace std;

int v,e,v_cnt=1,s_cnt=1,ans;
int dist[NUM_OF_VERTEX];
int hisID[NUM_OF_VERTEX];
vector<vector<int> > tree(NUM_OF_VERTEX);
vector<vector<int> > id(NUM_OF_VERTEX);
stack<int> st;

int scc(int now){
	int ret=dist[now]=v_cnt++;
	st.push(now);
	for(int i=0;i<tree[now].size();i++){
		int there=tree[now][i];
		if(!dist[there])
			ret=min(ret,scc(there));
		else if(!hisID[there])
			ret=min(ret,dist[there]);
	}
	if(ret==dist[now]){
		while(1){
			int t=st.top();
			st.pop();
			hisID[t]=s_cnt;
			id[s_cnt].push_back(t);
			if(t==now) break;
		}
		s_cnt++;
	}
	return ret;
}

int main(){
	scanf("%d%d",&v,&e);
	while(e--){
		int from,to;
		scanf("%d%d",&from,&to);
		tree[from].push_back(to);
	}
	for(int i=1;i<v+1;i++)
		if(!dist[i])
			scc(i);
	int in[100005]={};
	vector<vector<int> > to(100005);
	for(int i=1;i<v+1;i++)
		for(int j=0;j<tree[i].size();j++)
			if(hisID[tree[i][j]]!=hisID[i]){
				to[hisID[i]].push_back(hisID[tree[i][j]]);
				in[hisID[tree[i][j]]]++;
			}

	for(int i=1;i<s_cnt;i++)
		if(!in[i])
			ans++;
	printf("%d\n",ans);
}
