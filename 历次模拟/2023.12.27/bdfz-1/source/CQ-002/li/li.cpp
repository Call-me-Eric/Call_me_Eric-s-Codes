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
const ll N=2e5;
ll buc[N+10];
vector<ll> side[N+10];
bool vis[N+10];
ll stac[N+10];
ll b=0,quanb=1,sto=0;
//
void dfs(ll x){ vis[x]=1; ++sto; stac[sto]=x;
    if(side[x].size()>=4) b=max(b,2ll);
    if(side[x].size()==3) b=max(b,1ll);
    if(side[x].size()<2||side[x].size()>2) quanb=0;
    for(auto tox:side[x]){
        if(vis[tox]) continue;
        dfs(tox); 
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
    //链，环，三度点，三度点+1，大于等于四度点
    freopen("li.in","r",stdin);
    freopen("li.out","w",stdout);
    ll n=gt(),m=gt();
    FOR(i,1,m){
        ll x=gt(),y=gt();
        side[x].pb(y);
        side[y].pb(x);
    }
    ll havans=1,dt=0;
    FOR(i,1,n){
        if(!vis[i]){
            b=0; sto=0; quanb=1; dfs(i); 
            // printf("%lld %lld\n",b,quanb);
            // FOR(j,1,sto) printf("%lld ",stac[j]);
            // printf("\n");
            if(b==1){
                if(sto==4) ++buc[1],++dt,quanb=1;
                else b=2;
            }
            if(!quanb) buc[sto]++,++dt;
            if(b==2) havans=0;
        }
    }
    if(!havans) return printf("-1\n"),0;
    ll tot=n,nown=n;
    FOR(i,1,n){
        nown-=dt;
        tot+=nown;
        dt-=buc[i];
    }
    if(nown==0){
        printf("0 %lld\n",tot);
    }
    else{
        printf("1 %lld\n",nown);
    }
}