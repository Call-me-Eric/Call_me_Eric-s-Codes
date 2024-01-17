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
using namespace std; typedef long long ll; using Arr = array<int,22>;
constexpr int N=125,mod=998244353; using ull = unsigned long long;
constexpr int P[]={11,19,41,61,89,409,449,499,881,991,6469,6949,9001,9049,9649,9949,60649,666649,946669,60000049,66000049,66600049};
constexpr int Len[]={2,2,2,2,2,3,3,3,3,3,4,4,4,4,4,4,5,6,6,8,8,8};
constexpr int pw[]={1,10,100,1000,10000,100000,1000000,10000000,100000000};
map<Arr,int> mp; int tot,to[N][10]; char s[100005]; int n,f[2][N],tmp[2][N];
void dfs(Arr a,int u){
    mp[a]=u;
    // cerr<<"u="<<u<<'\n';
    int bad[10]={0}; Arr b[10]; for(int x:{0,1,4,6,8,9}) b[x]=a;
    For(i,0,21){
        int x=P[i]/pw[a[i]]%10; if(pw[a[i]+1]<P[i]) b[x][i]++; else bad[x]=1;
    }
    for(int x:{0,1,4,6,8,9}) if(!bad[x]){
        if(!mp.count(b[x])) dfs(b[x],++tot);
        to[u][x]=mp[b[x]];
    }
}
inline void ck(int& x,int y) { x+=y-mod; x+=x>>31&mod; }
int solve(){
    if(n==1&&s[1]=='0') return 1;
    For(o,0,1) For(i,1,tot) f[o][i]=0;
    int O=1;
    Rev(i,n,1){
        For(o,0,1) For(u,1,tot) tmp[o][u]=0;
        For(o,0,1) For(u,1,tot) if(f[o][u]){
            for(int x:{0,1,4,6,8,9}) if(to[u][x]){
                int v=to[u][x];
                if(x<s[i]-'0') ck(tmp[0][v],f[o][u]);
                else if(x>s[i]-'0') ck(tmp[1][v],f[o][u]);
                else ck(tmp[o][v],f[o][u]);
            }
        }
        int O0=0;
        for(int x:{0,1,4,6,8,9}) if(to[O][x]){
            int v=to[O][x];
            if(x<s[i]-'0') ck(tmp[0][v],1);
            else if(x>s[i]-'0') ck(tmp[1][v],1);
            else O0=v;
        }
        O=O0;
        For(o,0,1) For(u,1,tot) f[o][u]=tmp[o][u];
        // For(o,0,1) For(u,1,tot) if(f[o][u]) debug(i,o,u,f[o][u]);
    }
    int ans=(O!=0); For(u,1,tot) ck(ans,f[0][u]);
    // debug(s+1,ans);
    return ans;
}
signed main(){
    Fin("prime.in"); Fout("prime.out");
    atexit([](){cerr<<"Time = "<<clock()<<" ms"<<endl;}); ios::sync_with_stdio(0); cin.tie(0);
    dfs(Arr(),++tot);
    int T; cin>>T; while(T--){
        cin>>(s+1); n=strlen(s+1);
        Rev(i,n,1){
            if(s[i]=='0') s[i]='9';
            else { s[i]--; break; }
        }
        int ans=solve();
        cin>>(s+1); n=strlen(s+1);
        cout<<(solve()-ans+mod)%mod<<'\n';
    }
    return 0;
}

// START TYPING IF YOU DON'T KNOW WHAT TO DO
// STOP TYPING IF YOU DON'T KNOW WHAT YOU'RE DOING
// CONTINUE, NON-STOPPING, FOR CHARLIEVINNIE

// Started Coding On: December 11 Mon, 16 : 29 : 00