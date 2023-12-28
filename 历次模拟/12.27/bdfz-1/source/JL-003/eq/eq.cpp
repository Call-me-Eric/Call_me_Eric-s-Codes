#include<bits/stdc++.h>
#define ll long long
#define endl '\n'
using namespace std;
const int N=705;
const int mod=998244353;
inline int q_pow(int a,int b){
    static int ret;
    ret=1;
    while(b){
        if(b&1)ret=1ll*ret*a%mod;
        a=1ll*a*a%mod;
        b>>=1;
    }
    return ret;
}
inline int Inv(const int &x){
    return q_pow(x,mod-2);
}
inline void Sub(int &x,const int y){
    x+y>=mod?x=x+y-mod:x=x+y;
}
int n,q;
int a[N][N],b[N];
int x[N];
int tmpa[N][N],tmpb[N];
inline void Solve(){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++)
            a[i][j]=tmpa[i][j];
        b[i]=tmpb[i];
        x[i]=0;
    }
    for(int i=1;i<=n;i++){
        int pos=i;
        for(int j=1;j<=n;j++){
            if(a[j][i]>a[pos][i])pos=j;
        }
        for(int j=i;j<=n+1;j++)
            swap(a[pos][j],a[i][j]);
        swap(b[pos],b[i]);
        if(a[i][i]==0)
            continue;
        for(int j=1;j<=n;j++){
            if(i==j)continue;
            int div=1ll*a[j][i]*Inv(a[i][i])%mod;
            for(int k=1;k<=n;k++){
                Sub(a[j][k],1ll*a[i][k]*div%mod);
            }
            Sub(b[j],1ll*b[i]*div%mod);
        }
    }
    for(int i=1;i<=n;i++){
        if(a[i][i]==0){
            if(b[i]==0)cout<<"Many"<<endl;
            else cout<<"No"<<endl;
            return ;
        }
        x[i]=1ll*b[i]*Inv(a[i][i])%mod;
    }
    for(int i=1;i<=n;i++){
        cout<<x[i]<<' ';
    }
    cout<<endl;
    return ;
}
inline void solve1(){
    static int a,b;
    cin>>a>>b;
    if(a==0){
        if(b==0)cout<<"Many"<<endl;
        else cout<<"No"<<endl;
    }
    else cout<<1ll*b*Inv(a)%mod<<endl;
    while(q--){
        static int id,A,B;
        cin>>id>>A>>B;
        a=A,b=B;
        if(a==0){
            if(b==0)cout<<"Many"<<endl;
            else cout<<"No"<<endl;
        }
        else cout<<1ll*b*Inv(a)%mod<<endl;
    }
    return ;
}
int main(){
    freopen("eq.in","r",stdin);
    freopen("eq.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>q;
    if(n==1){
        solve1();
        return 0;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>tmpa[i][j];
        }
        cin>>tmpb[i];
    }
    Solve();
    while(q--){
        static int id;
        cin>>id;
        for(int i=1;i<=n;i++){
            static int ch;
            cin>>ch;
            tmpa[id][i]=ch;
        }
        cin>>tmpb[id];
        Solve();
    }
    return 0;
}