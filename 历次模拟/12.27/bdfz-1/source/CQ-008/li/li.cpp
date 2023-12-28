#include <iostream>
#define ll long long
#define no {cout<<"-1"<<endl;return 0;}
using namespace std;
const int maxn=2e5+5;
struct L{
	int v,bro;
}li[maxn<<1];
int n,m;
int head[maxn],cnt,du[maxn];
int vis[maxn],cntv,cnt3,sd,ps;
void add(int u,int v)
{
	li[++cnt].v=v;
	li[cnt].bro=head[u];
	head[u]=cnt;
	du[v]++;
}
void dfs(int u)
{
	vis[u]=1,ps++,sd+=du[u],cnt3+=(du[u]==3);
	for (int i=head[u];i;i=li[i].bro)
	{
		int v=li[i].v;
		if(vis[v]) continue;
		dfs(v);
	}
}
int main()
{
	freopen("li.in","r",stdin);
	freopen("li.out","w",stdout);
	cin>>n>>m;
	for (int i=1;i<=m;i++)
	{
		int u,v;
		cin>>u>>v;
		add(u,v);add(v,u);
	}
	ll ans=0,cal=0;
	for (int i=1;i<=n;i++)
	{
		if(du[i]>=4) no;
		if(du[i]<2&&!vis[i])
		{
			cnt3=sd=ps=0;
			dfs(i);
			if(cnt3>=2) no;
			if(cnt3&&sd/2!=3) no;
			if(cnt3) cal+=3;
			ans+=1ll*ps*(ps+1)/2;
			cntv+=ps;
		}
	}
	if(n-cntv+cal) cout<<"1 "<<n-cntv+cal<<endl;
	else cout<<"0 "<<ans<<endl;
	return 0;
}
