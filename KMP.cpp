#include <bits/stdc++.h>

using namespace std;

vector<int> getpi(string N){
	int n = N.size();
	vector<int> pi(n,0);
	int match = 0;
	for(int i=1;i<n;i++){
		while(match > 0 && N[i] != N[match])
			match = pi[match-1];
		if(N[i] == N[match]){
			match++;
			pi[i] = match;
		}
	}
	return pi;
}

vector<int> kmp(string M, string N){
	int m = M.size(), n = N.size();
	vector<int> ret;
	vector<int> pi = getpi(N);
	int match = 0;
	for(int i=0;i<m;i++){
		while(match > 0 && M[i] != N[match])
			match = pi[match-1];
		if(M[i] == N[match]){
			match++;
			if(match == n){
				ret.push_back(i-n+1);
				match = pi[match-1];
			}
		}
	}
	return ret;
}

int main(){
	string t,p;
	getline(cin,t);
	getline(cin,p);
	vector<int> ans=kmp(t,p);
	printf("%d\n",ans.size());
	for(int i=0;i<ans.size();i++)
		printf("%d ",ans[i]+1);

}
