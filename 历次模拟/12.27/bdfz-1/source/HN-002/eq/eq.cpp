#include<bits/stdc++.h>
using namespace std;
const int mod=998244353;
int n,q,bhh[710],wjtm=-1,cnt;
long long ans[710];
struct FC{
    int tm;
    long long a[710];
    void cpy(FC &x){tm=x.tm;
        for(int i=0;i<=n;i++)a[i]=x.a[i];
    }
}xxj[710],fc[1410];
long long ksm(long long x,long long y){
    long long gc=x,jg=1;
    while(y){
        if(y&1)jg=(jg*gc)%mod;
        gc=(gc*gc)%mod;y>>=1;
    }return jg;
}
void cr(FC &x){
    for(int i=1;i<=n;i++){
        if(!x.a[i])continue;
        if(xxj[i].tm==-1){xxj[i].cpy(x);cnt++;return;}
        if(xxj[i].tm<x.tm)swap(xxj[i],x);
        long long ny=(ksm(x.a[i],mod-2)*xxj[i].a[i])%mod;
        for(int j=i;j<=n;j++)x.a[j]=(x.a[j]*ny-xxj[i].a[j])%mod;
        x.a[0]=(x.a[0]*ny-xxj[i].a[0])%mod;
    }if(x.a[0])wjtm=max(wjtm,x.tm);
}
void del(int x){
    for(int i=1;i<=n;i++){
        if(xxj[i].tm!=-1&&xxj[i].tm<x){xxj[i].tm=-1;cnt--;}
    }
}
void work(){
    for(int i=n;i>=1;i--){
        long long qw=xxj[i].a[0];
        for(int j=n;j>i;j--){
            qw=(qw-xxj[i].a[j]*ans[j])%mod;
        }ans[i]=(qw*ksm(xxj[i].a[i],mod-2))%mod;
    }
}
int main(){
    freopen("eq.in","r",stdin);
    freopen("eq.out","w",stdout);
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++)scanf("%lld",&fc[i].a[j]);
        scanf("%lld",&fc[i].a[0]);fc[i].tm=q+1;
        bhh[i]=i;
    }
    for(int i=1;i<=n;i++)xxj[i].tm=-1;
    for(int i=n+1;i<=n+q;i++){
        int x;scanf("%d",&x);fc[bhh[x]].tm=i-n-1;
        for(int j=1;j<=n;j++)scanf("%lld",&fc[i].a[j]);
        scanf("%lld",&fc[i].a[0]);fc[i].tm=q+1;
        bhh[x]=i;
    }
    for(int i=1;i<n;i++){
        cr(fc[i]);
    }
    for(int i=n;i<=n+q;i++){
        del(i-n);
        cr(fc[i]);
        if(wjtm>=i-n){puts("No");continue;}
        if(cnt<n){puts("Many");continue;}
        work();
        for(int j=1;j<=n;j++)printf("%lld ",(ans[j]+mod)%mod);
        puts("");
    }return 0;
}