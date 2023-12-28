#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod=998244353;
int n,q;
ll a[701][702],b[701][702];
ll inv(ll a){
    ll b=mod-2,r=1;
    while(b){
        if(b&1)r=r*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return r;
}
void solve(){
    memcpy(a,b,sizeof a);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(((j<i&&a[j][j]==0)||j>=i)&&a[j][i]!=0){
                swap(a[i],a[j]);
                break;
            }
        }
        if(a[i][i]==0)continue;
        ll d=inv(a[i][i]);
        for(int j=1;j<=n+1;j++)a[i][j]=a[i][j]*d%mod;
        for(int j=1;j<=n;j++){
            if(i==j)continue;
            d=mod-a[j][i];
            for(int k=1;k<=n+1;k++)
                a[j][k]=(a[j][k]+a[i][k]*d)%mod;
        }
    }
    bool many=0;
    for(int i=1;i<=n;i++){
        bool f=1;
        for(int j=1;j<=n;j++){
            if(a[i][j]!=0){
                f=0;
                break;
            }
        }
        if(f&&a[i][n+1]!=0){
            cout<<"No\n";
            return;
        }
        if(f)many=1;
    }
    if(many){
        cout<<"Many\n";
        return;
    }
    for(int i=1;i<=n;i++)cout<<a[i][n+1]<<' ';
    cout<<'\n';
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    freopen("eq.in","r",stdin);
    freopen("eq.out","w",stdout);
    cin>>n>>q;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n+1;j++)
            cin>>b[i][j];
    solve();
    while(q--){
        int i;
        cin>>i;
        for(int j=1;j<=n+1;j++)
            cin>>b[i][j];
        solve();
    }
    return 0;
}
