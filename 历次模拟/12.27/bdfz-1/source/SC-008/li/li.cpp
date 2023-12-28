#include <bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
int n,m,s,sv,se,mx,vis[N];
ll ans;
vector<int> e[N];
void dfs(int x){
	sv++;vis[x]=1;
	mx=max(mx,(int)e[x].size());
	for(int y:e[x]){
		se+=x<y;
		if(!vis[y]) dfs(y);
	}
}
int main(){
	freopen("li.in","r",stdin);
	freopen("li.out","w",stdout);
	cin>>n>>m;
	for(int u,v;m--;) cin>>u>>v,e[u].push_back(v),e[v].push_back(u);
	auto fuck=[&](){
		cout<<-1;
		exit(0);
	};
	for(int i=1;i<=n;i++) if(!vis[i]){
		mx=sv=se=0;
		dfs(i);
		if(se<sv){
			if(mx<3){
				if(!s) ans+=sv*(sv+1ll)/2;
			}else if(mx==3&&sv==4){
				if(!s) s=1,ans=0;
				ans+=3;
			}else fuck();
		}else if(se==sv&&mx==2){
			if(!s) s=1,ans=0;
			ans+=sv;
		}else fuck();
	}
	cout<<s<<" "<<ans<<"\n";
	return 0;
}