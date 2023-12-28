#include<bits/stdc++.h>
using namespace std;
const int N=200005;
typedef long long ll;
int n,m,vis[N],mxd,cntc,cnte;ll ans0,ans1;
vector<int> G[N];
void dfs(int u)
{
	++cntc;mxd=max(mxd,(int)G[u].size());
	cnte+=(int)G[u].size();
	for(auto v:G[u])if(!vis[v])vis[v]=1,dfs(v);
}
int main()
{
	freopen("li.in","r",stdin);
	freopen("li.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1,u,v;i<=m;++i)
	{
		scanf("%d%d",&u,&v);
		G[u].push_back(v);G[v].push_back(u);
	}
	for(int i=1;i<=n;++i)if(!vis[i])
	{
		mxd=cntc=cnte=0;vis[i]=1;dfs(i);cnte/=2;
		if(cnte==cntc-1)
		{
			if(mxd>=4){return printf("-1"),0;}
			else if(mxd==3){if(cnte>3)return printf("-1"),0;else ans1+=cnte;}
			else ans0+=1ll*cntc*(cntc+1)/2;
		}
		else if(mxd>2){return printf("-1"),0;}
		else ans1+=cntc;
	}
	if(ans1)printf("1 %lld",ans1);else printf("0 %lld",ans0);
	return 0;
}