#pragma GCC optimize(2)
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int read()
{
	char ch;
	int s=1;
	while((ch=getchar())<'0' || ch>'9')
	  if(ch=='-')
	    s=-1;
	int res=ch-'0';
	while((ch=getchar())>='0' && ch<='9')
	  res=res*10+ch-'0';
	return res*s;
}
struct haha
{
	int next,to;
	int son,id,fa,deep,size,top,p;
	ll v;
}a[1000001];
int head[1000001],num=0,cnt=0;
struct Tree
{
	int l,r;
	ll v;
}tr[2000001];
int toa[1000001];
int sx[1000001];
int n,m;
void add(int aa,int bb)
{
	a[++num].to=bb;
	a[num].next=head[aa];
	head[aa]=num;
}
void dfs1(int u,int f,int dep)
{
	a[u].deep=dep;
	a[u].fa=f;
	a[u].size=1;
	int maxx=-1;
	for(int i=head[u];i;i=a[i].next)
	{
		int v=a[i].to;
		if(v==f)
		  continue;
		dfs1(v,u,dep+1);
		a[u].size+=a[v].size;
		if(a[v].size>maxx)
		{
			maxx=a[v].size;
			a[u].son=v;
		}
	}
}
void dfs2(int u,int topf)
{
	a[u].id=++cnt;
	toa[cnt]=u;
	a[u].top=topf;
	if(!a[u].son)
	  return;
	dfs2(a[u].son,topf);
	for(int i=head[u];i;i=a[i].next)
	{
		int v=a[i].to;
		if(v==a[u].fa || v==a[u].son)
		  continue;
		dfs2(v,v);
	}
}
int cmp(int aa,int bb)
{
	return  a[aa].p<a[bb].p;
}
int root[1000001];
int build(int l,int r)
{
	int k=++num;
	if(l!=r)
	{
		int mid=l+r>>1;
		tr[k].l=build(l,mid);
		tr[k].r=build(mid+1,r);
	}
	return k;
}
int change(int k,int l,int r,int x,int v)
{
	tr[++num]=tr[k];
	k=num;
	if(l==r)
	{
		tr[k].v=v;
		return k;
	}
	int mid=l+r>>1;
	if(x<=mid)
	  tr[k].l=change(tr[k].l,l,mid,x,v);
	else
	  tr[k].r=change(tr[k].r,mid+1,r,x,v);
	tr[k].v=tr[tr[k].l].v+tr[tr[k].r].v;
	return k;
}
ll query(int k,int l,int r,int x,int y)
{
	if(l>=x && r<=y)
	  return tr[k].v;
	int mid=l+r>>1;
	if(y<=mid)
	  return query(tr[k].l,l,mid,x,y);
	if(x>=mid+1)
	  return query(tr[k].r,mid+1,r,x,y);
	return query(tr[k].l,l,mid,x,y)+query(tr[k].r,mid+1,r,x,y);
}
ll ask(int x,int y,int kk)
{
	ll ans=0;
	while(a[x].top!=a[y].top)
	{
		if(a[a[x].top].deep<a[a[y].top].deep)
		  swap(x,y);
		ans+=query(root[kk],1,n,a[a[x].top].id,a[x].id);
		x=a[a[x].top].fa;
	}
	if(a[x].deep>a[y].deep)
	  swap(x,y);
	ans+=query(root[kk],1,n,a[x].id,a[y].id);
	return ans;
}
int main()
{
	freopen("war.in","r",stdin);
	freopen("war.out","w",stdout);
	n=read(),m=read();
	for(int i=1;i<n;i++)
	{
		int aa=read(),bb=read();
		add(bb,aa);
		add(aa,bb);
	}
	for(int i=1;i<=n;i++)
	  a[i].p=read(),a[i].v=read();
	for(int i=1;i<=n;i++)
	  sx[i]=i;
	sort(sx+1,sx+n+1,cmp);
	dfs1(1,0,1);
	dfs2(1,1);
	num=0;
	root[0]=build(1,n);
	for(int i=1;i<=n;i++)
	  root[i]=change(root[i-1],1,n,a[sx[i]].id,a[sx[i]].v);
	for(int i=1;i<=m;i++)
	{
		int aa=read(),bb=read(),cc=read();
		int l1=0,r1=n,now=-1;
		while(l1<=r1)
		{
			int mid=l1+r1>>1;
			if(ask(aa,bb,mid)>=cc)
			  now=mid,r1=mid-1;
			else
			  l1=mid+1;
		}
		if(now!=-1)
		  printf("%d\n",a[sx[now]].p);
		else
		  printf("Impossible\n");
	}
}
