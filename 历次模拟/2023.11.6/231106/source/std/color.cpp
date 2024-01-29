#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MOD=998244353;
#define fi first
#define se second
ll qp(ll a,ll b) {
    ll x=1; a%=MOD;
    while(b) {
        if(b&1) x=x*a%MOD;
        a=a*a%MOD, b>>=1;
    }
    return x;
}
#define SZ 666666
int n; ll t;
struct MyMap {
unordered_map<int,int> f;
ll k,b,s;
void clr() {
    k=1, b=s=0; f.clear();
}
MyMap() {
    clr();
}
ll sum() const {
    return (s*k+b*t)%MOD;
}
ll trans(ll x) const {
    x%=MOD; return (k*x+b)%MOD;
}
ll untrans(ll x) const {
    assert(k%MOD);
    x%=MOD; return (x-b)%MOD*qp(k,MOD-2)%MOD;
}
int size() const {
    return f.size();
}
void flip() {
    ll rs=sum();
    k=-k; b=(rs-b)%MOD;
}
ll get(int x) {
    return (f[x]*k+b)%MOD;
}
void set(int x,ll v) {
    v=untrans(v);
    s=(s-f[x]+v)%MOD;
    f[x]=v;
}
}f[SZ];
void merge(MyMap&a,MyMap&b) {
    ll normal_v = b.b;
    // except for values in b, multiply by normal_v
    unordered_map<int,int> m=b.f;
    for(const auto&it:b.f)
        m[it.fi]=b.get(it.fi)*(ll)a.get(it.fi)%MOD;
    if(normal_v%MOD==0) a.clr();
    else a.k=a.k*normal_v%MOD, a.b=a.b*normal_v%MOD;
    for(const auto&it:m)
        a.set(it.fi,it.se);
}
void swp(int a,int b) {
    swap(f[a].f,f[b].f);
    swap(f[a].k,f[b].k);
    swap(f[a].b,f[b].b);
    swap(f[a].s,f[b].s);
}
int c[SZ]; vector<int> adj[SZ];
void dfs(int x,int fa=0) {
    f[x].clr();
    if(c[x]) f[x].set(c[x],1);
    else f[x].b+=1;
    for(auto b:adj[x]) if(b!=fa) {
        dfs(b,x); f[b].flip();
        // cout<<"flipped:"<<b<<":"<<f[b].sum()<<"|"<<f[b].size()<<","<<f[x].size()<<"\n";
        if(f[x].size()<f[b].size()) swp(x,b);
        merge(f[x],f[b]);
    // cout<<x<<":";
    // cout<<f[x].sum()<<"?\n";
    }
    // cout<<x<<":";
    // cout<<f[x].sum()<<"\n";
}
#define FO(x) {freopen(#x".in","r",stdin);freopen(#x".out","w",stdout);}
int main() {
	FO(color)
    scanf("%d%lld",&n,&t);
    for(int i=1;i<=n;++i) scanf("%d",&c[i]);
    for(int i=1;i<n;++i) {
        int x,y; scanf("%d%d",&x,&y);
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    dfs(1);
    ll ans=f[1].sum();
    ans=(ans%MOD+MOD)%MOD;
    printf("%lld\n",ans);
}
