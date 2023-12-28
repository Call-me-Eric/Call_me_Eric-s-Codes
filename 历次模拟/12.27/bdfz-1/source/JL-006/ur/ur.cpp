#include<bits/stdc++.h>
using namespace std;
int n,k,mx,T;
bitset<1000000>ans,cur;
vector<int>v;
void dfs(int x,int num){
    if(x==n){
        if(num>mx){
            mx=num,ans=cur;
        }
        return;
    }
    for(auto d:v){
        T++;
        if(x-d>=0||num+n/d>k)continue;
        bool flag=1;
        for(int c=x;c<n&&flag;c+=d)flag&=!cur[c],T++;
        if(!flag)continue;
        for(int c=x;c<n;c+=d)cur[c]=1;
        dfs(x+1,num+n/d);
        if(T>100000000){
            for(int i=0;i<n;i++)cout<<ans[i];
            cout<<'\n';
            exit(0);
        }
        for(int c=x;c<n;c+=d)cur[c]=0;
    }
    dfs(x+1,num);
}
bool isprime(int x){
    for(int i=2;i*i<=x;i++)if(x%i==0)return 0;
    return 1;
}
int main(){
    freopen("ur.in","r",stdin);
    freopen("ur.out","w",stdout);
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>k;
    if(n==k){
        for(int i=1;i<=n;i++)cout<<1;
        cout<<'\n';
        exit(0);
    }
    if(k==1){
        for(int i=1;i<=n;i++)cout<<0;
        cout<<'\n';
        exit(0);
    }
    for(int i=2;i<n;i++){
        if(n%i==0&&isprime(n/i))v.push_back(i);
    }
    dfs(0,0);
    for(int i=0;i<n;i++)cout<<ans[i];
    cout<<'\n';
    return 0;
}