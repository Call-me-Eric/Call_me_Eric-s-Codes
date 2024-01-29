#include<bits/stdc++.h>
using namespace std;
//dengyaotriangle!

const int maxn=200005;

int n,m;
vector<int> adj[maxn];
int d[maxn];
bool vis[maxn];

int idg,mdg,sz,esz;
void dfs(int u){
    vis[u]=1;
    sz++;
    esz+=d[u];
    idg=min(idg,d[u]);
    mdg=max(mdg,d[u]);
    for(int v:adj[u]){
        if(!vis[v])dfs(v);
    }
}
int main(){
    #ifndef dengyaotriangle
    freopen("li.in","r",stdin);
    freopen("li.out","w",stdout);
    #endif
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v;cin>>u>>v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
        d[u]++;d[v]++;
    }
    bool typ=0;
    long long ans0=0,ans1=0;
    for(int i=1;i<=n;i++)if(!vis[i]){
        idg=INT_MAX,mdg=-1;
        sz=esz=0;
        dfs(i);
        esz/=2;
        if(mdg>=4){
            #ifndef N1
            cout<<"-1";
            #endif
            return 0;
        }else if(mdg==3&&esz>3){
            #ifndef N1
            cout<<"-1";
            #endif
            return 0;
        }else if(mdg==3){
            typ=1;ans1+=3;
        }else if(mdg==2&&idg==2){
            typ=1;ans1+=sz;
        }else{
            ans0+=(sz+1ll)*sz/2;
        }
    }
    if(typ){
        #ifndef NA
        cout<<"1 "<<ans1;
        #endif
    }else{
        #ifndef NB
        cout<<"0 "<<ans0;
        #endif
    } 
    return 0;
}