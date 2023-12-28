#include<bits/stdc++.h>
using namespace std;
#define ll long long
int n,m;
vector<int> edge[200005];
int vis[200005];
int cnt,tot,mx;
void dfs(int x){
    vis[x]=1;cnt++,tot+=edge[x].size(),mx=max(mx,(int)edge[x].size());
    for(int y:edge[x])if(!vis[y])dfs(y);
}
int main(){
    freopen("li.in","r",stdin);
    freopen("li.out","w",stdout);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        int x,y;scanf("%d%d",&x,&y);
        edge[x].push_back(y);
        edge[y].push_back(x);
    }
    ll ans=0,now=0;
    for(int i=1;i<=n;i++)if(!vis[i]){
        cnt=tot=mx=0;
        dfs(i);tot/=2;
        if(mx<=2){
            if(tot==cnt){
                if(now==0)now=1,ans=0;
                ans+=cnt;
            }else if(now==0)ans+=1ll*cnt*(cnt+1)/2;
        }else{
            if(cnt==4&&tot==3){
                if(now==0)now=1,ans=0;
                ans+=3;
            }else return puts("-1"),0;
        }
    }
    printf("%lld %lld\n",now,ans);
    return 0;
}