#include "bits/stdc++.h"
#ifdef DEBUG
#include "PrettyDebug.hpp"
#else
#define debug(...) [](auto...){}(__VA_ARGS__)
#define debuga(...) [](auto...){}(__VA_ARGS__)
#endif
#define For(i,a,b) for(int i=a;i<=b;i++)
#define Rev(i,a,b) for(int i=a;i>=b;i--)
#define Fin(file) freopen(file,"r",stdin)
#define Fout(file) freopen(file,"w",stdout)
using namespace std; typedef long long ll;
constexpr int N=2e5+5;
int n,m,fa[N],cnt[N],siz[N],flg[N],a[N],b[N],deg[N];
int getfa(int x) { return x==fa[x]?x:(fa[x]=getfa(fa[x])); }
signed main(){
    Fin("li.in"); Fout("li.out");
    atexit([](){cerr<<"Time = "<<clock()<<" ms"<<endl;}); ios::sync_with_stdio(0); cin.tie(0);
    cin>>n>>m; For(i,1,n) fa[i]=i,siz[i]=1;
    For(i,1,m) cin>>a[i]>>b[i],deg[a[i]]++,deg[b[i]]++;
    For(i,1,m){
        int x=getfa(a[i]),y=getfa(b[i]);
        if(x==y){
            if(deg[a[i]]>=3||deg[b[i]]>=3) flg[x]=1;
            cnt[x]++;
        }
        else{
            fa[y]=x; siz[x]+=siz[y]; cnt[x]+=cnt[y]+1; flg[x]|=flg[y]|(deg[a[i]]>=3)|(deg[b[i]]>=3);
        }
    }
    ll ans0=0,ans1=0; int loop=0;
    For(i,1,n) if(fa[i]==i){
        if(flg[i]){
            if(cnt[i]!=3) return cout<<"-1\n",0;
            else loop=1,ans1+=3;
        }
        else{
            if(cnt[i]==siz[i]){
                loop=1; ans1+=cnt[i];
            }
            else if(cnt[i]==siz[i]-1){
                ans0+=1ll*siz[i]*(siz[i]+1)/2;
            }
            else assert(0);
        }
    }
    if(loop) cout<<1<<' '<<ans1<<'\n';
    else cout<<0<<' '<<ans0<<'\n';
    return 0;
}

// START TYPING IF YOU DON'T KNOW WHAT TO DO
// STOP TYPING IF YOU DON'T KNOW WHAT YOU'RE DOING
// CONTINUE, NON-STOPPING, FOR CHARLIEVINNIE

// Started Coding On: December 25 Mon, 14 : 41 : 25