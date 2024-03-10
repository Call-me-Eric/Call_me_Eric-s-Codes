#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,a[1000010];
struct edge{int to,next,w;}e[1000010];
int tot,head[100010];
void add_edge(int u,int v,int w)
{
	e[tot].w=w;
	e[++tot].to=v;
	e[tot].next=head[u];
	head[u]=tot;
}
void SPFA(int 
signed main()
{
	freopen("transport.in","r",stdin);
	freopen("transport.out","w",stdout);
	scanf("%lld",&n);m=n-1;
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	for(int i=1;i<=m;i++)
	{
		int u,v,w;
		scanf("%lld%lld%lld",&u,&v,&w);
		add_edge(u,v,w);
		add_edge(v,u,w);
	}
	return 0;
}
