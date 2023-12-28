/*Mlm:  Tlm:*/
#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define mid ((l+r)>>1)
#define FOR(i,a,b) for(long long i=(a); i<=(b); ++i)
#define ROF(i,a,b) for(long long i=(a); i>=(b); --i)
#define modj(x) ((x)-=((x)>=MOD)?MOD:0)
using namespace std;
bool h1;
double time1=(double)clock()/CLOCKS_PER_SEC;
//
const ll N=20,MOD=998244353;
map<vector<ll>,ll> dp[N+10];
ll a[N+10],b[N+10];
//
//
inline char gc(){
    static char buf[100000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
inline ll gt(){
    ll t=0,f=0;char v=getchar();
    while(!isdigit(v))f|=(v=='-'),v=getchar();
    while(isdigit(v))t=(t<<3)+(t<<1)+v-48,v=getchar();
    return f?-t:t;
}
inline void wr(ll x){
    if(x<0){x*=-1; putchar('-');}
    if(x>9) wr(x/10);
    putchar(x%10+'0');
    return;
}
bool H1;
void usage() {
    double time2=(double)clock()/CLOCKS_PER_SEC;
    cerr<<(&H1-&h1)/1024/1024<<" Mb,"<<time2-time1<<" s\n";
}
int main() {
    (void)!freopen("young.in","r",stdin);
    (void)!freopen("young.out","w",stdout);
    ll n=gt();
    FOR(i,1,n) a[i]=gt();
    ll m=gt();
    FOR(i,1,m) b[i]=gt();
    vector<ll> S;
    FOR(i,1,n) S.pb(a[i]);
    dp[0][S]=1;
    ll q=gt(); assert(q==1);
    ll K=gt();
    S.clear();
    FOR(i,1,m) S.pb(b[i]);
    FOR(Tim,0,K-1){
        for(auto u:dp[Tim]){
            auto T=u.first;
            ll z=u.second;
            FOR(i,0,(ll)T.size()-1){
                auto toT=T;
                if(i==0||toT[i]<toT[i-1]){
                    toT[i]++;
                    dp[Tim+1][toT]+=z;
                    modj(dp[Tim+1][toT]);
                    toT=T;
                } 
                if(i==(ll)T.size()-1||toT[i]>toT[i+1]){
                    if(toT[i]==1){
                        assert(i==(ll)T.size()-1);
                        toT.pop_back();
                    } 
                    else toT[i]--;
                    dp[Tim+1][toT]+=z;
                    modj(dp[Tim+1][toT]);
                    toT=T;
                }
            }
            auto toT=T;
            toT.pb(1);
            dp[Tim+1][toT]+=z;
            modj(dp[Tim+1][toT]);
        }
    }
    cout<<dp[K][S];
}