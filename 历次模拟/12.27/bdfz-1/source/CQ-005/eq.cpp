#include<bits/stdc++.h>
using namespace std;
const int maxn=702;
const long long mod=998244353;
int n,Q;
long long coe[maxn][maxn],con[maxn],pase[maxn][maxn],pasn[maxn];
long long f_pow(long long x,long long p){
    long long ret=1ll;
    while(p){
        if(p%2)ret=ret*x%mod;
        x=x*x%mod;
        p/=2;
    }
    return ret;
}
void out(){
    printf("#######\n");
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            printf("%lld ",coe[i][j]);
        }
        printf("%lld\n",con[i]);
    }
    return ;
}
int gauss(){
    // printf("start!\n");
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++)coe[i][j]=pase[i][j];
        con[i]=pasn[i];
    }
    // out();
    for(int i=1,pos;i<=n;i++){
        pos=-1;
        for(int j=i;j<=n;j++)if(coe[j][i]>0)pos=j;
        if(pos==-1)continue;
        swap(coe[pos],coe[i]);
        swap(con[pos],con[i]);
        // printf("swap %d %d\n",pos,i);
        long long inv=f_pow(coe[i][i],mod-2),mul;
        for(int j=1;j<=n;j++){
            if(j==i)continue;
            mul=coe[j][i]*inv%mod;
            for(int k=i;k<=n;k++)coe[j][k]=(coe[j][k]-coe[i][k]*mul%mod+mod)%mod;
            con[j]=(con[j]-con[i]*mul%mod+mod)%mod;
        }
        // printf("after %d\n",i);
        // out();
    }
    for(int i=1;i<=n;i++){
        if(coe[i][i]==0)return (con[i]==0)?1:2;
        con[i]=con[i]*f_pow(coe[i][i],mod-2)%mod;
    }
    // printf("before return \n");
    // out();
    return 0;
}
void solve(){
    int ret=gauss();
    // printf("back \n");
    if(ret==2)printf("No\n");
    else if(ret==1)printf("Many\n");
    else {
        for(int i=1;i<=n;i++)printf("%lld ",con[i]);
        printf("\n");
    }
    return ;
}
int main(){
    freopen("eq.in","r",stdin);
    freopen("eq.out","w",stdout);
    scanf("%d%d",&n,&Q);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++)scanf("%lld",&pase[i][j]);scanf("%lld",&pasn[i]);
    }
    solve();
    int x;
    long long v;
    for(int i=1;i<=Q;i++){
        scanf("%d",&x);
        for(int j=1;j<=n;j++){
            scanf("%lld",&v);
            pase[x][j]=v;
        }
        scanf("%lld",&v);
        pasn[x]=v;
        solve();
    }
    return 0;
}