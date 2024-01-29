#include<bits/stdc++.h>
using namespace std;
#define ls (k<<1)
#define rs (k<<1|1)
#define mid (l+r>>1)
#define int long long
const int N=1000010;
int m,tp,x,y,v,opt,lstans;
int s[N*4],lazy[N*4];
int mod=998244353; 
void pushup(int k)
{
    s[k]=(s[ls]%mod+s[rs]%mod)%mod;
    return ;
}
void build(int k,int l,int r)
{
    if(l==r){
        s[k]=0;
        return ;
    }
    build(ls,l,mid);
    build(rs,mid+1,r);
    pushup(k);
    return ;
}
void add(int k,int l,int r,int v)
{
    s[k]=s[k]+(r-l+1)*v%mod;
    lazy[k]=lazy[k]+v%mod;
}
void pushdown(int k,int l,int r)
{
    add(ls,l,mid,lazy[k]);
    add(rs,mid+1,r,lazy[k]);
    lazy[k]=0;
}
void pls(int k,int l,int r,int x,int y,int v)
{
    if(x<=l&&y>=r){
        add(k,l,r,v);
        return ;
    }
    pushdown(k,l,r);
    if(x<=mid) pls(ls,l,mid,x,y,v);
    if(y>mid) pls(rs,mid+1,r,x,y,v);
    pushup(k);
}
int query(int k,int l,int r,int x,int y)
{
    if(x<=l&&y>=r) return s[k]%mod;
    pushdown(k,l,r);
    int val=0;
    if(x<=mid) val=val+query(ls,l,mid,x,y)%mod;
    if(y>mid) val=val+query(rs,mid+1,r,x,y)%mod;
    pushup(k);
    return val;
}
signed main()
{
	freopen("maze.in","r",stdin);
	freopen("maze.out","w",stdout);
	scanf("%lld %lld",&m,&tp);
	lstans=0;
	build(1,1,N);
	while(m--)
	{
		scanf("%lld %lld %lld",&opt,&x,&y);
		if(opt==1)
		{
			scanf("%lld",&v);
			if(tp) x^=lstans,y^=lstans,v^=lstans;
		//	printf("lstans=%lld\n",lstans);
		//	printf("chg=%lld %lld %lld\n",l,r,v);
			pls(1,1,N,x,y,v);
		}
		if(opt==2)
		{
			if(tp) x^=lstans,y^=lstans;
		}
		if(opt==3)
		{
			if(tp) x^=lstans,y^=lstans;
		//	printf("lstans=%lld\n",lstans);
		//	printf("chg=%lld %lld\n",l,r);
			lstans=query(1,1,N,x,y)%mod;
			printf("%lld\n",lstans);
		} 
	}
	return 0;
}
