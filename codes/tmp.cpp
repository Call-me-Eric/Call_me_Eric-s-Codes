#include<bits/stdc++.h>
#define pb push_back
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
const int N=3e5+5,MOD=998244353;
int power(int x,int y){
    int ans=1;
    for(;y;y>>=1,x=1ll*x*x%MOD) if(y&1) ans=1ll*ans*x%MOD;
    return ans;
}
void add(int &x,int y){ x+=y; if(x>=MOD) x-=MOD; if(x<0) x+=MOD; }
int ad(int x,int y){ x+=y; if(x>=MOD) x-=MOD; if(x<0) x+=MOD; return x; }
int n,m,q;
struct node{ int u,v,w; }edge[N];
vector<pii> e[N],fr[N],tree[N];
vector<int> t;
void Add(int u,int v,int w){ e[u].pb({v,w}); }
int dfn[N],tot,val[N],fa[N][20],sz[N],depth[N];
void dfs(int x){
    dfn[x]=++tot,sz[x]=1,depth[x]=depth[fa[x][0]]+1;
    for(int i=1;i<=q;++i) fa[x][i]=fa[fa[x][i-1]][i-1];
    for(auto y:e[x]) if(!dfn[y.fi]) val[y.fi]=1ll*val[x]*y.se%MOD,fa[y.fi][0]=x,dfs(y.fi),sz[x]+=sz[y.fi];
}
int lca(int x,int y){   
    if(depth[x]>depth[y]) x^=y^=x^=y;
    for(int i=q;~i;--i) if(depth[fa[y][i]]>=depth[x]) y=fa[y][i];
    if(x==y) return x;
    for(int i=q;~i;--i) if(fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
    return fa[x][0];
}
bool cmp(int x,int y){
    return dfn[x]<dfn[y];
}
int ed;
int work(int x){
    if(x==ed) return 0;
    int ans=1;
    for(auto y:tree[x]) ans=1ll*ans*ad(ad(1,-y.se),1ll*y.se*work(y.fi)%MOD)%MOD;
    return ans;
}
int main(){
    scanf("%d%d",&n,&m),q=log2(n);
    for(int i=1,p,q;i<=m;++i) scanf("%d%d%d%d",&edge[i].u,&edge[i].v,&p,&q),edge[i].w=1ll*p*power(q,MOD-2)%MOD,Add(edge[i].u,edge[i].v,edge[i].w);
    val[1]=1,dfs(1);
    for(int i=1;i<=m;++i) if(dfn[edge[i].u]<dfn[edge[i].v]||dfn[edge[i].u]>=dfn[edge[i].v]+sz[edge[i].v]) fr[edge[i].v].pb({edge[i].u,edge[i].w});
    puts("1");
    for(int x=2;x<=n;++x){
        t.clear(),t.pb(1); for(auto y:fr[x]) t.pb(y.fi);
        sort(t.begin(),t.end(),cmp),t.erase(unique(t.begin(),t.end()),t.end());
        int now=t.size();
        for(int i=1;i<now;++i) t.pb(lca(t[i],t[i-1]));
        sort(t.begin(),t.end(),cmp),t.erase(unique(t.begin(),t.end()),t.end());
        for(int i=1;i<t.size();++i){
            int l=lca(t[i],t[i-1]);
            tree[l].pb({t[i],1ll*val[t[i]]*power(val[l],MOD-2)%MOD});
        }
        for(auto y:fr[x]) tree[y.fi].pb({x,y.se});
        ed=x,printf("%d\n",ad(1,-work(1)));
        for(int i=0;i<t.size();++i) tree[t[i]].clear();
    }

    return 0;
}