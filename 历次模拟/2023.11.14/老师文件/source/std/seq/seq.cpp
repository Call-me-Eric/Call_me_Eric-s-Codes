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

struct Mat {
    ll a[3][3];
    Mat(){memset(a,0,sizeof(a));}
    Mat(const array<array<int,3>,3> &A){rep(i,0,2) rep(j,0,2) a[i][j]=A[i][j];}
    Mat operator * (const Mat &x) const {
        Mat res;
        rep(k,0,2) rep(i,0,2) rep(j,0,2) res.a[i][j]+=a[i][k]*x.a[k][j];
        return res;
    }
    Mat operator + (const Mat &x) const {
        Mat res;
        rep(i,0,2) rep(j,0,2) res.a[i][j]=a[i][j]+x.a[i][j];
        return res;
    }
    bool operator != (const Mat &x) const {rep(i,0,2) rep(j,0,2) if (a[i][j]!=x.a[i][j]) return 1;return 0;}
}O({array<int,3>{0,0,0},{0,0,0},{0,0,0}}),I({array<int,3>{1,0,0},{0,1,0},{0,0,1}}),I1({array<int,3>{0,0,0},{0,0,0},{0,0,1}});

int n,Q;
int a[sz];
int L[sz],R[sz];
array<int,3>q[sz];
ll ans[sz];

#define ls k<<1
#define rs k<<1|1
#define lson ls,l,mid
#define rson rs,mid+1,r
Mat tr[sz<<2],tag[sz<<2];
void Tag(int k,const Mat &m) {
    tr[k]=m*tr[k],tag[k]=m*tag[k];
}
void pushdown(int k) {
    Mat &m=tag[k];
    if (m!=I) Tag(ls,m),Tag(rs,m);
    m=I;
}
void pushup(int k){tr[k]=tr[ls]+tr[rs];}
void build(int k,int l,int r) {
    tag[k]=I;
    if (l==r) return tr[k]=I1,void();
    int mid=(l+r)>>1;
    build(lson),build(rson);
    pushup(k);
}
void modify(int k,int l,int r,int x,int y,const Mat &m) {
    if (x<=l&&r<=y) return Tag(k,m),void();
    int mid=(l+r)>>1; pushdown(k);
    if (x<=mid) modify(lson,x,y,m);
    if (y>mid) modify(rson,x,y,m);
    pushup(k);
}
Mat query(int k,int l,int r,int x,int y) {
    if (x<=l&&r<=y) return tr[k];
    int mid=(l+r)>>1; Mat res=O;
    if (x<=mid) res=res+query(lson,x,y);
    if (y>mid) res=res+query(rson,x,y);
    return tag[k]*res;
}

int main() {
    read(n,Q);
    rep(i,1,n) read(a[i]),R[a[i]]=i;
    drep(i,n,1) L[a[i]]=i;
    int x,y;
    rep(i,1,Q) read(x,y),q[i]={x,y,i};
    sort(q+1,q+Q+1,[](const array<int,3> &x,const array<int,3> &y){return x[1]<y[1];});
    int p=0;
    set<pii>S;
    build(1,1,n);
    rep(i,1,n) {
        if (R[a[i]]==i) {
            pii p(L[a[i]],a[i]);
            Mat m({array<int,3>{0,0,a[i]},{0,1,0},{0,0,1}});
            auto it=S.lower_bound(p);
            if (it!=S.end()&&it->sec>a[i]);
            else if (it==S.begin()) S.insert(p),modify(1,1,n,1,p.fir,m);
            else {
                --it;
                while (it!=S.begin()&&it->sec<a[i]) S.erase(it--);
                if (it->sec<a[i]) S.erase(it),modify(1,1,n,1,p.fir,m);
                else modify(1,1,n,it->fir+1,p.fir,m);
                S.insert(p);
            }
        }
        Tag(1,Mat({array<int,3>{1,0,0},{1,1,0},{0,0,1}}));
        while (p<Q&&q[p+1][1]==i) {
            ++p;
            ans[q[p][2]]=query(1,1,n,q[p][0],i).a[1][2];
        }
    }
    rep(i,1,Q) printf("%lld\n",ans[i]);
    // chktime();
    return 0;
}