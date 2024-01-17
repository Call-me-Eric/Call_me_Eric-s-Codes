#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<bitset>
#include<random>
#include<cmath>
#include<ctime>
#include<queue>
#include<map>
#include<set>

#define int long long
#define fi first
#define se second
#define max Max
#define min Min
#define abs Abs
#define lc (x<<1)
#define rc (x<<1|1)
#define mid ((l+r)>>1)
#define pb(x) push_back(x)
#define lowbit(x) ((x)&(-(x)))
#define fan(x) ((((x)-1)^1)+1)
#define mp(x,y) make_pair(x,y)
#define clr(f,n) memset(f,0,sizeof(int)*(n))
#define cpy(f,g,n) memcpy(f,g,sizeof(int)*(n))
#define SZ(x) ((int)(x.size()))
#define INF 0x3f3f3f3f3f3f3f3f

using namespace std;

inline int read()
{
	int ans=0,f=1;
	char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){ans=(ans<<1)+(ans<<3)+c-'0';c=getchar();}
	return ans*f;
}

inline void write(int x)
{
	if(x<0) putchar('-'),x=-x;
	if(x/10) write(x/10);
	putchar((char)(x%10)+'0');
}

template<typename T>inline T Abs(T a){return a>0?a:-a;};
template<typename T,typename TT>inline T Min(T a,TT b){return a<b?a:b;}
template<typename T,typename TT> inline T Max(T a,TT b){return a<b?b:a;}

const int N=2e5+5;
int n,a[N];

struct Node
{
	int w[2][2];
	Node operator + (const Node &x)const
	{
		Node res;
		for(int i=0;i<2;++i)
			for(int j=0;j<2;++j)
			{
				res.w[i][j]=INF;
				for(int k=0;k<2;++k)
					res.w[i][j]=min(res.w[i][j],max(w[i][k],x.w[k][j]));
			}
		return res;
	}
};

struct Seg
{
	Node val[N<<2];
	void build(int x,int l,int r)
	{
		if(l==r)
		{
			val[x].w[0][0]=a[l];
			val[x].w[0][1]=(l==n?INF:a[l]+a[l+1]);
			val[x].w[1][0]=(l==1?INF:a[l]+a[l-1]);
			val[x].w[1][1]=INF;
			return;
		}
		build(lc,l,mid);
		build(rc,mid+1,r);
		val[x]=val[lc]+val[rc];
	}
	void update(int x,int l,int r,int p,Node v)
	{
		if(l==r)
		{
			val[x]=v;
			return;
		}
		if(p<=mid) update(lc,l,mid,p,v);
		else update(rc,mid+1,r,p,v);
		val[x]=val[lc]+val[rc];
	}
}sm;

struct node
{
	int l,r,w;
	bool operator < (const node &x)const
	{
		return w<x.w;
	}
};

vector<node> hv;

signed main()
{
	freopen("segment.in","r",stdin);
	freopen("segment.out","w",stdout);
	n=read();
	for(int i=1;i<=n;++i)
		a[i]=read();
	sm.build(1,1,n);
	for(int i=1;i<=n;++i)
	{
		hv.push_back((node){i,i,a[i]});
		if(i!=n) hv.push_back((node){i,i+1,a[i]+a[i+1]});
	}
	sort(hv.begin(),hv.end());
	int ans=sm.val[1].w[0][0];
	for(int i=0;i<SZ(hv);++i)
	{
		int l=hv[i].l,r=hv[i].r,w=hv[i].w;
		ans=min(ans,sm.val[1].w[0][0]-w);
		if(hv[i].l==hv[i].r)
		{
			Node tmp;
			tmp.w[0][0]=INF;
			tmp.w[0][1]=(l==n?INF:a[l]+a[l+1]);
			tmp.w[1][0]=(l==1?INF:a[l]+a[l-1]);
			tmp.w[1][1]=INF;
			sm.update(1,1,n,l,tmp);
		}
		else
		{
			Node tmp;
			tmp.w[1][0]=(l==1?INF:a[l]+a[l-1]);
			tmp.w[0][0]=tmp.w[0][1]=tmp.w[1][1]=INF;
			sm.update(1,1,n,l,tmp);
			tmp.w[0][0]=a[r];
			tmp.w[0][1]=(r==n?INF:a[r]+a[r+1]);
			tmp.w[0][0]=tmp.w[1][0]=tmp.w[1][1]=INF;
			sm.update(1,1,n,r,tmp);
		}
	}
	write(ans);
	return 0;
}
