#include<bits/stdc++.h>
using namespace std;
int r,g,b,n,m;
int S,T,R,G,B;
int cnt=1;
int v[1000006],w[1000006],nxt[1000006],h[100005];
bool vis[100005];
int cn;
void add(int x,int y,int z)
{
	v[++cnt]=y;
	w[cnt]=z;
	nxt[cnt]=h[x];
	h[x]=cnt;

	v[++cnt]=x;
	w[cnt]=0;
	nxt[cnt]=h[y];
	h[y]=cnt;
}
int dis[100005],ans;
int dl[100005],head,tail;
int dfs(int nx,int mx)
{
	if(nx==T)
	{
		ans+=mx;
		return mx;
	}
	int used=0;
	for(int i=h[nx];i;i=nxt[i])
	{
		if(w[i]==0)	continue;
		if(dis[v[i]]!=dis[nx]+1)	continue;
		int tmp=dfs(v[i],min(w[i],mx));
		used+=tmp;
		mx-=tmp;
		w[i]-=tmp;
		w[i^1]+=tmp;
		if(!mx)	break;
	}
	if(!used)	dis[nx]=1e9;
	return used;
}
void dinic()
{
	for(int i=1;i<=cn;i++)	dis[i]=1e9;
	dis[S]=0;
	head=tail=0;
	dl[++tail]=S;
	while(head<tail)
	{
		int nx=dl[++head];
		for(int i=h[nx];i;i=nxt[i])
		{
			if(w[i]==0)	continue;
			if(dis[v[i]]>dis[nx]+1)
			{
				dis[v[i]]=dis[nx]+1;
				dl[++tail]=v[i];
			}
		}
	}
	if(dis[T]==1e9)	return;
	dfs(S,1e9);
	dinic();
}
void dfs1(int nx)
{
	if(vis[nx])	return;
	vis[nx]=1;
	for(int i=h[nx];i;i=nxt[i])
	{
		if(w[i^1]==0)	continue;
		dfs1(v[i]);
	}
}
int an[100005];
int main()
{
	freopen("rgb.in","r",stdin);
	freopen("rgb.out","w",stdout);
	scanf("%d%d%d%d",&r,&g,&b,&m);
	n=r+g+b+1;
	S=n+1;
	T=S+1;
	R=T+1;
	G=R+1;
	B=G+1;
	cn=B;
	add(S,R,r);
	add(S,G,g);
	add(S,B,b);
	for(int i=1;i<=n;i++)	add(i,T,1);
	for(int i=1;i<=m;i++)
	{
		int x,y;
		char c;
		scanf("%d%d %c",&x,&y,&c);
		if(c=='r')
		{
			++cn;
			add(R,cn,1);
			an[i]=cnt;
			add(cn,x,1);
			add(cn,y,1);
		}
		if(c=='g')
		{
			++cn;
			add(G,cn,1);
			an[i]=cnt;
			add(cn,x,1);
			add(cn,y,1);
		}
		if(c=='b')
		{
			++cn;
			add(B,cn,1);
			an[i]=cnt;
			add(cn,x,1);
			add(cn,y,1);
		}
	}
	dinic();
	if(ans!=n-1)
	{
		cout<<"NO\n";
		return 0;
	}
	dfs1(T);
	for(int i=1;i<=n;i++)
	{
		if(!vis[i])
		{
			cout<<"NO\n";
			return 0;
		}
	}
	cout<<"YES\n";
	for(int i=1;i<=m;i++)	cout<<w[an[i]];
	return 0;
}
