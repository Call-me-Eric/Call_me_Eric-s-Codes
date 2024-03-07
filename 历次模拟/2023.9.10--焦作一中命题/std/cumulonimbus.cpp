#include<bits/stdc++.h>
using namespace std;
const int N = 18;
const int M = (1<<16)+7;
int mod;
struct FastMod
{
	using ull=unsigned long long;
	using L=__int128;
	ull b,m;
	void init(ull w)
	{
		b=w;
		m=ull((L(1)<<64)/b);
	}
	int red(ull a)
	{
		ull q=(ull)((L(m)*a)>>64),r=a-q*b;
		return r>=b?r-b:r;
	}
}F;
int Pow(int a,int b)
{
    int res=1;
    while(b)
    {
        if(b&1)res=F.red(1ll*res*a);
        a=F.red(1ll*a*a);
        b>>=1;
    }
    return res;
}
int n,m;
int A[N][N];
int f[M][2],lg[M],dp[M][2],h[M];//S,c
int E[M],I[M],cnt[M];
inline int get(int S,int T)
{
    if(cnt[S]-cnt[T]-cnt[S^T]>0) return 0;
    return F.red(1ll*F.red(1ll*I[T]*I[S^T])*E[S]);
}
void solve()
{
    scanf("%d %d %d",&n,&m,&mod);
    F.init(mod);
    int V=n+m;
    for(int S=0;S<(1<<V);S++)
    {
        cnt[S]=0;
        h[S]=0;
        f[S][0]=1,f[S][1]=0;
        dp[S][0]=dp[S][1]=0;
        E[S]=I[S]=1;
    }
    for(int i=1;i<=n;i++)
    for(int j=1;j<=m;j++)
    {
        int w;
        scanf("%d",&w);
        int S=((1<<(i-1))+(1<<(j+n-1)));
        int v=(1-w+mod)%mod;
        f[S][1]=w;
        f[S][0]=v;
        if(v==0)cnt[S]++;
        if(v==0)v=1;
        E[S]=v;
        I[S]=Pow(v,mod-2);
    }
    for(int i=1;i<=V;i++)
    for(int S=0;S<(1<<V);S++)
    if((S>>(i-1))&1)
    {
        int T=(S^(1<<(i-1)));
        int f0=f[S][0],f1=f[S][1];
        int g0=f[T][0],g1=f[T][1];
        f[S][0]=F.red(1ll*f0*g0+1ll*f1*g1);
        f[S][1]=F.red(1ll*f0*g1+1ll*f1*g0);
        E[S]=F.red(1ll*E[S]*E[T]);
        I[S]=F.red(1ll*I[S]*I[T]);
        cnt[S]+=cnt[T];
    }
    lg[0]=-1;
    for(int S=1;S<(1<<V);S++)
    {
        lg[S]=lg[S>>1]+1;
        int U=(S-(S&-S));
        __int128 res=0,f0=f[S][0],f1=f[S][1];
        for(int T=U;T;T=(T-1)&U)
        {
            int coef=get(S,T);
            f0=f0-(__int128)f[T][0]*dp[S^T][0]*coef;
            f0=f0-(__int128)f[T][1]*dp[S^T][1]*coef;
            f1=f1-(__int128)f[T][0]*dp[S^T][1]*coef;
            f1=f1-(__int128)f[T][1]*dp[S^T][0]*coef;
            res+=(__int128)h[T]*coef*dp[S^T][0];
            res+=(__int128)(h[T]+1)*coef*dp[S^T][1];
        }
        dp[S][0]=(f0%mod+mod)%mod;
        dp[S][1]=(f1%mod+mod)%mod;
        h[S]=(res%mod+dp[S][1])%mod;
    }
    printf("%d\n",h[(1<<V)-1]);
}
int main()
{
    freopen("cumulonimbus.in","r",stdin);
    freopen("cumulonimbus.out","w",stdout);
    int T;
    cin>>T;
    while(T--)
    {
        solve();
    }
    return 0;
}
