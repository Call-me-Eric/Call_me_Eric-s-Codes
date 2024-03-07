#include<bits/stdc++.h>
using namespace std;
const int N = 1e6+7;
int n,m,q;
int c[N];
int idx=0;struct dsu
{
	int fa[N],siz[N];
	int find(int x)
	{
		if(x==fa[x])return x;
		return fa[x]=find(fa[x]);
	}
	void merge(int x,int y)
	{
		if(find(x)==find(y))return;
		x=find(x);y=find(y);
		fa[x]=y;
		siz[y]+=siz[x];
	}
}A,B;
struct edge 
{
	int a,b,next,id;
}e[N];
const int M = 1e6+7;
int flink[M],t=0;
int get(int a,int b)
{
	int h=(1ll*a*131%M+b)%M;
	for(int i=flink[h];i;i=e[i].next)
	if(e[i].a==a&&e[i].b==b)return e[i].id;
	e[++t].a=a;
	e[t].b=b;
	e[t].id=++idx;
	e[t].next=flink[h];
	flink[h]=t;
	return idx;
}
int qry(int a,int b)
{
	int h=(1ll*a*131%M+b)%M;
	for(int i=flink[h];i;i=e[i].next)
	if(e[i].a==a&&e[i].b==b)return e[i].id;
	return 0;
}
#define PII pair<int,int>
#define mk(x,y) make_pair(x,y)
#define X(x) x.first
#define Y(x) x.second
typedef long long LL;
inline int read() {
	char ch = getchar(); int x = 0;
	while (!isdigit(ch)) {ch = getchar();}
	while (isdigit(ch)) {x = x * 10 + ch - 48; ch = getchar();}
	return x;
}
void write(LL x) {
	if (!x) return;
	write(x / 10); putchar(x % 10 + '0');
}
inline void print(LL x, char ch = '\n') {
	if (!x) putchar('0');
	else write(x);
	putchar(ch);
}
vector<int> E[N];
LL ans[N];
int U[N],V[N];
int seq[2*N],tot=0;
bool mark[N];
LL ext[N];
int vis[N],tag;
int main()
{
	freopen("tmp.in","r",stdin);
	freopen("ans.out","w",stdout);
	n = read(); q = read();
	for(int i=1;i<=n;i++)
	{
		c[i] = read();
		A.fa[i]=i;
		A.siz[i]=1;
	}
	for(int i=2;i<=n;i++)
	{
		int x;
		x = read();
		if(c[i]==c[x]) A.merge(x,i);
		else 
		{
			int cx=c[x],cy=c[i];
			if(cx>cy)swap(cx,cy);
			++m;
			U[m]=x;
			V[m]=i;
			E[get(cx,cy)].push_back(m);
		}
	}
	for(int i=1;i<=m;i++)
	{
		U[i]=A.find(U[i]);
		V[i]=A.find(V[i]);
		mark[U[i]]=1;
		mark[V[i]]=1;
	}
	for(int i=1;i<=n;i++)
	if(A.find(i)==i)
	ext[c[i]]+=1ll*A.siz[i]*A.siz[i];
	for(int r=1;r<=idx;r++)
	{
		tot=0;++tag; 
		for(auto p:E[r])
		{
			int x=U[p],y=V[p];
			if(vis[x]!=tag)vis[x]=tag,seq[++tot]=x;
			if(vis[y]!=tag)vis[y]=tag,seq[++tot]=y;
		}
		LL res=0;
		for(int i=1;i<=tot;i++)
		{
			B.fa[seq[i]]=seq[i];
			B.siz[seq[i]]=A.siz[seq[i]];
			res-=1ll*A.siz[seq[i]]*A.siz[seq[i]];
		}
		for(auto p:E[r])
		{
			int x=U[p],y=V[p];
			B.merge(x,y);
		}
		for(int i=1;i<=tot;i++)
		{
			int x=seq[i];
			if(B.find(x)==x)
			res+=1ll*B.siz[x]*B.siz[x];
		}
		ans[r]=res;
	}
	while(q--)
	{
		int x,y;
		x = read(); y = read();
		assert(x != y);
		if(x>y)swap(x,y);
		LL res=ext[x]+ext[y];
		if(qry(x,y))res+=ans[qry(x,y)];
		print(res);
	}
	return 0;
}
