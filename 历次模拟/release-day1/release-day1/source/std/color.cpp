#include "bits/stdc++.h"
#define debug(...) (void)(__VA_ARGS__)
#define For(i,a,b) for(int i=a;i<=b;i++)
#define Rev(i,a,b) for(int i=a;i>=b;i--)
#define Fin(file) freopen(file,"r",stdin)
#define Fout(file) freopen(file,"w",stdout)
#define assume(expr) ((!!(expr))||(exit((fprintf(stderr,"Assumption Failed: %s on Line %d\n",#expr,__LINE__),-1)),false))
#define range basic_string_view
using namespace std; typedef long long ll; using pii = pair<int,int>;
void Solve(){
    int n,m; cin>>n>>m; vector G(n+1,vector(0,0)),to(n*2+1,vector(0,0)); For(i,1,m) { int x,y; cin>>x>>y; G[x].push_back(y); G[y].push_back(x); }
    stack<int> st; vector<int> dfn(n+1),low(n+1); int dfscnt=0,cnt=n;
    auto addedge=[&](int x,int y){to[x].push_back(y);to[y].push_back(x);};
    function<void(int,int)> dfs=[&](int u,int pa){
        dfn[u]=low[u]=++dfscnt; st.push(u);
        for(int v:G[u]) if(v!=pa){
            if(!dfn[v]){
                dfs(v,u),low[u]=min(low[u],low[v]);
                if(low[v]>=dfn[u]){
                    addedge(u,++cnt); while(st.top()!=v) addedge(st.top(),cnt),st.pop();
                    addedge(v,cnt); st.pop();
                }
            }
            else low[u]=min(low[u],dfn[v]);
        }
    };
    dfs(1,0); int ans=0;
    For(u,n+1,cnt) for(int v:to[u]) debug(u,v);
    function<pii(int,int)> get=[&](int u,int pa){
        pii res(1,u); for(int v:to[u]) if(v!=pa) { pii tt=get(v,u); tt.first++; res=max(res,tt); }
        return res;
    };
    int P=get(1,0).second, Q=get(P,0).second; debug(P,Q);
    auto solve=[&](int rt){
        get(rt,0);
        queue<int> q; vector<int> dis(n+1),siz(n+1); q.push(rt);
        while(q.size()){
            int u=q.front(); q.pop(); for(int v:G[u]) if(v!=rt&&!dis[v]) dis[v]=dis[u]+1,q.push(v);
        }
        dfscnt=0; For(i,1,n) dfn[i]=low[i]=0;
        function<int(int)> dfs2=[&](int u){
            debug(rt,u);
            dfn[u]=low[u]=++dfscnt; int mx=dis[u]; siz[u]=(u<=n);
            for(int v:G[u]){
                if(!dfn[v]){
                    int x=dfs2(v); mx=max(mx,x); siz[u]+=siz[v]; low[u]=min(low[u],low[v]);
                    if(u<=n&&low[v]>=dfn[u]) ans=max(ans,2*(x-dis[u])-siz[v]),debug(rt,u,v,x,dis[u],siz[v]);
                }
                else low[u]=min(low[u],dfn[v]);
            }
            debug(u);
            return mx;
        };
        dfs2(rt);
    };
    solve(P); solve(Q);
    debug(ans);
    if((ans&1)==(n&1)) ans++;
    cout<<(n+ans-1)/2<<'\n';
}
signed main(){
    Fin("color.in");
	Fout("color.out");
    atexit([](){cerr<<"Time = "<<clock()<<" ms"<<endl;});
    ios::sync_with_stdio(0); cin.tie(0); Solve();
    return 0;
}
