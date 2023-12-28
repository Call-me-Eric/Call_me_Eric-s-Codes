#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
int n,k;
int ans[N];
int prime[N],minn[N],cnt,tot;
vector<pair<int,int>>f;
inline void Init(int x){
    for(int i=2;i<N;i++){
        if(!minn[i])minn[i]=i,prime[++cnt]=i;
        for(int j=1;j<=cnt&&prime[j]*i<N;j++){
            minn[prime[j]*i]=prime[j];
            if(i%prime[j]==0)break;
        }
    }
    while(x!=1){
        int mod=minn[x];
        int sum=0;
        while(x%mod==0){
            x/=mod;
            sum++;
        }
        f.push_back(make_pair(mod,sum));
        // cerr<<mod<<endl;
    }
    tot=f.size();
}
int sum;
int main(){
    freopen("ur.in","r",stdin);
    freopen("ur.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>k;
    Init(n);
    if(n==k){
        for(int i=1;i<=n;i++){
            ans[i]=1;
        }
    }
    else if(k<=1){
        for(int i=1;i<=n;i++){
            ans[i]=0;
        }
    }
    else if(tot==1&&f[0].second==1){
        for(int i=1;i<=n;i++){
            ans[i]=0;
        }
    }
    else{
        int maxn=0,mod;
        for(pair<int,int> u:f){
            int Mod=u.first;
            int P=k/Mod;
            sum=Mod*P;
            if(maxn<sum){
                maxn=sum;
                mod=Mod;
            }
        }
        sum=0;
        // cerr<<mod<<endl;
        int p=k/mod;
        mod=n/mod;
        // cerr<<p<<endl;
        for(int i=1;i<=p;i++){
            for(int pos=i;pos<=n;pos+=mod){
                ans[pos]=1;
                sum++;
            }
        }
        // cerr<<sum<<endl;
        // assert(sum<=k);
        // for(int i=1;i<=n;i++){
            // if((i%mod+1)<=p)ans[i]=1,sum++;
            // else ans[i]=0;
        // }
        
    }
    for(int i=1;i<=n;i++)
        cout<<ans[i];
    return 0;
}

// 111111111111111101
// 111111111111111101