#include <bits/stdc++.h>
using namespace std;

int main(){
	freopen("li.in","r",stdin);
	freopen("li.out","w",stdout);
	int n,m; scanf("%d%d",&n,&m);
	vector <vector <int> > adj(n+1);
	for(int i=1; i<=m; i++){
		int u,v; scanf("%d%d",&u,&v);
		adj[u].emplace_back(v),adj[v].emplace_back(u);
	}
	vector <int> vis(n+1,0);
	int a=0; long long b=0;
	auto solve = [&](int i){
		vector <int> cur={i};
		vis[i]=1;
		int pos=0,edge=0,mxdeg=0;
		for(; pos<(int)cur.size(); pos++){
			int u=cur[pos];
			mxdeg=max(mxdeg,(int)adj[u].size());
			edge+=adj[u].size();
			for(int v:adj[u])
				if(!vis[v]) vis[v]=1,cur.emplace_back(v);
		}
		edge/=2;
		if(edge>n) puts("-1"),exit(0);
		if(edge==n){
			if(mxdeg==2) a+=cur.size();
			else puts("-1"),exit(0);
		}
		else{
			if(mxdeg<=2) b+=1ll*cur.size()*((int)cur.size()-1)/2;
			else if(edge==3) a+=edge;
			else puts("-1"),exit(0);
		}
	};
	for(int i=1; i<=n; i++)
		if(!vis[i]) solve(i);
	if(a) printf("1 %d\n",a);
	else printf("0 %lld\n",b);
	return 0;
}