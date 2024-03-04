# include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,int> pli;
const ll INF=1e18;
int n,a[200010];
vector<int> G[200010];
void upd(ll &a,ll b){a=max(a,b);}
namespace sub1
{
	ll f[200010];
	int f_from[200010];
	vector<int> Ans;
	void dfs(int u,int fa)
	{
		for(int v:G[u])
		{
			if(v==fa) continue;
			dfs(v,u);
			if(f[v]>f[u]) f[u]=f[v],f_from[u]=v;
		}
		f[u]+=a[u];
	}
	int main()
	{
		dfs(1,0);
		cout<<f[1]<<endl;
		for(int u=1;u;u=f_from[u]) Ans.push_back(u);
		cout<<Ans.size()<<endl;
		for(int u:Ans) printf("%d ",u);
		return puts(""),0;
	}
}
namespace sub2
{
	ll f[200010],g[200010][2],s[200010];
	int fa[200010],f_from[200010],g_from1[200010],g_from2[200010];
	vector<int> Ans;
	void dfs1(int u)
	{
		pli mx={0,0};
		bool son=0;
		for(int v:G[u])
		{
			if(v==fa[u]) continue;
			fa[v]=u;dfs1(v);son=1;
			s[u]+=a[v];mx=max(mx,(pli){f[v]-a[v],v});
		}
		if(son) f[u]=s[u]+a[u]+mx.first,f_from[u]=mx.second;
		else f[u]=-INF;
	}
	void buildF(int u,bool rev)
	{
		if(rev)
		{
			for(int v:G[u])
				if(v!=fa[u] && v!=f_from[u]) Ans.push_back(v);
			if(f_from[u]) buildF(f_from[u],0);
			Ans.push_back(u);
		}
		else
		{
			Ans.push_back(u);
			if(f_from[u]) buildF(f_from[u],1);
			for(int v:G[u])
				if(v!=fa[u] && v!=f_from[u]) Ans.push_back(v);
		}
	}
	void dfs2(int u)
	{
		pli mx1={0,0},mx2={0,0},mx3={0,0};
		for(int v:G[u])
		{
			if(v==fa[u]) continue;
			pli t={f[v]-a[v],v};
			if(t>mx1) mx3=mx2,mx2=mx1,mx1=t;
			else if(t>mx2) mx3=mx2,mx2=t;
			else if(t>mx3) mx3=t;
		}
		for(int v:G[u])
		{
			if(v==fa[u]) continue;
			g[v][0]=g[v][1]=-INF;
			upd(g[v][0],max(g[u][0],g[u][1])+a[u]);
			ll w1,w2;
			if(mx1.second==v) g_from1[v]=mx2.second,w1=mx2.first,g_from2[v]=mx3.second,w2=mx3.first;
			else
			{
				g_from1[v]=mx1.second;w1=mx1.first;
				if(mx2.second==v) g_from2[v]=mx3.second,w2=mx3.first;
				else g_from2[v]=mx2.second,w2=mx2.first;
			}
			upd(g[v][0],g[u][0]+s[u]-a[v]+w1+a[u]);
			upd(g[v][1],max(g[u][0],g[u][1])+s[u]-a[v]+w1+a[u]);
			upd(g[v][1],g[u][0]+s[u]-a[v]+w1+w2+a[u]);
			dfs2(v);
		}
	}
	void buildG0(int),buildG1(int);
	void buildG0(int u)
	{
		assert(u>1);
		int v=fa[u],v1=g_from1[u];
		if(g[u][0]==max(g[v][0],g[v][1])+a[v])
		{
			if(g[v][0]>g[v][1]) buildG0(v);
			else buildG1(v);
			Ans.push_back(v);
		}
		else
		{
			ll w1=f[v1]-a[v1];
			assert(g[u][0]==g[v][0]+s[v]-a[u]+w1+a[v]);
			buildG0(v);
			for(int w:G[v])
				if(w!=fa[v] && w!=u && w!=v1) Ans.push_back(w);
			if(v1) buildF(v1,0);
			Ans.push_back(v);
		}
	}
	void buildG1(int u)
	{
		if(u==1) return;
		int v=fa[u],v1=g_from1[u],v2=g_from2[u];
		ll w1=f[v1]-a[v1],w2=f[v2]-a[v2];
		if(g[u][1]==max(g[v][0],g[v][1])+s[v]-a[u]+w1+a[v])
		{
			if(g[v][0]>g[v][1]) buildG0(v);
			else buildG1(v);
			Ans.push_back(v);
			if(v1) buildF(v1,1);
			for(int w:G[v])
				if(w!=fa[v] && w!=u && w!=v1) Ans.push_back(w);
		}
		else
		{
			assert(g[u][1]==g[v][0]+s[v]-a[u]+w1+w2+a[v]);
			buildG0(v);
			if(v1) buildF(v1,0);
			Ans.push_back(v);
			if(v2) buildF(v2,1);
			for(int w:G[v])
				if(w!=fa[v] && w!=u && w!=v1 && w!=v2) Ans.push_back(w);
		}
	}
	int main()
	{
		g[1][0]=-INF;dfs1(1);dfs2(1);
		pli ans={-INF,0};
		for(int u=2;u<=n;u++)
		{
			ll w=max(max(g[u][0],g[u][1])+a[u],g[u][0]+s[u]+f[f_from[u]]-a[f_from[u]]+a[u]);
			ans=max(ans,(pli){w,u});
		}
		cout<<ans.first<<endl;
		int u=ans.second;
		if(ans.first==max(g[u][0],g[u][1])+a[u])
		{
			if(g[u][0]>g[u][1]) buildG0(u);
			else buildG1(u);
			Ans.push_back(u);
		}
		else
		{
			buildG0(u);
			for(int v:G[u])
				if(v!=fa[u] && v!=f_from[u]) Ans.push_back(v);
			if(f_from[u]) buildF(f_from[u],0);
			Ans.push_back(u);
		}
		cout<<Ans.size()<<endl;
		for(int u:Ans) printf("%d ",u);
		return puts(""),0;
	}
}
namespace sub3
{
	vector<int> Ans;
	void dfs(int u,int fa,bool rev)
	{
		if(rev)
		{
			for(int v:G[u])
				if(v!=fa) dfs(v,u,0);
			Ans.push_back(u);
		}
		else
		{
			Ans.push_back(u);
			for(int v:G[u])
				if(v!=fa) dfs(v,u,1);
		}
	}
	int main()
	{
		ll sum=0;
		for(int i=1;i<=n;i++) sum+=a[i];
		cout<<sum<<endl;
		dfs(1,0,0);
		cout<<Ans.size()<<endl;
		for(int u:Ans) printf("%d ",u);
		return puts(""),0;
	}
}
int main()
{
	int K,u,v;
	cin>>n>>K;
	for(int i=1;i<n;i++)
	{
		scanf("%d%d",&u,&v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	if(K==1) sub1::main();
	else if(K==2) sub2::main();
	else sub3::main();
	return 0;
}