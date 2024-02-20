#include<bits/stdc++.h>
#define ls (now<<1)
#define rs (now<<1|1)
#define mid ((l+r)>>1)
using namespace std;
typedef long long ll;
const int inf=1e9,N=2e5+10,M=N<<2;
struct Task{
	int n,m,tag[M],len[M],t[M],deg[N];
	vector<pair<int,int>> v[N];
	void Tag(int x){tag[x]^=1,t[x]=len[x]-t[x];}
	void update(int now)
	{
		t[now]=t[ls]+t[rs];
		if(tag[now]) t[now]=len[now]-t[now];
	}
	void modify(int l,int r,int now,int L,int R)
	{
		if(l>R||r<L) return;
		if(L<=l&&r<=R) return Tag(now);
		modify(l,mid,ls,L,R),modify(mid+1,r,rs,L,R);
		update(now);
	}
	void build(int l,int r,int now)
	{
		len[now]=r-l+1,tag[now]=t[now]=0;
		if(l==r) return;
		build(l,mid,ls),build(mid+1,r,rs);
		update(now);
	}
	void add(int i,int l,int r){v[i].push_back({l,r});}
	void solve(int n,int m,int p)
	{
		build(1,m,1);
		if(p) Tag(1);
		for(int i=1;i<=n;i++)
		{
			for(auto k:v[i]) modify(1,m,1,k.first,k.second);
			deg[i]=t[1];
		}
	}
}t1,t2;
namespace seg
{
	pair<int,int> t[M];
	int tag[M];
	void Tag(int x)
	{
		tag[x]^=1,swap(t[x].first,t[x].second);
	}
	void update(int now)
	{
		t[now]={max(t[ls].first,t[rs].first),max(t[ls].second,t[rs].second)};
		if(tag[now]) swap(t[now].first,t[now].second);
	}
	void modify(int l,int r,int now,int L,int R)
	{
		if(l>R||r<L) return;
		if(L<=l&&r<=R) return Tag(now);
		modify(l,mid,ls,L,R),modify(mid+1,r,rs,L,R);
		update(now);
	}
	void build(int l,int r,int now,int *a)
	{
		if(l==r) return t[now]={a[l],0},void();
		build(l,mid,ls,a),build(mid+1,r,rs,a);
		update(now);
	}
}
struct node{
	int x;
	ll y;
}s1[N],s2[N];
vector<int> v1[N],v2[N];
int ans1[N],ans2[N],n,m,Q,a[N],b[N],mx[N];
void work1(int x,int s){for(auto y:v1[x]) ans1[y]=s;}
void work2(int x,int s){for(auto y:v2[x]) ans2[y]=s;}
bool chk(int x,int y)
{
	int p=s1[x].x,q=s2[y].x;
	long long sum=s1[x].y+s2[y].y;
	return sum==1ll*p*q;
}
int main()
{
	freopen("graph.in","r",stdin);
	freopen("graph.out","w",stdout);
	scanf("%d%d%d",&n,&m,&Q);
	for(int i=1,x1,y1,x2,y2;i<=Q;i++)
	{
		scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
		t1.add(x1,y1,y2);
		t1.add(x2+1,y1,y2);
		t2.add(y1,x1,x2);
		t2.add(y2+1,x1,x2);
	}
	t1.solve(n,m,0),t2.solve(m,n,1);
	for(int i=1;i<=n;i++) v1[a[i]=t1.deg[i]].push_back(i);
	for(int i=1;i<=m;i++) v2[b[i]=t2.deg[i]].push_back(i);
	for(int i=0;i<=m;i++)
	{
		int x=v1[i].size();
		s1[i]=node{x,1ll*x*i};
		if(i) s1[i].x+=s1[i-1].x,s1[i].y+=s1[i-1].y;
	}
	for(int i=0;i<=n;i++)
	{
		int x=v2[i].size();
		s2[i]=node{x,1ll*x*i};
		if(i) s2[i].x+=s2[i-1].x,s2[i].y+=s2[i-1].y;
	}
	seg::build(1,m,1,b);
	for(int i=1;i<=n;i++)
	{
		for(auto k:t1.v[i])
			seg::modify(1,m,1,k.first,k.second);
		mx[a[i]]=max(mx[a[i]],seg::t[1].second);
	}
	int X=0,Y=0,sum=v1[0].size()+v2[0].size();
	for(int i=1;i<=n;i++) if(a[i]==0) ans1[i]=1;
	for(int i=1;i<=m;i++) if(b[i]==0) ans2[i]=1;
	while(X<m)
	{
		while(Y<n&&chk(X,Y+1)) Y++,work2(Y,sum+1),sum+=v2[Y].size();
		int x=X+1,y=max(Y,mx[x]);
		while(!chk(x,y))
			x++,y=max(y,mx[x]);
		if(y==Y)
		{
			for(int i=X+1;i<=x;i++) work1(i,sum+1);
			for(int i=X+1;i<=x;i++) sum+=v1[i].size();
		}
		else
		{
			for(int i=X+1;i<=x;i++) sum+=v1[i].size();
			for(int i=Y+1;i<=y;i++) sum+=v2[i].size();
			for(int i=X+1;i<=x;i++) work1(i,sum);
			for(int i=Y+1;i<=y;i++) work2(i,sum);
		}
		X=x,Y=y;
	}
	for(int i=1;i<=n;i++) printf("%d ",ans1[i]);
	for(int i=1;i<=m;i++) printf("%d%c",ans2[i]," \n"[i==m]);
}