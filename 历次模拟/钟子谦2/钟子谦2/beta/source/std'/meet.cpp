#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
#define fi first
#define se second
typedef long long ll;
#define SZ 233333
#define mp make_pair
#define pb push_back
int n;
int sz[SZ],son[SZ],fa[SZ],fe[SZ];
vector<pii> e[SZ];
void dfs(int x,int faa=0) {
    sz[x]=1; ::fa[x]=faa;
    for(auto _:e[x]) {
        int b=_.fi,c=_.se;
        if(b==faa) continue;
        fe[b]=c;
        dfs(b,x);
        sz[x]+=sz[b];
        if(sz[b]>sz[son[x]]) son[x]=b;
    }
}
struct Bit {
ll b[SZ];
void edt(int x,ll v) {
    for(;x<SZ;x+=x&-x) b[x]+=v;
}
ll qry(int x) {
    ll r=0;
    for(;x;x-=x&-x) r+=b[x];
    return r;
}
ll qry(int l,int r) {
    return qry(r)-qry(l-1);
}
};
struct DS {
Bit b0,b1;
void edt_node(int x,int k) {
    int c=fe[x]*k;
    b0.edt(sz[x],c);
    b1.edt(sz[x],sz[x]*(ll)c);
}
}In,Out,Stk;
void edt(int x,int k) {
    // cout<<"edt"<<x<<","<<k<<"+\n";
    In.edt_node(x,k);
    Out.edt_node(x,-k);
}
void add_tree(int x) {
    edt(x,1);
    for(auto p:e[x]) {
        int b=p.fi;
        if(b==fa[x]) continue;
        add_tree(b);
    }
}
void clear_tree(int x) {
    edt(x,-1);
    for(auto p:e[x]) {
        int b=p.fi;
        if(b==fa[x]) continue;
        clear_tree(b);
    }
}
ll aans=8e18;
void dsu(int x,bool clr=0) {
    Stk.edt_node(x,1);
    for(auto p:e[x]) {
        int b=p.fi;
        if(b==fa[x]||b==son[x]) continue;
        dsu(b,1);
    }
    if(son[x]) dsu(son[x],0);
    Stk.edt_node(x,-1);
    for(auto p:e[x]) {
        int b=p.fi;
        if(b==fa[x]||b==son[x]) continue;
        add_tree(b);
    }
    edt(x,1);
    // In: min(s, sz[x]-s)
    // Out: min(n-s-sz[x], s)
    // Stack: min(n-s, s-sz[x])
    ll ans=0;
    int cut=sz[x]/2;
    ans+=In.b1.qry(cut);
    ans+=In.b0.qry(cut+1,sz[x])*sz[x]-In.b1.qry(cut+1,sz[x]);
    // cout<<ans<<"+\n";
    cut=(n-sz[x])/2;
    ans+=Out.b1.qry(cut);
    ans-=Stk.b1.qry(cut);
    ans+=Out.b0.qry(cut+1,n)*(n-sz[x])-Out.b1.qry(cut+1,n);
    ans-=Stk.b0.qry(cut+1,n)*(n-sz[x])-Stk.b1.qry(cut+1,n);
    cut=(n+sz[x])/2;
    ans+=Stk.b1.qry(cut)-Stk.b0.qry(cut)*sz[x];
    ans+=Stk.b0.qry(cut+1,n)*n-Stk.b1.qry(cut+1,n);
    aans=min(ans,aans);
    if(clr) clear_tree(x);
}
#define FO(x) {freopen(#x".in","r",stdin);freopen(#x".out","w",stdout);}
int main() {
    FO(meet)
    scanf("%d",&n);
    for(int i=1,a,b,c;i<n;++i)
        scanf("%d%d%d",&a,&b,&c),
        e[a].pb(mp(b,c)),
        e[b].pb(mp(a,c));
    dfs(1);
    for(int i=1;i<=n;++i) Out.edt_node(i,1);
    dsu(1);
    printf("%lld\n",aans);
}