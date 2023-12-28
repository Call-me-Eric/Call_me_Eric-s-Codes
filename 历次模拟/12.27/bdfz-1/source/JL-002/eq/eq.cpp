#include<bits/stdc++.h>
#define N 15000101
#define MAX 2001
using namespace std;
typedef long long ll;
typedef double db;
const ll mod=998244353;
inline void read(ll &ret)
{
    ret=0;char c=getchar();bool pd=false;
    while(!isdigit(c)){pd|=c=='-';c=getchar();}
    while(isdigit(c)){ret=(ret<<1)+(ret<<3)+(c&15);c=getchar();}
    ret=pd?-ret:ret;
    return;
}
ll n,q,a[MAX][MAX],las[MAX],cnt,now[MAX];
vector<ll>v[MAX<<2];
inline ll qpow(ll a,ll b)
{
    ll ret=1;
    while(b)
    {
        if(b&1)
            ret*=a,ret%=mod;
        b>>=1;
        a*=a;
        a%=mod;
    }
    return ret;
}
inline void upgrade(ll pos,ll l,ll r,ll s,ll t,ll p)
{
    if(l>t||r<s)
        return;
    else if(l>=s&&r<=t)
    {
        v[pos].push_back(p);
        return;
    }
    ll mid=l+r>>1;
    upgrade(pos<<1,l,mid,s,t,p);
    upgrade(pos<<1|1,mid+1,r,s,t,p);
    return;
}
vector<ll>g;
ll p[MAX];
int pid[N],qid[N],d[N],head;
ll ans[MAX][MAX];
ll mx;
inline void add(ll id)
{
  //  cout<<"add "<<id<<" "<<head<<endl;
    for(auto x:g)
    {
        if(!p[x])
            continue;
        ll div=a[id][p[x]]*qpow(a[x][p[x]],mod-2)%mod;
        head++;
        pid[head]=id,qid[head]=x,d[head]=div;
        for(int j=1;j<=n+1;j++)
        {
            if(a[x][j])
                a[id][j]-=a[x][j]*div%mod,a[id][j]+=a[id][j]<0?mod:0;
        }
    }
    g.push_back(id);
    bool flag=false;
    p[id]=0;
    for(int i=1;i<=n;i++)
        if(a[id][i])
        {
            p[id]=i;
            break;
        }
    return;
}
inline void work(ll pos,ll l,ll r)
{
    ll tmp=head;
    for(auto x:v[pos])
        add(x);
    if(l==r)
    {
      //  cout<<"query "<<l<<endl;
        bool f1=true,f2=true;
        for(int j=(int)g.size()-1;j+1;j--)
        {
          //  cout<<g[j]<<" "<<p[g[j]]<<endl;
            if(!p[g[j]])
            {
                f1=false;
                f2&=a[g[j]][n+1]==0;
                continue;
            }
            ans[l][p[g[j]]]=a[g[j]][n+1];
            for(int k=1;k<=n;k++)
            {
                if(a[g[j]][k]&&k!=p[g[j]]&&ans[l][k])
                {
                    ans[l][p[g[j]]]-=a[g[j]][k]*ans[l][k]%mod;
                    ans[l][p[g[j]]]+=ans[l][p[g[j]]]<0?mod:0;
                }
            }
            ans[l][p[g[j]]]*=qpow(a[g[j]][p[g[j]]],mod-2),ans[l][p[g[j]]]%=mod;
        }
        if(!f1)
        {
            if(f2)
                ans[l][n+1]=1;
            else
                ans[l][n+1]=-1;
        }
    }
    else
    {
        ll mid=l+r>>1;
        work(pos<<1,l,mid);
        work(pos<<1|1,mid+1,r);
    }
    for(auto x:v[pos])
        g.pop_back();
    while(head>tmp)
    {
        ll div=d[head];
        for(int j=1;j<=n+1;j++)
        {
            if(a[qid[head]][j])
                a[pid[head]][j]+=a[qid[head]][j]*d[head]%mod,a[pid[head]][j]-=a[pid[head]][j]>=mod?mod:0;
        }
        head--;
    }
    return;
}
signed main()
{
    freopen("eq.in","r",stdin);
    freopen("eq.out","w",stdout);
    read(n);
    read(q);
    for(int i=1;i<=n;i++)
    {
        now[i]=i;
        for(int j=1;j<=n+1;j++)
            read(a[i][j]);
    }
    for(int i=1;i<=q;i++)
    {
        ll id;
        read(id);
        upgrade(1,0,q,las[id],i-1,now[id]);
        for(int j=1;j<=n+1;j++)
            read(a[n+i][j]);
        las[id]=i;
        now[id]=n+i;
    }
    for(int i=1;i<=n;i++)
        upgrade(1,0,q,las[i],q,now[i]);
    work(1,0,q);
    for(int i=0;i<=q;i++)
    {
        if(ans[i][n+1]==1)
            puts("Many");
        else if(ans[i][n+1]==-1)
            puts("No");
        else
        {
            for(int j=1;j<=n;j++)
                printf("%lld ",ans[i][j]);
            putchar('\n');
        }
    }
    exit(0);
}