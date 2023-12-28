// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")
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
    #define sz 1005005
    typedef long long ll;
    typedef unsigned long long ull;
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
        cerr<<clock()/db(CLOCKS_PER_SEC)<<'\n';
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

int n,m,Q;
vector<int>V[sz];
int q[sz];

const int L1=24;
const int L2=16;
const db prob[L1] = {
    1.0, 0.5714285714285714, 0.32653061224489793, 0.18658892128279883, 0.10662224073302791, 0.06092699470458737, 0.0348154255454785, 0.01989452888313057, 0.011368302218931755, 0.006496172696532431, 0.003712098683732818, 0.0021211992478473245, 0.0012121138559127568, 0.0006926364890930039, 0.00039579227948171653, 0.00022616701684669517, 0.00012923829534096867, 7.385045448055353e-05, 4.220025970317344e-05, 2.411443411609911e-05, 1.3779676637770919e-05, 7.874100935869097e-06, 4.499486249068055e-06, 2.5711349994674604e-06
};
db coef[L1],pw[sz][L1];
struct Init__ {
    Init__() {
        rep(i,1,L1-1) coef[i]=1-prob[i];
        rep(x,0,sz-1) rep(i,1,L1-1) pw[x][i]=log(1-pow(coef[i],x));
    }
}init__;
struct Hsh {    
    ull h[L2];
    void clear(){memset(h,0,sizeof(h));}
    void operator ^= (const Hsh &a) {
        rep(j,0,L2-1) h[j]^=a.h[j];
    }
}w[sz],a[sz];

int eval(int p[L1]) {
    if (!p[0]) return 0;
    db K=0;
    rep(i,1,L1-1) K+=(L2-p[i])*log(coef[i]);
    auto calc=[&](db x) {
        db res=K*x;
        rep(i,1,L1-1) res+=p[i]*pw[(int)x][i];
        return res;
    };
    db l=1,r=m;
    while (l<r*0.95) {
        db m1=cbrt(l*l*r),m2=cbrt(l*r*r);
        if (calc(m1)<calc(m2)) l=m1;
        else r=m2;
    }
    return sqrt(1ll*l*r);
}

int p[sz][L1];

int main() {
    read(n,m,Q);
    rep(i,1,n) {
        int K,x; read(K); V[i].reserve(K);
        while (K--) read(x),V[i].push_back(x);
    }
    rep(i,1,Q) read(q[i]);
    static ull ww[sz];
    rep(i,1,m) ww[i]=rnd(0ull,1ull<<62);
    chktime();
    rep(j,0,L1-1) {
        rep(i,1,n) a[i].clear();
        rep(i,1,m) w[i].clear();
        if (j==0) rep(i,1,m) rep(k,0,L2-1) w[i].h[k]=ww[i];
        else if (j<=3) {
            rep(i,1,m) rep(k,0,L2-1) if (rnd(0ll,ll(10000/prob[j]))<10000) w[i].h[k]=ww[i];
        }
        else {
            int cc=m*L2*prob[j],x;
            while (cc--) {
                x=rnd(0,m*L2-1); 
                if (w[x/L2+1].h[x%L2]) ++cc;
                w[x/L2+1].h[x%L2]=ww[x/L2+1];
            }
        }
        rep(i,1,n) for (auto x:V[i]) a[i]^=(x<0?w[-x]:a[x]);
        Hsh cur=w[0];
        rep(i,1,Q) {
            cur^=a[q[i]];
            rep(k,0,L2-1) p[i][j]+=(cur.h[k]!=0);
        }
    }
    rep(i,1,Q) printf("%d\n",min(m,eval(p[i])));
    chktime();
    return 0;
}