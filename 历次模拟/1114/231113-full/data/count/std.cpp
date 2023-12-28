#include<bits/stdc++.h>
namespace my_std{
    using namespace std;
    #define pii pair<int,int>
    #define fir first
    #define sec second
    #define MP make_pair
    #define rep(i,x,y) for (int i=(x);i<=(y);i++)
    #define drep(i,x,y) for (int i=(x);i>=(y);i--)
    #define go(x) for (int i=head[x];i;i=edge[i].nxt)
    #define templ template<typename T>
    #define sz 555555
    #define mod 998244353ll
    typedef long long ll;
    typedef double db;
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    templ inline T rnd(T l,T r) {return uniform_int_distribution<T>(l,r)(rng);}
    templ inline bool chkmax(T &x,T y){return x<y?x=y,1:0;}
    templ inline bool chkmin(T &x,T y){return x>y?x=y,1:0;}
    templ inline void read(T& t) {
        t=0;char f=0,ch=getchar();double d=0.1;
        while(ch>'9'||ch<'0') f|=(ch=='-'),ch=getchar();
        while(ch<='9'&&ch>='0') t=t*10+ch-48,ch=getchar();
        if(ch=='.'){ch=getchar();while(ch<='9'&&ch>='0') t+=d*(ch^48),d*=0.1,ch=getchar();}
        t=(f?-t:t);
    }
    template<typename T,typename... Args>inline void read(T& t,Args&... args){read(t); read(args...);}
    void file() {
        #ifdef zqj
        freopen("a.in","r",stdin);
        #endif
    }
    inline void chktime() {
        #ifdef zqj
        cerr<<clock()/1000.0<<'\n';
        #endif
    }
    #ifdef mod
    ll ksm(ll x,int y){ll ret=1;for (;y;y>>=1,x=x*x%mod) if (y&1) ret=ret*x%mod;return ret;}
    ll inv(ll x){return ksm(x,mod-2);}
    #else
    ll ksm(ll x,int y){ll ret=1;for (;y;y>>=1,x=x*x) if (y&1) ret=ret*x;return ret;}
    #endif
}
using namespace my_std;

int n;
vector<int>V[sz];

int vis[sz];
int loop;
vector<int>vv;
void dfs(int x) {
    vis[x]=1,vv.push_back(x);
    for (auto v:V[x]) {
        if (v==x) loop=1;
        else if (!vis[v]) dfs(v);
    }
}

int main() {
    // file();
    read(n);
    static int a[sz],b[sz];
    rep(i,1,n) read(a[i]);
    rep(i,1,n) read(b[i]);
    rep(i,1,n) {
        V[a[i]].push_back(b[i]);
        if (a[i]!=b[i]) V[b[i]].push_back(a[i]);
    }
    ll ans=1;
    rep(i,1,n) if (!vis[i]) {
        loop=0; vv.clear();
        dfs(i);
        int edge=0;
        for (auto x:vv) for (auto v:V[x]) if (v<=x) edge++;
        if (edge>(int)vv.size()) ans=0;
        else if (loop) ans=ans*n%mod;
        else ans=ans*2%mod;
    }
    cout<<(ksm(n,n)-ans+mod)%mod<<'\n';
    return 0;
}