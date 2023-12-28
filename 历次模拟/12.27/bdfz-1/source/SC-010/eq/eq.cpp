#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,q,ma[705][705],ans[705],fc[705][705];
const int mod=998244353;
int qp(int a,int k){
    int ret=1;
    for(;k;k>>=1){
        if(k&1)ret=ret*a%mod;
        a=a*a%mod;
    }
    return ret;
}
int gauss(){
    memcpy(ma,fc,sizeof(ma));
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            if(i==j)continue;
            while(ma[i][i]){
                int t=ma[j][i]/ma[i][i];
                for(int k=i;k<=n+1;k++){
                    ma[j][k]=(ma[j][k]-ma[i][k]*t%mod+mod)%mod;
                }
                swap(ma[i],ma[j]);
            }
            swap(ma[i],ma[j]);
        }
    }
    int dj=0;
    for(int i=n;i;i--){
        if(!ma[i][i]&&ma[i][n+1])return 0;
        if(!ma[i][i])dj=1;
        ans[i]=qp(ma[i][i],mod-2)*ma[i][n+1]%mod;
        for(int j=1;j<i;j++)ma[j][n+1]=(ma[j][n+1]-ans[i]*ma[j][i]%mod+mod)%mod;
    }
    if(dj)return 2;
    return 1;
}
void print(int t){
    if(t==0)puts("No");
    else if(t==2)puts("Many");
    else{
        for(int i=1;i<=n;i++)printf("%lld ",ans[i]);
        puts("");
    }
}
signed main(){
    freopen("eq.in","r",stdin);
    freopen("eq.out","w",stdout);
    cin>>n>>q;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n+1;j++){
            scanf("%lld",&fc[i][j]);
        }
    }
    print(gauss());
    while(q--){
        int x;scanf("%lld",&x);
        for(int i=1;i<=n+1;i++)scanf("%lld",&fc[x][i]);
        print(gauss());
    }
    return 0;
}