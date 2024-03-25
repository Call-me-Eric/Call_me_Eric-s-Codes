#include<bits/stdc++.h>
using namespace std;

#define int long long
int n,m;
int cnt,head[400010],to[400010],nex[400010],val[4000010];
int idx,fa[2000010],son[2000010],top[2000010],dep[2000010],dfn[2000010],siz[2000010],tmp[2000010],w[2000010];
int sumn[200010<<2],maxn[200010<<2],minn[200010<<2],lz[200010<<2];
struct node
{
	int x,y;
}id[2000010];

void add(int x,int y,int w)
{
	nex[++cnt]=head[x];
	to[cnt]=y;
	val[cnt]=w;
	head[x]=cnt;
}

void dfs1(int x,int f)
{
	dep[x]=dep[f]+1;
	fa[x]=f;
	siz[x]=1;
	for(int i=head[x];i;i=nex[i])
	{
		int v=to[i];
		if(v==f)
		{
			continue;
		}
		dfs1(v,x);
		tmp[v]=val[i];
		siz[x]+=siz[v];
		if(siz[son[x]]<siz[v])
		{
			son[x]=v;
		}
	}
}

void dfs2(int x,int topf)
{
	dfn[x]=++idx;
	w[idx]=tmp[x];
	top[x]=topf;
	if(son[x])
	{
		dfs2(son[x],topf);
	}
	for(int i=head[x];i;i=nex[i])
	{
		int v=to[i];
		if(top[v])
		{
			continue;
		}
		dfs2(v,v);
	}
	return ;
}

void pushup(int rt)
{
	sumn[rt]=sumn[rt<<1]+sumn[rt<<1|1];
	maxn[rt]=max(maxn[rt<<1],maxn[rt<<1|1]);
	minn[rt]=min(minn[rt<<1],minn[rt<<1|1]);
}

void build(int rt,int l,int r)
{
	if(l==r)
	{
		sumn[rt]=maxn[rt]=minn[rt]=w[l];
		return ;
	}
	int mid=(l+r)>>1; 
	build(rt<<1,l,mid);
	build(rt<<1|1,mid+1,r);
	pushup(rt);
}

void pushdown(int rt)
{
	lz[rt<<1]^=1;
	lz[rt<<1|1]^=1;
	sumn[rt<<1]=-sumn[rt<<1];
	sumn[rt<<1|1]=-sumn[rt<<1|1];
	maxn[rt<<1]=-maxn[rt<<1];
	maxn[rt<<1|1]=-maxn[rt<<1|1];
	minn[rt<<1]=-minn[rt<<1];
	minn[rt<<1|1]=-minn[rt<<1|1];
    swap(minn[rt<<1|1],maxn[rt<<1|1]);
    swap(minn[rt<<1],maxn[rt<<1]);
	lz[rt]=0;
}

void update(int rt,int l,int r,int q,int k)
{
	if(l==r)
	{
		sumn[rt]=maxn[rt]=minn[rt]=k;
		return ;
	}
	if(lz[rt])
	{
		pushdown(rt);
	}
	int mid=(l+r)>>1;
	if(q<=mid)
	{
		update(rt<<1,l,mid,q,k);
	}
	else
	{
		update(rt<<1|1,mid+1,r,q,k);
	}
	pushup(rt); 
}

void change(int rt,int l,int r,int L,int R)
{
	if(L<=l&&r<=R)
	{
		lz[rt]^=1;
		sumn[rt]=-sumn[rt];
		maxn[rt]=-maxn[rt];
		minn[rt]=-minn[rt];
		swap(maxn[rt],minn[rt]);
		return ;
	}
	if(lz[rt])
	{
		pushdown(rt);
	}
	int mid=(l+r)>>1;
	if(L<=mid)
	{
		change(rt<<1,l,mid,L,R);
	}
	if(R>mid)
	{
		change(rt<<1|1,mid+1,r,L,R);
	}
	pushup(rt);
}

