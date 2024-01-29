#include<bits/stdc++.h>
#define il inline
using namespace std;
il long long read()
{
    long long xr=0,F=1; char cr;
    while(cr=getchar(),cr<'0'||cr>'9') if(cr=='-') F=-1;
    while(cr>='0'&&cr<='9')
        xr=(xr<<3)+(xr<<1)+(cr^48),cr=getchar();
    return xr*F;
}
#define int long long
namespace sub1
{
    const int mod=1e9+7;
    il int qpow(int n,int k)
    {
        int res=1;
        for(;k;n=n*n%mod,k>>=1) if(k&1) res=res*n%mod;
        return res;
    }
    il void solve()
    {
        int x=read();
        int ans=(qpow(3,x)+qpow(-1,x)*3%mod)%mod;
        ans=(ans+mod)%mod;
        printf("%lld\n",ans);
    }
}
namespace sub5
{
    const int N=1005;
    int n;
    struct edge{int nxt,to,w;} e[N<<1];
    int head[N],cnt;
    il void add(int u,int v,int w) {e[++cnt]={head[u],v,w};head[u]=cnt;}
    int dis[N],mx,rt;
    void dfs(int u,int fa)
    {
        if(dis[u]>mx) mx=dis[u],rt=u;
        for(int i=head[u];i;i=e[i].nxt)
        {
            int v=e[i].to,w=e[i].w; if(v==fa) continue;
            dis[v]=dis[u]+w;
            dfs(v,u);
        }
    }
    void solve()
    {
        n=read();
        for(int i=1;i<n;i++) 
        {
            int u=read(),v=read(),w=read();
            add(u,v,w),add(v,u,w);
        }
        dfs(1,0);
        dis[rt]=0,mx=0;
        dfs(rt,0);
        printf("%lld\n",mx);
    }
}
namespace sub7
{
    const int N=1005;
    int n,m;
    struct edge{int nxt,to,w;} e[N<<1];
    int head[N],cnt,dis[N];
    il void add(int u,int v,int w) {e[++cnt]={head[u],v,w};head[u]=cnt;}
    #define pii pair<int,int>
    #define fi first
    #define se second
    priority_queue<pii,vector<pii>,greater<pii> >q;
    void dij(int s)
    {
        dis[s]=0;
        q.push(pii(0,s));
        while(!q.empty())
        {
            int u=q.top().se,f=q.top().fi; q.pop();
            if(f!=dis[u])continue;
            for(int i=head[u];i;i=e[i].nxt)
            {
                int v=e[i].to,w=e[i].w;
                if(dis[v]>dis[u]+w)
                {
                    dis[v]=dis[u]+w;
                    q.push(pii(dis[v],v));
                }
            }
        }
    }
    void solve()
    {
        n=read(),m=read();
        for(int i=1;i<=m;i++)
        {
            int u=read(),v=read(),w=read();
            add(u,v,w),add(v,u,w);
        }
        dij(1);
        printf("%lld\n",dis[n]);
    }
}
signed main()
{
    freopen("crack.in","r",stdin);
    freopen("crack.out","w",stdout);
    int T=read();
    if(T==1) sub1::solve();
    if(T==5) sub5::solve();
    if(T==7) sub7::solve();
}