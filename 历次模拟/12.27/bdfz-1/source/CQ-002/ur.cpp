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
struct node{
    ll x,y;
};
const ll N=1e6;
ll n,m,ans;
ll orip[N+10],pre[N+10];
node p[N+10];
bool vis[N+10];
ll opto=0,pto=0;
vector<ll> outans;
vector<ll> outans2;
//
namespace BRUTE{
    const ll M=11;
    ll p[M+1];
    bool vis[40];
    ll pto=0;
    ll ans=0;
    vector<ll> outans;
    void dfs(ll x,ll y,ll z){
        if(y>=n/p[x]) ++x,y=0;
        if(x==pto+1) return;
        // printf("DFS:%lld %lld %lld\n",x,y,z);
        // FOR(i,1,n) printf("%lld",vis[i]);
        // printf("\n");
        if(z>ans){
            ans=z;
            outans.clear();
            FOR(i,1,n) outans.pb(vis[i]);
        }
        bool b=0;
        ll tz=z;
        for(ll i=y; i<=n; i+=n/p[x]){
            if(i==0) continue;
            ++tz;
            if(vis[i]){
                b=1; break;
            } 
        }
        if(tz>m) b=1;
        if(!b){
            tz=z;
            for(ll i=y; i<=n; i+=n/p[x]){
                if(i==0) continue;
                vis[i]=1;
                ++tz;
            }
            dfs(x,y+1,tz);
            for(ll i=y; i<=n; i+=n/p[x]){
                if(i==0) continue;
                vis[i]=0;
            }
        }
        dfs(x,y+1,z);
    }
    ll solve(){
        pto=0; memset(vis,0,sizeof(vis)); ans=0; outans.clear();
        FOR(i,1,opto){
            if(n<orip[i]) break;
            if(n%orip[i]==0) p[++pto]=orip[i];
        }
        reverse(p+1,p+pto+1);
        // FOR(i,1,pto) printf("%lld ",p[i]);
        // printf("\n");
        FOR(i,1,n) outans.pb(0);
        dfs(1,0,0);
        ::outans=outans;
        return ans;
    }
}
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
    FOR(i,2,N){
        if(!pre[i]){
            orip[++opto]=i;
            pre[i]=i;
        }
        FOR(j,1,opto){
            if(i*orip[j]>N) break;
            pre[i*orip[j]]=orip[j];
            if(!(i%orip[j])) break;
        }
    }
    (void)!freopen("ur.in","r",stdin);
    (void)!freopen("ur.out","w",stdout);
    n=gt(),m=gt();
    if(m==n){
        FOR(i,1,n) printf("1");
        printf("\n");
        // printf("%lld\n",1);
        return 0;
    }
    if(m<=1){
        FOR(i,1,n) printf("0");
        printf("\n");
        // printf("%lld\n",0);
        return 0;
    }
    ll tn=n;
    outans.pb(0); FOR(i,1,n) outans.pb(0);
    FOR(i,1,opto){
        if(!(tn%orip[i])){
            ll z=0;
            while(!(tn%orip[i])) tn/=orip[i],++z;
            p[++pto]=(node){orip[i],z};
        }
    }
    // cout<<pto<<endl;
    // printf("%lld %lld\n",p[1].x,p[2].x);
    if(pto==1){
        ll gp=n/p[1].x,t=m/p[1].x;
        FOR(i,1,t) outans[i]=1;
        FOR(i,gp+1,n) if(outans[i-gp]) outans[i]=1;
        FOR(i,1,n) printf("%lld",outans[i]);
        printf("\n");
        // printf("%lld\n",t*p[1].x);
        return 0;
    }
    if(n<=36) {
        ans=BRUTE::solve();
        for(auto x:outans) printf("%lld",x);
        printf("\n");
        return 0;
    }
}