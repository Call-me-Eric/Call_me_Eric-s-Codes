#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n,a[N];
struct node{
	int nxt,to,w;
}e[N];
int head[N],cnt;
void add(int u,int v,int w){
	e[++cnt].to=v;e[cnt].w=w;e[cnt].nxt=head[u];head[u]=cnt;
}
int b[N],ans;
void dfs(int u,int fa)
{
	//cout<<u<<" "<<fa<<endl;
	for(int i=head[u];i;i=e[i].nxt)
	{
		int v=e[i].to,w=e[i].w;
		if(v==fa) continue;
		if(b[u]-w>=0)
		{
			ans++;
			b[v]=b[u]-w+a[v];
			dfs(v,u);
		}
	}
}
int main()
{
	freopen("transport.in","r",stdin);
	freopen("transport.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1,u,v,w;i<n;i++) 
	{
		scanf("%d%d%d",&u,&v,&w);
		add(u,v,w);add(v,u,w);
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++) b[j]=0;
		b[i]=a[i];dfs(i,0);
	}
	cout<<ans<<endl;
	return 0;
}
	
