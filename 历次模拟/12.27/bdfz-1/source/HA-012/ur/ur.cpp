#include<bits/stdc++.h>
#define ll long long
#define uit unsigned int
using namespace std;
template<typename T>void read(T &x){
    x=0;char c=getchar();
    for(;c<'0'||c>'9';c=getchar()) ;
    for(;c>='0'&&c<='9';c=getchar()) x=(x<<1)+(x<<3)+(c^48);
}
const int N=1e6+10,INF=1e9,V=1e6;
bool memory_be;
int n,K,pn=0,p[N],mn[N];bool nop[N];
void GetP(){
    nop[1]=1;
    for(int i=2;i<=V;i++){
        if(!nop[i]){p[++pn]=i;mn[i]=i;}
        for(int j=1;j<=pn&&1ll*p[j]*i<=V;j++){
            nop[i*p[j]]=1;
            if(!(i%p[j])){
                mn[i*p[j]]=mn[i];break;
            }
            mn[i*p[j]]=p[j];
        }
    }
}
namespace task1{
    vector<ll> vec[40];vector<int> D;
    int seq[N],ans=INF;ll ansmask=0;
    void Deal(const int d){
        int cnt=0;
        for(int i=1;i<=n;i+=n/d){
            seq[++cnt]=i;
        }
        for(int i=0;i<n/d;i++){
            ll mask=0;
            for(int j=1;j<=cnt;j++){
                int u=seq[j]+i;
                mask|=(1ll<<(u-1));
            }
            vec[d].emplace_back(mask);
           // cout<<d<<' '<<mask<<endl;
        }
    }
    void Init(){
        for(int i=2;i<=n;i++){
            if(nop[i]) continue;
            if((n%i)) continue;
            D.emplace_back(i);
            Deal(i);
        }
    }
    namespace HS{
        const int mod=1e7+7;
        int tot=0,head[mod];ll e[1100000];int nex[1100000];
        void Ins(ll mask){
            int key=mask%mod;
            for(int i=head[key];i;i=nex[i]){
                if(e[i]==mask) return ;
            }
            ++tot;nex[tot]=head[key];head[key]=tot;e[tot]=mask;
        }
        int ask(ll mask){
            int key=mask%mod;
            for(int i=head[key];i;i=nex[i]){
                if(e[i]==mask) return 1;
            }
            return 0;
        }
    }
    void dfs(const ll now,const int lev){
        if(HS::ask(now)) return ;
        HS::Ins(now);
        if(lev<ans) ansmask=now;
        ans=min(ans,lev);
        for(auto d:D){
            if(d>lev) break;
            for(auto mask:vec[d]){
                if((now&mask)==0){
                    dfs(now^mask,lev-d);
                }
            }
        }
    }
    void sol(){
        Init();
        ans=INF;
        dfs(0,K);
        //printf("%d\n",K-ans);
//        cerr<<"[cerr] ansnum:"<<K-ans<<' '<<"all f num:"<<debug<<'\n';
        for(int i=1;i<=n;i++) printf("%lld",(ansmask>>(i-1))&1ll);printf("\n");
    }
}
namespace task2{
    bool sub_check(){
        int x=n,o=mn[x];
        while(!(x%o)) x/=o;
        return x==1;
    }
    int seq[N];
    void sol(){
        int tmp=0;
        while(tmp*mn[n]<=K) ++tmp;
        for(int i=1;i<=tmp;i++){
            for(int j=i;j<=n;j+=n/mn[n]){
                seq[j]=1;
            }
        }
        for(int i=1;i<=n;i++) printf("%d",seq[i]);printf("\n");
    }
}
bool memory_ed;
int main(){
    freopen("ur.in","r",stdin);
    freopen("ur.out","w",stdout);
    cerr<<"[cerr] memory use:"<<(&memory_ed-&memory_be)/1024/1024<<'\n';
    GetP();
    scanf("%d%d",&n,&K);
    if(n<=36){
        task1::sol();return 0;
    }
    if(n==K){
        for(int i=1;i<=n;i++) printf("1");printf("\n");
        return 0;
    }
    if(K<=1){
        for(int i=1;i<=n;i++) printf("0");printf("\n");
        return 0;
    }
    if(!nop[n]){
        for(int i=1;i<=n;i++) printf("0");printf("\n");
    }
    if(task2::sub_check()){
        task2::sol();return 0;
    }
    return 0;
}