int qsum(int rt,int l,int r,int L,int R)
{
	int res=0;
	if(L<=l&&r<=R)
	{
		return sumn[rt];
	}
	if(lz[rt])
	{
		pushdown(rt);
	}
	int mid=(l+r)>>1;
	if(L<=mid)
	{
		res+=qsum(rt<<1,l,mid,L,R);
	}
	if(R>mid)
	{
		res+=qsum(rt<<1|1,mid+1,r,L,R);
	}
	pushup(rt);
	return res;
}

int qmax(int rt,int l,int r,int L,int R)
{
	int res=-1e10;
	if(L<=l&&r<=R)
	{
		return maxn[rt];
	}
	if(lz[rt])
	{
		pushdown(rt);
	}
	int mid=(l+r)>>1;
	if(L<=mid)
	{
		res=max(res,qmax(rt<<1,l,mid,L,R));
	}
	if(R>mid)
	{
		res=max(res,qmax(rt<<1|1,mid+1,r,L,R));
	}
	pushup(rt);
	return res;
}

inline int qmin(int rt,int l,int r,int L,int R){
	int res=2147483647;
	if(L<=l&&r<=R) return minn[rt];
	if(lz[rt]) pushdown(rt);
	int mid=(l+r)>>1;
	if(L<=mid) res=min(res,qmin(rt<<1,l,mid,L,R));
	if(R>mid)  res=min(res,qmin(rt<<1|1,mid+1,r,L,R));
	pushup(rt);
	return res;
}
//以上是线段树
//以下是树链剖分
void update(int x,int y)
{
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		change(1,1,n,dfn[top[x]],dfn[x]);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y]) swap(x,y);
	if(x!=y) change(1,1,n,dfn[x]+1,dfn[y]);
}

int qsum(int x,int y)
{
	int res=0;
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		res+=qsum(1,1,n,dfn[top[x]],dfn[x]);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y]) swap(x,y);
	if(x!=y) res+=qsum(1,1,n,dfn[x]+1,dfn[y]);
	return res;
}

int qmax(int x,int y)
{
	int res=-2147483647;
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		res=max(res,qmax(1,1,n,dfn[top[x]],dfn[x]));
		x=fa[top[x]];
	}
	if(dep[x]>dep[y]) swap(x,y);
	if(x!=y) res=max(res,qmax(1,1,n,dfn[x]+1,dfn[y]));
	return res;
}

int qmin(int x,int y)
{
	int res=2147483647;
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		res=min(res,qmin(1,1,n,dfn[top[x]],dfn[x]));
		x=fa[top[x]];
	}
	if(dep[x]>dep[y]) swap(x,y);
	if(x!=y) res=min(res,qmin(1,1,n,dfn[x]+1,dfn[y]));
	return res;
}
signed main()
{
	//freopen("1.in", "r", stdin);
	//freopen("ccc.out","w",stdout);
    cin>>n;
    for(int i=1;i<n;i++)
    {
    	int a,b,c;
    	cin>>a>>b>>c;
    	a++,b++;
    	add(a,b,c);
    	add(b,a,c);
    	id[i].x=a;
    	id[i].y=b;
	}
	dfs1(1,0);
	//cout<<1; 
	dfs2(1,1);
	//cout<<1;
	build(1,1,n);
	cin>>m;
	while(m--)
	{
		char s[10];
		int a,b;
		cin>>s;
		//cout<<s<<'\n';
		cin>>a>>b;
		if(s[0]=='C')
		{
			int mp;
			if(dep[id[a].x]>dep[id[a].y])
			{
				mp=id[a].x;
			}
			else
			{
				mp=id[a].y;
			}
			update(1,1,n,dfn[mp],b);
		}
		else if(s[0]=='N')
		{
			a++,b++;
			update(a,b);
		}
		else if(s[0]=='S')
		{
			a++,b++;
			cout<<qsum(a,b)<<endl;
		}
		else if(s[2]=='X')
		{
			a++;
			b++;
			cout<<qmax(a,b)<<endl;
		}
		else if(s[2]=='N')
		{
			a++;
			b++;
			cout<<qmin(a,b)<<endl; 
		}
	}
	return 0;
}

