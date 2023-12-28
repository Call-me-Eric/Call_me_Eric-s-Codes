#include <bits/stdc++.h>
using namespace std;
int n,t;
typedef pair<int,int> pii;
#define fi first
#define se second
typedef long long ll;
#define SZ 233333
pii g[SZ];
int ff[SZ],mx[SZ],mi[SZ];
ll rl[SZ],su[SZ];
int gf(int x) {
    return ff[x]?ff[x]=gf(ff[x]):x;
}
void uni(int a,int b) {
    a=gf(a), b=gf(b);
    if(a!=b) ff[a]=b;
}
set<pair<ll,pii> > q;
ll f[SZ];
int vs[SZ],vn;
ll tot=0,ans[SZ];
int L[SZ],R[SZ];
ll e[SZ];
set<int> ava;
#define FO(x) {freopen(#x".in","r",stdin);freopen(#x".out","w",stdout);}
int main() {
	FO(distanced)
    scanf("%d%d",&n,&t);
    for(int i=1;i<=n;i++)
        scanf("%d",&g[i].fi),mx[i]=-2e9,mi[i]=2e9;
    for(int i=1;i<=n;i++) scanf("%d",&g[i].se),tot+=max(0,g[i].se);
    sort(g+1,g+n+1);
    for(int i=2;i<=n;++i) {
        if(g[i].se>=0&&g[i-1].se>=0&&abs(g[i].fi-g[i-1].fi)<=t)
            uni(i-1,i);
    }
    for(int i=1;i<=n;++i) {
        if(gf(i)==i&&g[i].se>=0) vs[++vn]=i,ava.insert(i);
        mx[gf(i)]=max(mx[gf(i)],i);
        mi[gf(i)]=min(mi[gf(i)],i);
        su[gf(i)]+=g[i].se;
    }
    for(int i=1;i<vn;++i) {
        int l=mx[vs[i]],r=mi[vs[i+1]];
        ll ans;
        static pair<ll,ll> ss[2333333]; int h=0,t=0;
        auto upd=[&](ll x,ll y) {
            while(h<t&&ss[t-1].se<=y) --t;
            ss[t++]={x,y};
        };
        auto qry=[&](ll x) {
            while(h<t&&ss[h].fi<x) ++h;
            return h<t?ss[h].se:ll(-1e18);
        };
        upd(g[l].fi,0);
        for(int u=l+1;u<=r;++u) {
            ll t=qry(g[u].fi-::t);
            if(u==r) ans=t;
            upd(g[u].fi,t+g[u].se);
        }
        e[vs[i]]=-ans;
        q.insert(make_pair(-ans,make_pair(vs[i],vs[i+1])));
    }
    for(int i=1;i<=vn;++i) {
        int v=vs[i];
        q.insert(make_pair(su[v],pii(v,0)));
    }
    vs[0]=0; vs[vn+1]=n+1;
    for(int i=0;i<=vn;++i)
        R[vs[i]]=vs[i+1],L[vs[i+1]]=vs[i];
    ans[vn]=tot;
    while(!q.empty()) {
        auto t=*q.begin(); q.erase(q.begin());
        if(t.se.se) {
            int a=t.se.fi,b=t.se.se,c=R[b];
            if(!ava.count(a)||!ava.count(b)) continue;
            // cout<<"A:"<<t.fi<<"|"<<a<<","<<b<<","<<c<<endl;
            --vn; tot-=t.fi;
            ans[vn]=max(ans[vn],tot);
            q.erase(make_pair(su[a],make_pair(a,0)));
            q.erase(make_pair(su[b],make_pair(b,0)));
            ff[b]=a; su[a]+=su[b]-t.fi;
            e[a]=e[b]; L[c]=a; R[a]=c;
            if(c<=n) {
                q.erase(make_pair(e[b],make_pair(b,c)));
                q.insert(make_pair(e[a],make_pair(a,c)));
            }
            q.insert(make_pair(su[a],make_pair(a,0)));
            ava.erase(b);
        }
        else {
            int a=t.se.fi,l=L[a],r=R[a];
            if(!ava.count(a)) continue;
            // cout<<"B:"<<t.fi<<"|"<<a<<","<<l<<","<<r<<endl;
            --vn; tot-=t.fi;
            ans[vn]=max(ans[vn],tot);
            // q.erase(make_pair(su[a],make_pair(a,0)));
            // remove
            ll ne=min(-su[a]+e[a]+e[l],ll(1e18)); // overflow!
            L[r]=l; R[l]=r;
            if(0<=l&&l<=n&&0<=r&&r<=n) {
                q.erase(make_pair(e[l],make_pair(l,a)));
                e[l]=ne;
                q.insert(make_pair(e[l],make_pair(l,r)));
            }
            ava.erase(a);
        }
        // cerr<<vn<<","<<tot<<"!\n";
    }
    for(int i=1;i<=n;++i)
        ans[i]=max(ans[i],ans[i-1]);
    for(int i=1;i<=n;++i)
        printf("%lld ",ans[i]);puts("");
}
