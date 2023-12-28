#include<bits/stdc++.h>
#define int long long 
using namespace std;
int T;
int l,r;
bool b[100005];
int prime[100005];
bool bl[100005];
int num;
int t[55];
signed main(){
    ios::sync_with_stdio(0);
    freopen("prime.in","r",stdin);
    freopen("prime.out","w",stdout);
    cin>>T;
    b[0]=b[1]=1;
    for(int i=2;i<=100001;++i){
        if(!b[i])prime[++num]=i;
        for(int j=1;j<=num and i*prime[j]<=100001;++j){
            b[i*prime[j]]=1;
            if(i%prime[j]==0)break;
        }
    }
    bl[1]=1;
    for(int i=2;i<=100000;++i){
        bl[i]=1;
        int tp=i;
        num=0;
        while(tp){
            t[++num]=tp%10;
            tp/=10;
        }
        for(int j=1;j<(1<<num);++j){
            int tp=0;
            for(int k=num;k;--k){
                if(j&(1<<k-1))tp*=10,tp+=t[k];
            }
            if(!b[tp]){bl[i]=0;if(i==40)cout<<j<<'\n';break;}
        }
    }
    while(T--){
        cin>>l>>r;
        int ans=0;
        for(int i=l;i<=r;++i)ans+=bl[i];
        cout<<ans<<"\n";
    }
    return 0;
}