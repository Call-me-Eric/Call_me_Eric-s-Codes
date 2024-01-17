#include<bits/stdc++.h>
using namespace std;
int n,k;
int a[1000001],ta,b[1000001],tb;
int sum,res;
bool now[1000001],ans[1000001];
void dfs(int i,int x){
    if(i>ta||sum+a[i]>k){
        if(sum>res){
            res=sum;
            for(int i=1;i<=n;i++)ans[i]=now[i];
        }
        return;
    }
    if(x==n/a[i]){
        dfs(i+1,0);
        return;
    }
    dfs(i,x+1);
    bool f=1;
    for(int j=0;j<a[i];j++){
        if(now[j*(n/a[i])+x]){
            f=0;
            break;
        }
    }
    if(f){
        for(int j=0;j<a[i];j++)
            now[j*(n/a[i])+x]=1;
        sum+=a[i];
        dfs(i,x+1);
        sum-=a[i];
        for(int j=0;j<a[i];j++)
            now[j*(n/a[i])+x]=0;
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    freopen("ur.in","r",stdin);
    freopen("ur.out","w",stdout);
    cin>>n>>k;
    if(k==n){
        for(int i=1;i<=n;i++)cout<<'1';
        return 0;
    }
    if(k<=1){
        for(int i=1;i<=n;i++)cout<<'0';
        return 0;
    }
    for(int i=2;i*i<=n;i++){
        if(n%i==0){
            b[++tb]=i;
            if(i!=n/i)b[++tb]=n/i;
        }
    }
    sort(b+1,b+tb+1);
    for(int i=1;i<=tb;i++){
        bool f=1;
        for(int j=1;j<=ta;j++){
            if(b[i]%a[j]==0){
                f=0;
                break;
            }
        }
        if(f)a[++ta]=b[i];
    }
    if(ta==1){
        int x=k/a[1];
        for(int i=0;i<n;i++)
            if(i%(n/a[1])<x)cout<<'1';
            else cout<<'0';
        return 0;
    }
    if(ta==2&&n>36){
        int p=k/a[1]*a[1],q=k/a[2]*a[2];
        if(p<q)swap(a[1],a[2]);
        int x=k/a[1];
        for(int i=0;i<n;i++)
            if(i%(n/a[1])<x)cout<<'1';
            else cout<<'0';
        return 0;
    }
    dfs(1,0);
    for(int i=1;i<=n;i++)cout<<ans[i];
    return 0;
}
