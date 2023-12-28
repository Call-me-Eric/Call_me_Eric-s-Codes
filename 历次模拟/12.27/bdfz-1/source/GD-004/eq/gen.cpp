#include<bits/stdc++.h>
#define rep(i,a,b) for (int i=(a);i<=(b);i++)
#define drep(i,a,b) for (int i=(a);i>=(b);i--)
using namespace std;
typedef long long ll;
inline void setfile()
{
	#ifndef pbtxdy
	freopen("eq.in","r",stdin);
	freopen("eq.out","w",stdout);
	#endif
}

const int mod=998244353;
inline int qmo(int x){return x+((x>>31)&mod);}
inline int add(int x,int y){return qmo(x+y-mod);}
inline int sub(int x,int y){return qmo(x-y);}
inline void inc(int &x,int y){x=add(x,y);}
inline void dec(int &x,int y){x=sub(x,y);}
inline int quick_pow(int x,int k){int res=1; for (;k;k>>=1,x=1ll*x*x%mod) if (k&1) res=1ll*res*x%mod; return res;}

mt19937 rng(time(0)^rand()^(*(new int)));
inline int rnd(int l,int r){return l+((rng()%(r-l+1)));}

int main()
{
	ios::sync_with_stdio(false),cin.tie(0);

	int n=700,q=700;
	printf("%d %d\n",n,q);
	rep(i,1,n)
	{
		rep(j,0,n) printf("%d ",rnd(0,mod-1));
		printf("\n");
	}
	rep(i,1,q)
	{
		printf("%d ",rnd(1,n));
		rep(j,0,n) printf("%d ",rnd(0,mod-1));
		printf("\n");
	}

	return 0;
}