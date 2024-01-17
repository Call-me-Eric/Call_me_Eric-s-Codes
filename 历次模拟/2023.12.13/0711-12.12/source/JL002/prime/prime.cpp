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
ll t,l,r,pw[N];
vector<ll>g={1,4,6,8,9};
ll p[8]={2,3,5,7,11,13,17,19};
inline ll qpow(ll a,ll b,ll p)
{
    ll ret=1;
    while(b)
    {
        if(b&1)
            ret=(__int128)ret*a%p;
        b>>=1;
        a=(__int128)a*a%p;
    }
    return ret;
}
inline bool miller(ll x)
{
    for(int i=0;i<8;i++)
    {
        if(x==p[i])
            return true;
        if(qpow(p[i],x-1,x)!=1)
        {
            if(x==11)
                cerr<<"??? "<<x<<" "<<p[i]<<endl;
            return false;
        }
        ll now=x-1;
        while(now&&!(now&1))
        {
            now>>=1;
            ll tmp=qpow(p[i],now,x);
            if(tmp!=x-1&&tmp!=1)
            {
                if(x==11)
                    cerr<<"??? "<<x<<" "<<tmp<<" "<<p[i]<<endl;
                return false;
            }
            if(tmp==x-1)
                break;
        }
    }
    return true;
}
inline bool check(ll c,ll x,ll n)
{
    vector<ll>v;
    c=c*pw[n];
    ll t=n,px=x;
    while(n--)
    {
        v.push_back(x%10);
        x/=10;
    }
    reverse(v.begin(),v.end());
    for(int i=0;i<(1<<v.size());i++)
    {
        ll r=__builtin_popcount(i);
        ll pr=r;
        ll tmp=c*pw[pr];
        pr--;
        for(int j=0;j<v.size();j++)
            if((1<<j)&i)
                tmp+=v[j]*pw[pr],pr--;
        if(c==10&&px==1&&t==1)
            cerr<<tmp<<endl;
        if(miller(tmp))
            return false;
    }
    return true;
}
inline ll work(ll n)
{
    vector<ll>v;
    v.clear();
    ll now=0;
    while(true)
    {
        vector<ll>res=v;
        for(auto x:g)
        {
            if(x*pw[now]<=n)
                res.push_back(x*pw[now]);
        }
        for(auto x:v)
        {
            for(auto c:g)
            {
                if(c*pw[now]+x==11)
                    cerr<<c<<" "<<x<<" "<<now<<endl;
                if(c*pw[now]+x<=n&&check(c,x,now))
                    res.push_back(c*pw[now]+x);
            }
        }
        if(res==v)
            break;
        swap(v,res);
       for(auto x:v)
            cerr<<x<<" ";
        cerr<<endl;
        now++;
    }
    return v.size()%mod;
}
signed main()
{
    freopen("prime.in","r",stdin);
    freopen("prime.out","w",stdout);
    read(t);
    pw[0]=1;
    for(int i=1;i<=18;i++)
        pw[i]=pw[i-1]*10;
    while(t--)
    {
        read(l);
        read(r);
        printf("%lld\n",(work(r)-work(l-1)+mod)%mod);
    }
    exit(0);
}
