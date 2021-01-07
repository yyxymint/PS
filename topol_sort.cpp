#include <bits/stdc++.h>

using namespace std;

vector<vector<int> > v(1005); 
queue<int> q;
queue<int> ans;
int in[1005],did[1005];
int n,m;

int main(){
    scanf("%d%d",&n,&m);
    while(m--){
        int q,left,right;
        scanf("%d%d",&q,&left);
        q--;
        while(q--){
            scanf("%d",&right);
            in[right]++;
            v[left].push_back(right);
            left=right;
        }
    }
    for(int i=1;i<n+1;i++)
        if(!in[i])
            q.push(i);

    while(q.size()){
        int now=q.front();
        ans.push(now);
        did[now]=1;
        for(int i=0;i<v[now].size();i++)
            if(!(--in[v[now][i]]))
                q.push(v[now][i]);
        q.pop();    
    }   
    for(int i=1;i<n+1;i++)
        if(!did[i]) return !printf("0");
    while(ans.size()){
        printf("%d\n",ans.front());
        ans.pop();
    }
}
