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
const ll N=7e2+2,MOD=998244353;
ll n,q;
ll ans[N+10];
ll tans[N+10][N+10];
struct node{
    ll a[N+10];
    node(){memset(a,0,sizeof(a));}
};
inline ll ksm(ll x,ll y){
    ll rt=1,lx=x;
    while(y){
        if(y&1) rt=rt*lx%MOD;
        lx=lx*lx%MOD;
        y>>=1;
    }
    return rt;
}
struct SGT{
    #define ls (x<<1)
    #define rs ((x<<1)|1)
    vector<node> T[N*4+10];
    node AU;
    bool vis[N+10];
    ll apo[N+10];
    node d[N+10];
    ll dto=0;
    void add(ll x,ll l,ll r,ll ql,ll qr){
        if(ql<=l&&r<=qr) return T[x].pb(AU),void();
        if(ql<=mid) add(ls,l,mid,ql,qr);
        if(qr>mid) add(rs,mid+1,r,ql,qr);
    }
    void solve(ll x,ll l,ll r){
        // printf("SOLVE:[%lld,%lld]\n",l,r);
        for(auto U:T[x]){
            ++dto; d[dto]=U; 
            // printf("U\n");
            // FOR(i,1,n+1) printf("%lld ",U.a[i]);
            // printf("\n");
            // printf("\n");
            FOR(i,1,dto-1){
                ll u=apo[i];
                if(u==0) continue;
                ll t=d[dto].a[u];
                FOR(j,1,n+1) d[dto].a[j]+=MOD-d[i].a[j]*t%MOD,modj(d[dto].a[j]);
            }
            FOR(i,1,n){
                if(!vis[i]&&d[dto].a[i]){
                    apo[dto]=i; vis[i]=1; break;
                }
            }
            if(!apo[dto]) continue;
            ll u=apo[dto];
            ll t=ksm(d[dto].a[u],MOD-2);
            FOR(i,1,n+1) (d[dto].a[i]*=t)%=MOD;
            // FOR(i,1,dto){
            //     printf("D:%lld->",apo[i]);
            //     FOR(j,1,n+1){
            //         printf("%lld ",d[i].a[j]);
            //     }
            //     printf("\n");
            // }
            // printf("\n");
        }
        if(l==r){
            assert(dto==n); 
            // printf("L:%lld\n",l);
            // FOR(i,1,n){
            //     FOR(j,1,n+1){
            //         printf("%lld ",d[i].a[j]);
            //     }
            //     printf("\n");
            // }
            // printf("\n");
            FOR(i,1,n){
                bool b=0;
                FOR(j,1,n) if(d[i].a[j]!=0) b=1;
                if(b==0&&d[i].a[n+1]!=0) ans[l]=-1;
            }
            if(ans[l]==0){
                FOR(i,1,n) if(apo[i]==0) ans[l]=1e18;
                if(ans[l]==0){
                    ans[l]=1;
                    ROF(i,n,1){
                        ll z=d[i].a[n+1];
                        FOR(j,1,n){
                            if(j==apo[i]) continue;
                            z+=MOD-d[i].a[j]*tans[l][j]%MOD;
                            modj(z);
                        }
                        tans[l][apo[i]]=z;
                    }
                }
            } 
            ROF(i,dto,dto-(ll)T[x].size()+1) if(apo[i]) vis[apo[i]]=0,apo[i]=0;
            dto-=T[x].size();
            return;
        }
        solve(ls,l,mid);
        solve(rs,mid+1,r);
        ROF(i,dto,dto-(ll)T[x].size()+1) if(apo[i]) vis[apo[i]]=0,apo[i]=0;
        dto-=T[x].size();
    }
}T;
node c[N+10];
ll tim[N+10];
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
    usage();
    (void)!freopen("eq.in","r",stdin);
    (void)!freopen("eq.out","w",stdout);
    n=gt(),q=gt();
    FOR(i,1,n){
        FOR(j,1,n+1) c[i].a[j]=gt();
        tim[i]=1;
    }
    FOR(i,2,q+1){
        ll z=gt();
        T.AU=c[z]; T.add(1,1,q+1,tim[z],i-1);
        tim[z]=i;
        FOR(j,1,n+1) c[z].a[j]=gt();
    }
    FOR(i,1,n) T.AU=c[i],T.add(1,1,q+1,tim[i],q+1);
    T.solve(1,1,q+1);
    FOR(i,1,q+1){
        if(ans[i]==-1) printf("No\n");
        else if(ans[i]==1e18) printf("Many\n");
        else{
            assert(ans[i]==1);
            FOR(j,1,n) wr(tans[i][j]),putchar(' ');
            printf("\n");
        }
    }
    usage();
}