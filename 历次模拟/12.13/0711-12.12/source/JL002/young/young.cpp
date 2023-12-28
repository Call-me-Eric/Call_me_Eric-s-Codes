#include<bits/stdc++.h>
#define N 201001
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
ll n,m,q,k;
vector<ll>a,b;
map<pair<vector<ll>,ll>,ll>mp;
inline ll dfs(vector<ll>now,ll k)
{
    for(int i=0;i<now.size();i++)
    {
        if(now[i]<0)
            return 0;
        if(i&&now[i-1]<now[i])
            return 0;
    }
    while(now.size()&&!now.back())
        now.pop_back();
    if(!k)
        return now==b;
    auto it=mp.find(make_pair(now,k));
    if(it!=mp.end())
        return it->second;
    ll ans=0;
    for(int i=0;i<now.size();i++)
    {
        now[i]--;
        ans+=dfs(now,k-1);
        now[i]++;
        now[i]++;
        ans+=dfs(now,k-1);
        now[i]--;
    }
    now.push_back(1);
    ans+=dfs(now,k-1);
    now.pop_back();
    return mp[make_pair(now,k)]=ans%mod;
}
signed main()
{
    freopen("young.in","r",stdin);
    freopen("young.out","w",stdout);
    read(n);
    a.resize(n);
    for(int i=0;i<n;i++)
        read(a[i]);
    read(m);
    b.resize(m);
    for(int i=0;i<m;i++)
        read(b[i]);
    read(q);
    while(q--)
    {
        read(k);
        printf("%lld\n",dfs(a,k));
    }
    exit(0);
}