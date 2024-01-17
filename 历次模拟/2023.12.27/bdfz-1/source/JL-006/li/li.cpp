#include<bits/stdc++.h>
#define N 210000
using namespace std;
vector<int>v[N];
int n,m,vis[N],sum,siz,flag,num;
void dfs(int x){
    vis[x]=1;
    sum+=v[x].size(),siz++;
    flag&=v[x].size()==2;
    num+=v[x].size()>=3;
    for(auto to:v[x]){
        if(!vis[to])dfs(to);
    }
}
int main(){
    freopen("li.in","r",stdin);
    freopen("li.out","w",stdout);
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int a,b;
        cin>>a>>b;
        v[a].push_back(b),v[b].push_back(a);
    }
    int tmp=0;
    long long ans=0;
    for(int i=1;i<=n;i++){
        if(!vis[i]){
            sum=siz=num=0;
            flag=1;
            dfs(i);
            sum/=2;
            if(sum==siz-1){
                if(num==1&&siz==4){
                    tmp+=3;
                }
                else if(num){
                    cout<<-1<<'\n';
                    exit(0);
                }
                else{
                    ans+=1ll*siz*(siz+1)/2;
                }
            }
            else if(flag){
                tmp+=siz;
            }
            else{
                cout<<-1<<'\n';
                exit(0);
            }
        }
    }
    if(tmp)cout<<1<<" "<<tmp<<'\n';
    else cout<<0<<" "<<ans<<'\n';
    return 0;
}