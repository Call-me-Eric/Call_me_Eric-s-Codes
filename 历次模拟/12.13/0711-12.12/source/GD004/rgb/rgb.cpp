#include<bits/stdc++.h>
#define rep(i,a,b) for (int i=(a);i<=(b);i++)
#define drep(i,a,b) for (int i=(a);i>=(b);i--)
typedef long long ll;
using namespace std;
inline void setfile()
{
	#ifndef pbtxdy
	freopen("rgb.in","r",stdin);
	freopen("rgb.out","w",stdout);
	#endif
}

const int N=520,M=N*N;

struct edge
{
	int u,v,col,id;
	ll w;
};
inline bool cmp(edge a,edge b){return a.w==b.w?a.col<b.col:a.w<b.w;}
inline edge ecmp(edge a,edge b){return cmp(a,b)?a:b;}

struct DSU
{
	int fa[N];
	inline void init(int size){iota(fa+1,fa+size+1,1);}
	int getfa(int x){return fa[x]==x?x:fa[x]=getfa(fa[x]);}
	inline void merge(int x,int y){fa[getfa(x)]=getfa(y);}
	inline bool same(int x,int y){return getfa(x)==getfa(y);}
}dsu;

int n,R,G,B,m,U[M],V[M],C[M];
vector<edge> es[3];
mt19937 rng(114514^rand()^(*(new int)));

vector<edge> merge(vector<edge> a,vector<edge> b)
{
	reverse(a.begin(),a.end());
	reverse(b.begin(),b.end());
	vector<edge> c;
	while (a.size()||b.size())
	{
		if (!a.size())
		{
			c.push_back(b.back());
			b.pop_back();
		}
		else if (!b.size())
		{
			c.push_back(a.back());
			a.pop_back();
		}
		else
		{
			if (cmp(a.back(),b.back()))
			{
				c.push_back(a.back());
				a.pop_back();		
			}
			else
			{
				c.push_back(b.back());
				b.pop_back();
			}
		}
	}
	return c;
}

array<int,3> kruskal(ll dg,ll db)
{
	vector<edge> nes[3];
	rep(i,0,2) nes[i]=es[i];
	for (auto &e:nes[1]) e.w+=dg;
	for (auto &e:nes[2]) e.w+=db;
	vector<edge> ee=merge(merge(nes[0],nes[1]),nes[2]);

	array<int,3> cnt={0,0,0};
	int ecnt=0;
	dsu.init(n);
	for (auto e:ee)
	{
		if (!dsu.same(e.u,e.v))
		{
			ecnt++;
			dsu.merge(e.u,e.v);
			cnt[e.col]++;
			if (ecnt==n-1) break;
		}
	}
	return cnt;
}

int work(ll dg)
{
	ll l=-5e9,r=5e9;
	while (l<r)
	{
		ll mid=(l+r)>>1;
		auto res=kruskal(dg,mid);
		if (res[2]>B) l=mid+1;
		else r=mid;
	}
	auto res=kruskal(dg,l);
	if (res[2]!=B)
	{
		#ifdef pbtxdy
		// printf("ahahaha GG! have %d %d %d\n",res[0],res[1],res[2]);
		#endif
		return 233;
	}

	if (res[1]>G) return 0;
	return 1;
}

bool find(ll dg)
{
	ll l=-5e9,r=5e9;
	while (l<r)
	{
		ll mid=(l+r)>>1;
		auto res=kruskal(dg,mid);
		if (res[2]>B) l=mid+1;
		else r=mid;
	}
	auto res=kruskal(dg,l);
	if (res[0]!=R||res[1]!=G||res[2]!=B) return 0;

	ll db=l;
	vector<edge> nes[3];
	rep(i,0,2) nes[i]=es[i];
	for (auto &e:nes[1]) e.w+=dg;
	for (auto &e:nes[2]) e.w+=db;
	vector<edge> ee=merge(merge(nes[0],nes[1]),nes[2]);

	vector<int> ans(m+1);
	
	int ecnt=0;
	dsu.init(n);
	for (auto e:ee)
	{
		if (!dsu.same(e.u,e.v))
		{
			ecnt++;
			dsu.merge(e.u,e.v);
			ans[e.id]=1;
			if (ecnt==n-1) break;
		}
	}

	#ifdef pbtxdy
	dsu.init(n);
	int cc[3]={0,0,0};
	rep(i,1,m) if (ans[i])
	{
		if (dsu.same(U[i],V[i]))
		{
			printf("NOT A TREE !\n");
			exit(0);
		}
		dsu.merge(U[i],V[i]);
		cc[C[i]]++;
	}
	if (cc[0]!=R||cc[1]!=G||cc[2]!=B)
	{
		printf("WRONG COLOR!\n");
		exit(0);
	}
	printf("spjok\n");

	#else
	printf("YES\n");
	rep(i,1,m) printf("%d",ans[i]);
	printf("\n");
	#endif

	return 1;
}

bool solve()
{
	rep(i,0,2) for (auto &e:es[i]) e.w=rng();
	rep(i,0,2) sort(es[i].begin(),es[i].end(),[&](auto a,auto b){return a.w<b.w;});

	ll l=-5e9,r=5e9;
	while (l<r)
	{
		ll mid=(l+r)>>1;
		int res=work(mid);
		if (res==233) return 0;
		if (res==0) l=mid+1;
		else r=mid;
	}
	if (find(l)) return 1;
	return 0;
}

int main()
{
	setfile();
	ios::sync_with_stdio(false),cin.tie(0);

	cin>>R>>G>>B>>m; n=R+G+B+1;
	rep(i,1,m)
	{
		int u,v; char c; cin>>u>>v>>c;
		edge e;
		e.u=u,e.v=v;
		e.col=(c=='r')?0:(c=='g'?1:2);
		e.id=i;
		es[e.col].push_back(e);
		U[i]=u,V[i]=v,C[i]=e.col;
	}

	rep(i,1,10) if (solve()) return 0;
	printf("NO\n");

	return 0;
}