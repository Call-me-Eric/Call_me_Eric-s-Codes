#include <bits/stdc++.h>
using namespace std;
vector<int> s,t;
int lim;
int res[12];
void dfs(vector<int> vc,int dep){
	if(dep>10)return;
	if(vc==t) ++res[dep];
	for(int i=1;i<lim;++i) if(vc[i]<vc[i-1]) return;
	for(int i=0;i<lim;++i){
		vector<int> tmp=vc;
		if(tmp[i]){
			--tmp[i];
			dfs(tmp,dep+1);
		}
	}
	for(int i=0;i<lim;++i){
		vector<int> tmp=vc;
		++tmp[i];
		dfs(tmp,dep+1);
	}
}
int main(){
	freopen("young.in","r",stdin);
	freopen("young.out","w",stdout);
	int tc;
	scanf("%d",&tc);
	while(tc--){
		int n,m;
		s.clear();t.clear();
		scanf("%d",&n);
		for(int i=0;i<n;++i){
			int x;
			scanf("%d",&x);
			s.emplace_back(x);
		}
		scanf("%d",&m);
		for(int i=0;i<n;++i){
			int x;
			scanf("%d",&x);
			t.emplace_back(x);
		}
		dfs(s,0);
		int q;
		cin>>q;
		while(q--){
			int x;
			cin>>x;
			printf("%d\n",res[x]);
		}
	}
}
