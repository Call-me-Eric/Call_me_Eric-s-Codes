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
const ll N=1e5;
ll ans[N+10];
ll p[N+10];
ll f[8][8];
ll a[10],b[10];
ll pto=0;
//
bool check(ll x,ll y){
    memset(f,0,sizeof(f));
    ll ato=0,bto=0;
    ll t=x;
    while(t) a[++ato]=t%10,t/=10;
    reverse(a+1,a+ato+1);
    t=y;
    while(t) b[++bto]=t%10,t/=10;
    reverse(b+1,b+bto+1);
    f[0][0]=1;
    FOR(i,1,ato){
        FOR(j,0,min(i-1,bto)){
            if(!f[i-1][j]) continue;
            f[i][j]=1;
            if(j!=bto&&a[i]==b[j+1]) f[i][j+1]=1;
        }
    }
    if(f[ato][bto]) return 0;
    return 1;
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
        // cerr<<"I:"<<i<<endl;
        ll S=sqrtl(i)+1;
        bool b=1;
        FOR(j,2,min(S,i-1)){
            if(i%j==0){
                b=0; break;
            }
        }
        if(b==1){
            // cerr<<"Is prime\n";
            FOR(j,1,pto) if(!check(i,p[j])){
                b=0; break;
            }
            if(b==0) continue;
            // cerr<<"Useful\n";
            p[++pto]=i; 
        }
        else{
            // cerr<<"Is not prime\n";
            FOR(j,1,pto) if(!check(i,p[j])){
                b=1; break;
            }
            if(b==1) continue;
            // cerr<<"ans\n";
            ans[i]=1;
        }
    }   
    ans[1]=1;
    FOR(i,1,N) ans[i]+=ans[i-1];
    (void)!freopen("prime.in","r",stdin);
    (void)!freopen("prime.out","w",stdout);
    ll T=gt();
    while(T--){
        ll l=gt(),r=gt();
        wr(ans[r]-ans[l-1]); putchar('\n');
    }
}