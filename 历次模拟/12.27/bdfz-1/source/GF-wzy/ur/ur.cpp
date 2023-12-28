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
namespace Solve1{
    constexpr int N=36; using T = complex<double>; const double eps=1e-8,PI=acos(-1.0);
    struct Cmp{
        bool operator() (const T& A,const T& B) const {
            if(abs(A.real()-B.real())>eps) return A.real()<B.real();
            else if(abs(A.imag()-B.imag())>eps) return A.imag()<B.imag();
            else return false;
        }
    };
    T I[N],S1[1<<((N+1)/2)],S2[1<<((N+1)/2)]; map<T,vector<int>,Cmp> mp1,mp2;
    void solve(int n,int k){
        For(i,0,n-1) I[i]=T(cos(2*PI*i/n),sin(2*PI*i/n));
        mp1[0].push_back(0); mp2[0].push_back(0);
        For(s,1,(1<<(n/2))-1){
            int u=__builtin_ctz(s); S1[s]=S1[s^1<<u]+I[u]; mp1[S1[s]].push_back(s);
        }
        For(s,1,(1<<(n-n/2))-1){
            int u=__builtin_ctz(s); S2[s]=S2[s^1<<u]+I[u+n/2]; mp2[S2[s]].push_back(s);
        }
        ll ans=0; int cur=0; set<int> S;
        for(const auto& [_,v1]:mp1){
            if(!mp2.count(-_)) continue;
            const auto& v2=mp2[-_];
            for(int u:v1) for(int v:v2) {
                int siz=__builtin_popcount(u)+__builtin_popcount(v); S.insert(siz);
                if(siz<=k&&siz>cur){
                    cur=siz; ans=u|v<<(n/2);
                }
            }
        }
        debug(cur,S);
        For(i,0,n-1) cout<<(ans>>i&1);; cout<<'\n';
    }
}
namespace Solve2{
    void solve(int n,int k,int p){
        string ans(n,'0');
        For(i,0,k/p-1) For(j,0,p-1) ans[i+n/p*j]='1';
        cout<<ans<<'\n';
    }
}
namespace Solve3{
    void solve(int n,int k,int p1,int p2){
        string ans(n,'0');
        if(k/p1*p1>k/p2*p2){
            For(i,0,k/p1-1) For(j,0,p1-1) ans[i+n/p1*j]='1';
        }
        else{
            For(i,0,k/p2-1) For(j,0,p2-1) ans[i+n/p2*j]='1';
        }
        cout<<ans<<'\n';
    }
}
signed main(){
    Fin("ur.in"); Fout("ur.out");
    atexit([](){cerr<<"Time = "<<clock()<<" ms"<<endl;});
    int n,k; cin>>n>>k;
    if(k==n) return cout<<string(n,'1')<<'\n',0;
    if(k<=1) return cout<<string(n,'0')<<'\n',0;
    if(n<=36) return Solve1::solve(n,k),0;
    int nn=n,p[60]={0},c=0;
    For(i,2,nn) if(nn%i==0) { p[c++]=i; while(nn%i==0) nn/=i; }
    if(c==1) return Solve2::solve(n,k,p[0]),0;
    if(c==2) return Solve3::solve(n,k,p[0],p[1]),0;
    return 0;
}

// START TYPING IF YOU DON'T KNOW WHAT TO DO
// STOP TYPING IF YOU DON'T KNOW WHAT YOU'RE DOING
// CONTINUE, NON-STOPPING, FOR CHARLIEVINNIE

// Started Coding On: December 25 Mon, 17 : 52 : 00