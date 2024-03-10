#include <bits/stdc++.h>
using namespace std;
#define int long long

const int maxn=1e6+5;
int to[maxn],head[maxn],nxt[maxn],cnt,dep[maxn],a[maxn];
bool vis[maxn];

void add(int x,int y){to[++cnt]=y,nxt[cnt]=head[x],head[x]=cnt;}

void dfs(int x,int fa)
{
	dep[x]=dep[fa]+1;
	for(int i=head[x];i;i=nxt[i])
	{
		if(to[i]==fa) continue;
		dfs(to[i],x);
	}
}

signed main()
{
	freopen("router.in","r",stdin);
	freopen("router.out","w",stdout);
	int n;cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<n;i++)
	{
		int u,v;cin>>u>>v,add(u,v),add(v,u);
	}
	dfs(1,0);
	int maxdep=-114514,mdp=1;
	for(int i=1;i<=n;i++)
		if(dep[i]>maxdep) maxdep=dep[i],mdp=i;
	int ans=0;
//	ans+=a[to[mdp]];
	sort(a+1,a+n+1);
	if(n<=4) ans+=a[1]+a[2];
	else for(int i=1;i<=(maxdep-1)*2;i++) ans+=a[i];
	cout<<ans;
	return 0;
}
