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
#define RGB Charlie_RGB
using namespace std; typedef long long ll;
constexpr int N=255,M=N*N;
class UFSet{
    int n,fa[N];
public:
    void init(int _n) { n=_n; For(i,1,n) fa[i]=i; }
    int getfa(int x) { return x==fa[x]?x:(fa[x]=getfa(fa[x])); }
    bool merge(int x,int y){
        x=getfa(x); y=getfa(y); if(x==y) return false; else return fa[y]=x,true;
    }
}S;
char c[M]; int ansR,ansG,ansB,n,m,a[M],b[M],R,G,B,vis[M]; vector<int> lis,Tmax,Tmin;
[[noreturn]] void NO() { cout<<"NO\n"; exit(0); }
inline int& RGB(char ch) { return ch=='r'?R:ch=='g'?G:B; }
bool SwapFor(int o,char cc){
    S.init(n); S.merge(a[o],b[o]);
    for(int e:lis) if(c[e]!=cc){
        if(!S.merge(a[e],b[e])) return false;
    }
    RGB(c[o])++; RGB(cc)--; int bad=0;
    for(int e:lis) if(c[e]==cc){
        if(!S.merge(a[e],b[e])) { bad=e; break; }
    }
    assert(bad);
    lis.push_back(o); lis.erase(find(lis.begin(),lis.end(),bad));
    vis[o]=1; vis[bad]=0;
    return true;
}
signed main(){
    Fin("rgb.in"); Fout("rgb.out");
    atexit([](){cerr<<"Time = "<<clock()<<" ms"<<endl;});; ios::sync_with_stdio(0); cin.tie(0);
    cin>>ansR>>ansG>>ansB>>m; n=ansR+ansG+ansB+1; For(i,1,m) cin>>a[i]>>b[i]>>c[i];
    S.init(n);
    For(i,1,m) if(c[i]=='r'&&S.merge(a[i],b[i])) lis.push_back(i),R++,vis[i]=1;
    For(i,1,m) if(c[i]=='g'&&S.merge(a[i],b[i])) lis.push_back(i),G++,vis[i]=1;
    For(i,1,m) if(c[i]=='b'&&S.merge(a[i],b[i])) lis.push_back(i),B++,vis[i]=1;
    if(R<ansR) NO();
    while(G<ansG&&R>=ansR){
        int ok=0;
        For(i,1,m) if(c[i]=='g'&&!vis[i]){
            if(SwapFor(i,'b')) { ok=1; break; }
        }
        if(ok) continue;
        For(i,1,m) if(c[i]=='g'&&!vis[i]){
            if(SwapFor(i,'r')) { ok=1; break; }
        }
        if(!ok) break;
    }
    if(G<ansG||R<ansR) NO();
    Tmax=lis; debug(Tmax);
    S.init(n); R=G=B=0; lis.clear(); For(i,1,m) vis[i]=0;
    For(i,1,m) if(c[i]=='b'&&S.merge(a[i],b[i])) lis.push_back(i),B++,vis[i]=1;
    For(i,1,m) if(c[i]=='g'&&S.merge(a[i],b[i])) lis.push_back(i),G++,vis[i]=1;
    For(i,1,m) if(c[i]=='r'&&S.merge(a[i],b[i])) lis.push_back(i),R++,vis[i]=1;
    if(R>ansR) NO();
    while(G>ansG&&R<=ansR){
        int ok=0;
        For(i,1,m) if(c[i]=='b'&&!vis[i]){
            if(SwapFor(i,'g')) { ok=1; break; }
        }
        if(ok) continue;
        For(i,1,m) if(c[i]=='r'&&!vis[i]){
            if(SwapFor(i,'g')) { ok=1; break; }
        }
         if(!ok) break;
    }
    if(G>ansG||R>ansR) NO();
    Tmin=lis;
    debug(Tmax); debug(Tmin);
    cout<<"YES\n";
    while(R<ansR||G<ansG){
        int ok=0;
        if(R<ansR){
            for(int e:Tmax) if(c[e]=='r'&&!vis[e]){
                if(SwapFor(e,'b')) { ok=1; break; }
            }
        }
        if(ok) continue;
        if(G<ansG){
            for(int e:Tmax) if(c[e]=='g'&&!vis[e]){
                if(SwapFor(e,'b')) { ok=1; break; }
            }
        }
        if(ok) continue;
        for(int e:Tmax) if(c[e]=='r'&&!vis[e]){
            if(SwapFor(e,'g')) { ok=1; break; }
        }
        assert(ok);
    }
    For(i,1,m) cout<<vis[i];; cout<<'\n';
    return 0;
}

// START TYPING IF YOU DON'T KNOW WHAT TO DO
// STOP TYPING IF YOU DON'T KNOW WHAT YOU'RE DOING
// CONTINUE, NON-STOPPING, FOR CHARLIEVINNIE

// Started Coding On: December 11 Mon, 15 : 12 : 27