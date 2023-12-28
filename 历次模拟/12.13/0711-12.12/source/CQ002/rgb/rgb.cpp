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
    ll x,y,z;
};
const ll N=250,M=N*N+10,MAX=(1ll<<32)-1;
vector<node> side[N+10];
node ys[M+10];
ll fa[N+10];
ll f[5],g[5];
ll uic[M+10];
ll stac[N+10];
ll n,m,ans=0,pans=0,sto=0,cnt=0,TTT;
inline ll find(ll x){
    return fa[x]=(fa[x]==x)?x:find(fa[x]);
}
//
// namespace TEST{
//     string s;
//     void IN(){
//         cin>>s;
//     }
//     void YES(){
//         FOR(i,1,n) fa[i]=i;
//         memset(g,0,sizeof(g));
//         FOR(i,1,m){
//             if(!uic[i]) continue;
//             g[ys[i].z]++;
//             ll x=ys[i].x,y=ys[i].y;
//             ll fx=find(x),fy=find(y);
//             assert(fx!=fy);
//             fa[fx]=fy;
//         }
//         FOR(i,1,3) assert(f[i]==g[i]);
//         FOR(i,1,n) assert(find(i)==find(1));
//         assert(TTT<=1);
//     }
//     void NO(){
//         if(s[0]=='Y') exit(1);
//     }
// }
void check(){
    ans=0;
    FOR(i,1,3) ans+=abs(f[i]-g[i]);
    if(ans!=0) return;
    printf("YES\n");
    FOR(i,1,m) printf("%lld",uic[i]);
    // TEST::YES();
    cerr<<cnt<<endl;
    exit(0);
}
bool dfs(ll yx,ll x,ll tar){
    if(x==tar) return 1;
    for(auto u:side[x]){
        ll tox=u.x,toz=u.z;
        if(tox==yx) continue;
        stac[++sto]=toz; 
        if(dfs(x,tox,tar)) return 1;
        --sto;
    }
    return 0;
}
inline void erase(ll ord){
    ll x=ys[ord].x,y=ys[ord].y;
    FOR(i,0,(ll)side[x].size()-1){
        node u=side[x][i];
        if(u.x==y){
            if(i!=(ll)side[x].size()-1) swap(side[x][i],side[x][(ll)side[x].size()-1]);
            side[x].pop_back();
            break;
        }
    }
    swap(x,y);
    FOR(i,0,(ll)side[x].size()-1){
        node u=side[x][i];
        if(u.x==y){
            if(i!=(ll)side[x].size()-1) swap(side[x][i],side[x][(ll)side[x].size()-1]);
            side[x].pop_back();
            break;
        }
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
    mt19937 rnd(14530529);
    (void)!freopen("rgb.in","r",stdin);
    (void)!freopen("rgb.out","w",stdout);
    f[1]=gt(); f[2]=gt(); f[3]=gt();
    m=gt(); n=f[1]+f[2]+f[3]+1;
    FOR(i,1,m){
        ll x=gt(),y=gt(),z=0; string s; cin>>s;
        if(s[0]=='r') z=1;
        if(s[0]=='g') z=2;
        if(s[0]=='b') z=3;
        if(f[z]==0){
            --i; --m; continue;
        }
        ys[i]=(node){x,y,z};
    }
    // TEST::IN();
    FOR(TT,1,2){
        TTT=TT;
        shuffle(ys+1,ys+m+1,mt19937(rnd()));
        FOR(i,1,n) fa[i]=i;
        FOR(i,1,n) side[i].clear();
        memset(g,0,sizeof(g));
        memset(uic,0,sizeof(uic));
        FOR(i,1,m){
            ll x=ys[i].x,y=ys[i].y,z=ys[i].z;
            ll fx=find(x),fy=find(y);
            if(fx!=fy){
                fa[fx]=fy;
                side[x].pb((node){y,i,i});
                side[y].pb((node){x,i,i});
                ++g[z];
            }
        }
        bool havnoans=0;
        FOR(i,1,n) if(find(i)!=find(1)) havnoans=1;
        if(havnoans){
            printf("NO\n");
            return 0;
        }
        FOR(i,1,n) for(auto u:side[i]) uic[u.z]=1;
        check();
        if(m==n-1){
            printf("NO\n");
            return 0;
        }
        for(double T=1; T>=0.0001; T*=0.99998){
            ++cnt;
            pans=ans;
            ll ord=rnd()%m+1;
            if((double)m/(double)(m-n+1)>=20){
                ord=rnd()%(m-n+1)+1; ll t=0;
                FOR(i,1,m){
                    if(uic[i]) continue;
                    ++t;
                    if(t==ord){
                        ord=i; break;
                    }
                }
            }
            while(uic[ord]) ord=rnd()%m+1;
            sto=0; 
            ll rt=dfs(ys[ord].x,ys[ord].x,ys[ord].y);
            assert(rt==1);
            ll ord2=stac[rnd()%sto+1];
            swap(ord,ord2);
            uic[ord]=0; uic[ord2]=1;
            --g[ys[ord].z]; ++g[ys[ord2].z];
            check();
            if(ans<=pans||(double)rnd()/(double)MAX<=T){
                erase(ord);
                side[ys[ord2].x].pb((node){ys[ord2].y,ord2,ord2});
                side[ys[ord2].y].pb((node){ys[ord2].x,ord2,ord2});
            }
            else{
                uic[ord]=1; uic[ord2]=0;
                ++g[ys[ord].z]; --g[ys[ord2].z];
                ans=pans;
            }
        }
    }
    usage();
    cerr<<cnt<<endl;
    // TEST::NO();
    printf("NO\n");
}