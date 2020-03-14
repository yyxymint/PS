#include <bits/stdc++.h>

using namespace std;

int v,e,v_cnt=1,s_cnt=1;
int dist[20005];
int hisID[20005];
vector<vector<int> > tree(20005);
vector<vector<int> > id(20005);
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

int nega(int x){
	if(x%2){
		return x+1;
	}
	return x-1;
}

int main(){
	scanf("%d%d",&v,&e);
	while(e--){
		int a,b;
		scanf("%d%d",&a,&b);
		int a_m=(a>0);
		int b_m=(b>0);
		a=abs(a)*2;
		b=abs(b)*2;
		// a or b
		if(a_m && b_m){
			tree[nega(a)].push_back(b);
			tree[nega(b)].push_back(a);
		}

		if(a_m && !b_m){
			tree[nega(a)].push_back(nega(b));
			tree[b].push_back(a);	
		}

		if(!a_m && b_m){
			tree[a].push_back(b);
			tree[nega(b)].push_back(nega(a));
		}
		if(!a_m && !b_m){
			tree[a].push_back(nega(b));
			tree[b].push_back(nega(a));
		}
	}
	//정점개수*2 만큼
	for(int i=1;i<2*v+1;i++)
		if(!dist[i])
			scc(i);

	vector<pair<int,int> > li;

	int tf[20005]={};
	for(int i=1;i<2*v+1;i++){
		li.push_back(make_pair(hisID[i],i));
		tf[i]=-1;
	}
	sort(li.begin(),li.end());
	for(int i=1;i<v+1;i++){
		if(hisID[2*i]==hisID[2*i-1])
			return !printf("0");
	}
	printf("1\n");

	for(int i=li.size()-1;i>=0;i--){
		int now=li[i].second;
	
		if(tf[(1+now)/2]==-1){
			tf[(1+now)/2]=!((now+1)%2);
		}
	}
	for(int i=1;i<v+1;i++)
		printf("%d ",tf[i]);
}
