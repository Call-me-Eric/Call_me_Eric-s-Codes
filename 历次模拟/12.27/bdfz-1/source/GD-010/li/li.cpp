#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m;
int in[200005];
int v[400005],nxt[400005];
int h[200005];
int vis[200005];
int cnt=1;
int f[4];
int s,ans;
void dfs(int nx)
{
	if(vis[nx])	return;
	vis[nx]=1;
	if(!in[nx])
	{
		if(s==0)	++ans;
		return;
	}
	f[min(in[nx],4ll)-1]++;
	for(int i=h[nx];i;i=nxt[i])
	{
		int to=v[i];
		if(!vis[to])	dfs(to);
	}
}
signed main()
{
	freopen("li.in","r",stdin);
	freopen("li.out","w",stdout);
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=m;i++)
	{
		int x,y;
		scanf("%lld%lld",&x,&y);
		in[x]++;
		in[y]++;
		v[++cnt]=y;
		nxt[cnt]=h[x];
		h[x]=cnt;
		v[++cnt]=x;
		nxt[cnt]=h[y];
		h[y]=cnt;
	}
	for(int i=1;i<=n;i++)
	{
		if(vis[i])	continue;
		f[0]=f[1]=f[2]=f[3]=0;
		dfs(i);
		if(f[0]==0&&f[1]==0&&f[2]==0&&f[3]==0)	continue;
		if(f[2]==0&&f[3]==0)
		{
			if(f[0])
			{
				if(s==0)
				{
					ans+=(f[1]+3)*(f[1]+2)/2;
				}
			}
			else
			{
				if(s==0)
				{
					s=1;
					ans=0;
				}
				if(s==1)
				{
					ans+=f[1];
				}
			}
		}
		else if(f[0]==3&&f[1]==0&&f[2]==1&&f[3]==0)
		{
			if(s==0)
			{
				s=1;
				ans=0;
			}
			if(s==1)
			{
				ans+=3;
			}
		}
		else
		{
			s=-1;
		}
	}
	if(~s)	cout<<s<<' '<<ans<<'\n';
	else	cout<<"-1\n";
	return 0;
}
