#include <bits/stdc++.h>
using namespace std;
mt19937 rnd(22625025);
struct qwq
{
	int u,v,col,id;
}a[100005];
int lim[3];
int n,m;
int ans[100005];
struct qwq1
{
	int c[3];
	void ins(int id)
	{
		++c[a[id].col];
	}
	bool ck(int id)
	{
		return c[a[id].col]<lim[a[id].col];
	}
	void clr()
	{
		memset(c,0,sizeof c);
	}
}M1;
struct qwq2
{
	int fa[255];
	int ff(int x)
	{
		if(fa[x]==x) return x;
		return fa[x]=ff(fa[x]);
	}
	void ins(int id)
	{
		fa[ff(a[id].u)]=ff(a[id].v);
	}
	bool ck(int id)
	{
		return ff(a[id].u)!=ff(a[id].v);
	}
	void clr()
	{
		for(int i=1;i<=n;i++) fa[i]=i;
	}
}M2;
vector<int> u;
bitset<40005> in,ok1,ok2,vis;
vector<int> e[40005];
int fr[40005];
bool go()
{
	M1.clr(),M2.clr();
	in.reset();
	for(auto t:u) M1.ins(t),M2.ins(t),in[t]=1;
	ok1.reset(),ok2.reset();
	queue<int> q;
	for(int i=1;i<=m;i++)
	{
		if(M1.ck(i)) ok1[i]=1;
		if(M2.ck(i)) ok2[i]=1;
		if(ok1[i]&&ok2[i])
		{
			u.push_back(i);
			return 1;
		}
	}
	for(int i=1;i<=m;i++) e[i].clear();
	for(auto t:u)
	{
		M1.clr(),M2.clr();
		for(auto x:u)
			if(x!=t) M1.ins(x),M2.ins(x);
		for(int i=1;i<=m;i++)
		{
			if(in[i]) continue;
			if(M2.ck(i))
				e[i].push_back(t);
			if(M1.ck(i))
				e[t].push_back(i);
		}
	}
	vis=(ok1);
	for(int i=1;i<=m;i++)
		if(ok1[i]&&!in[i]) q.push(i);
	while(!q.empty())
	{
		int x=q.front();
		if(ok2[x])
		{
			while(!ok1[x])
				in.flip(x),x=fr[x];
			in.flip(x);
			u.clear();
			for(int i=1;i<=m;i++) if(in[i]) u.push_back(i);
			return 1;
		}
		q.pop();
		for(auto v:e[x])
			if(!vis[v]) q.push(v),fr[v]=x,vis[v]=1;
	}
	return 0;
}
signed main()
{
	freopen("rgb.in","r",stdin);
	freopen("rgb.out","w",stdout);
	cin >> lim[0] >> lim[1] >> lim[2] >> m;
	for(int i=1;i<=m;i++)
	{
		cin >> a[i].u >> a[i].v;
		a[i].id=i;
		char c;
		cin >> c;
		if(c=='r') a[i].col=0;
		else if(c=='g') a[i].col=1;
		else a[i].col=2;
	}
	shuffle(a+1,a+m+1,rnd);
	n=lim[0]+lim[1]+lim[2]+1;
	while((int)u.size()<n-1&&go());
	if(u.size()!=n-1)
	{
		cout << "NO\n";
		return 0;
	}
	cout << "YES\n";
	in.reset();
	for(auto t:u) in[a[t].id]=1;
	for(int i=1;i<=m;i++) cout << in[i];
	return 0;
}
/*

*/