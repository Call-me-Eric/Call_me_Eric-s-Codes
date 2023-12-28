#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll mod=998244353;
int n,q,m;
int vis[705],id[705],quex[705];
ll A[705][705],B[705][705];
ll queval[705][705];
int pos[705],isok[705];
ll ans[705];
ll power(ll a,ll p){
    ll res=1;
    while(p){
        if(p&1)res=res*a%mod;
        p>>=1;
        a=a*a%mod;
    }
    return res;
}
void solve(){
    for(int i=1;i<=n;i++)for(int j=1;j<=n+1;j++)B[i][j]=A[i][j];
    int now=1;
    for(int i=1;i<=n;i++)if(!isok[i]){
        int p=0;
        for(int j=now;j<=m;j++)if(B[j][i]){p=j;break;}
        if(p){
            pos[now]=i;
            for(int j=i;j<=n+1;j++)swap(B[p][j],B[now][j]);
            ll val=power(B[now][i],mod-2);
            for(int j=i;j<=n+1;j++)B[now][j]=B[now][j]*val%mod;
            for(int j=now+1;j<=m;j++){
                ll val=B[j][i];
                for(int k=i;k<=n+1;k++)B[j][k]=(B[j][k]-B[now][k]*val%mod+mod)%mod;
            }
            now++;
        }
    }
    if(now<=m){
        for(int i=now;i<=m;i++)if(B[i][n+1])return puts("No"),void();
        return puts("Many"),void();
    }
    for(int i=m;i>=1;i--){
        for(int j=i-1;j>=1;j--){
            B[j][n+1]=(B[j][n+1]-B[j][pos[i]]*B[i][n+1]%mod+mod)%mod;
            B[j][pos[i]]=0;
        }
        for(int j=m+1;j<=n;j++){
            B[j][n+1]=(B[j][n+1]-B[j][pos[i]]*B[i][n+1]%mod+mod)%mod;
            B[j][pos[i]]=0;
        }
    }
    for(int i=1;i<=n;i++)ans[pos[i]]=B[i][n+1];
    for(int i=1;i<=n;i++)printf("%lld ",ans[i]);puts("");
}
int main(){
    freopen("eq.in","r",stdin);
    freopen("eq.out","w",stdout);
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)for(int j=1;j<=n+1;j++)scanf("%lld",&A[i][j]);
    for(int i=1;i<=q;i++){
        scanf("%d",&quex[i]);
        if(!vis[quex[i]])vis[quex[i]]=1;
        for(int j=1;j<=n+1;j++)scanf("%lld",&queval[i][j]);
    }
    for(int i=1;i<=n;i++)if(vis[i]){
        vis[i]=++m;
        for(int j=1;j<=n+1;j++)swap(A[m][j],A[i][j]);
    }
    for(int i=1;i<=q;i++)quex[i]=vis[quex[i]];
    int now=m+1;
    for(int i=1;i<=n;i++){
        int p=0;
        for(int j=now;j<=n;j++)if(A[j][i]){p=j;break;}
        if(p){
            pos[now]=i,isok[i]=1;
            for(int j=1;j<=n+1;j++)swap(A[now][j],A[p][j]);
            ll val=power(A[now][i],mod-2);
            for(int j=i;j<=n+1;j++)A[now][j]=A[now][j]*val%mod;
            for(int k=now+1;k<=n;k++){
                ll val=A[k][i];
                for(int j=i;j<=n+1;j++)A[k][j]=(A[k][j]-A[now][j]*val%mod+mod)%mod;
            }
            now++;
        }
    }
    if(now<=n){
        for(int i=now;i<=n;i++){
            for(int j=1;j<=n;j++)assert(A[i][j]==0);
            if(A[i][n+1]){
                for(int j=1;j<=q+1;j++)puts("No");
                return 0;
            }
        }
        for(int i=1;i<=q+1;i++)puts("Many");
        return 0;
    }
    for(int i=n;i>m;i--)
        for(int j=i-1;j>m;j--){
            ll val=A[j][pos[i]];
            for(int k=pos[i];k<=n+1;k++)A[j][k]=(A[j][k]-A[i][k]*val%mod+mod)%mod;
        }
    for(int i=m+1;i<=n;i++){
        assert(A[i][pos[i]]==1);
        for(int j=m+1;j<=n;j++)if(j!=i)assert(A[i][pos[j]]==0);
        for(int j=1;j<=m;j++){
            ll val=A[j][pos[i]];
            for(int k=pos[i];k<=n+1;k++)A[j][k]=(A[j][k]-A[i][k]*val%mod+mod)%mod;
        }
        for(int j=1;j<=q;j++){
            ll val=queval[j][pos[i]];
            for(int k=pos[i];k<=n+1;k++)queval[j][k]=(queval[j][k]-A[i][k]*val%mod+mod)%mod;
        }
    }
    solve();
    for(int i=1;i<=q;i++){
        for(int j=1;j<=n+1;j++)A[quex[i]][j]=queval[i][j];
        solve();
    }
    return 0;
}