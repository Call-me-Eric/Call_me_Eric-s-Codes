#include<bits/stdc++.h>
#define N 710
#define MOD 998244353
using namespace std;
int n,q,a[N][N],b[N][N];
int qpow(int a,int b){
    int ans=1;
    while(b){
        if(b&1)ans=1ll*ans*a%MOD;
        a=1ll*a*a%MOD;
        b>>=1;
    }
    return ans;
}
int ans[N];
void solve(){
    for(int i=1;i<=n;i++){
        int j=i;
        while(j<=n&&!a[j][i])j++;
        if(j<=n){
            for(int k=i;k<=n+1;k++)swap(a[i][k],a[j][k]);
            int inv = qpow(a[i][i],MOD-2);
            for(int k=i+1;k<=n;k++){
                int v = 1ll*a[k][i]*inv%MOD;
                for(int l=i;l<=n+1;l++){
                    a[k][l]=(a[k][l]-1ll*a[i][l]*v%MOD+MOD)%MOD;
                }
            }
        }
    }
    bool flag=0;
    for(int i=n;i>=1;i--){
        for(int j=i+1;j<=n;j++)a[i][n+1]=(a[i][n+1]-1ll*ans[j]*a[i][j]%MOD+MOD)%MOD;
        if(!a[i][i]&&!a[i][n+1]){
            flag=1;
            continue;
        }
        if(!a[i][i]){
            cout<<"No"<<'\n';
            return;
        }
        ans[i]=1ll*a[i][n+1]*qpow(a[i][i],MOD-2)%MOD;
    }
    if(flag){
        cout<<"Many"<<'\n';
        return;
    }
    for(int i=1;i<=n;i++)cout<<ans[i]<<" ";
    cout<<'\n';
}
int main(){
    freopen("eq.in","r",stdin);
    freopen("eq.out","w",stdout);
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>q;
    for(int i=1;i<=n;i++)
    for(int j=1;j<=n+1;j++)cin>>b[i][j];
    memcpy(a,b,sizeof(b));
    solve();
    for(int i=1;i<=q;i++){
        int x;
        cin>>x;
        for(int j=1;j<=n+1;j++)cin>>b[x][j];
        memcpy(a,b,sizeof(b));
        solve();
    }
    return 0;
}