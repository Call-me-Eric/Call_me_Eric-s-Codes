#include <bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
int n,m,q,k,num[65],b[65],ans;
int get(){
    int ret=0;
    for(int i=1;i<=n+k;i++){
        ret+=abs(num[i]-b[i]);
    }
    return ret;
}
void dfs(int st){
    if(get()>st)return;
    if(!st){
        ans++;
        return;
    }
    for(int i=1;i<=n+k;i++){
        if(num[i]<num[i-1]||i==1){
            num[i]++;
            dfs(st-1);
            num[i]--;
        }
        if(num[i]>num[i+1]){
            num[i]--;
            dfs(st-1);
            num[i]++;
        }
    }
}
signed main(){
    freopen("young.in","r",stdin);
    freopen("young.out","w",stdout);
    cin>>n;
    for(int i=1;i<=n;i++)cin>>num[i];
    cin>>m;
    for(int i=1;i<=m;i++)cin>>b[i];
    cin>>q;
    while(q--){
        cin>>k;
        ans=0;
        dfs(k);
        printf("%lld\n",ans);
    }
    return 0;
}