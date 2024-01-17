#include "bits/stdc++.h"
#define DEBUG_OFF
#ifdef DEBUG
#include "PrettyDebug.hpp"
#else
#define debug(...) [](auto...){}(__VA_ARGS__)
#endif
#define For(i,a,b) for(int i=a;i<=b;i++)
#define Rev(i,a,b) for(int i=a;i>=b;i--)
#define Fin(file) freopen(file,"r",stdin)
#define Fout(file) freopen(file,"w",stdout)
#define assume(expr) ((!!(expr))||(exit((fprintf(stderr,"Assumption Failed: %s on Line %d\n",#expr,__LINE__),-1)),false))
#define range basic_string_view
using namespace std; typedef long long ll;
signed main(){
    Fin("andgraph.in"); Fout("andgraph.out");
    atexit([](){cerr<<"Time = "<<clock()<<" ms"<<endl;}); ios::sync_with_stdio(0); cin.tie(0);
    int n,m,Q; cin>>n>>m>>Q; vector<int> a(n+1); For(i,1,n) cin>>a[i];
    auto b=a; sort(b.begin()+1,b.end());
    ll dis[21][21]={0}; For(i,0,20) For(j,0,20) dis[i][j]=i==j?0:1e18;
    int msk[21]={0}; For(i,0,20) msk[i]=(1<<20)-1;
    For(i,1,n){
        For(u,0,20) if(b[i]>>u&1){
            int s=b[i]&msk[u]; if(!s) continue;
            For(v,0,20) if(s>>v&1) dis[u][v]=b[i];
            msk[u]^=s;
        }
    }
    For(k,0,20) For(i,0,20) For(j,0,20) dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
    // cerr<<"Time: "<<clock()<<'\n';
    For(i,0,20) debug(i,dis[i]);
    vector<ll> Dis[21];
    // vector<int> ctz(1<<20); For(s,1,(1<<20)-1) ctz[s]=__builtin_ctz(s);
    For(i,0,20){
        Dis[i].resize(1<<20); Dis[i][0]=1e18;
        For(s,1,(1<<20)-1){
            int j=__builtin_ctz(s);
            Dis[i][s]=min(Dis[i][s^1<<j],dis[i][j]);
        }
    }
    // cerr<<"Time: "<<clock()<<'\n';
    while(Q--){
        int x,y; cin>>x>>y; //if(x==y) { cout<<"0\n"; continue; }
        if(a[x]&a[y]) { cout<<a[x]+a[y]<<'\n'; continue; }
        ll ans=1e18; For(i,0,20) if(a[y]>>i&1) ans=min(ans,Dis[i][a[x]]);
        if(ans==1e18) cout<<"-1\n"; else cout<<ans*2+a[x]+a[y]<<'\n';
    }
    return 0;
}

// START TYPING IF YOU DON'T KNOW WHAT TO DO
// STOP TYPING IF YOU DON'T KNOW WHAT YOU'RE DOING
// CONTINUE, NON-STOPPING, FOR CHARLIEVINNIE

// Started Coding On: October 17 Tue, 08 : 39 : 29