#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,m,cnt,lst[200005],s,deg[200005],cir,ln;
bool vis[200005];
struct edge{
    int f,t,lst;
    edge(int f=0,int t=0,int lst=0):
        f(f),t(t),lst(lst){}
}e[400005];
void add(int u,int v){
    deg[u]++,deg[v]++;
    e[++cnt]=edge(u,v,lst[u]);lst[u]=cnt;
    e[++cnt]=edge(v,u,lst[v]);lst[v]=cnt;
}
vector<int> now;
void dfs(int u,int fa){
    vis[u]=1;now.push_back(u);
    for(int i=lst[u];i;i=e[i].lst){
        int v=e[i].t;
        if(vis[v])continue;
        dfs(v,u);
    }
}
bool chk_cir(){
    for(int v:now){
        if(deg[v]!=2)return 0;
    }
    return 1;
}
bool chk_4(){
    if(now.size()!=4)return 0;
    int id=-1;
    for(int v:now){
        if(deg[v]!=3&&deg[v]!=1)return 0;
        if(deg[v]==3&&id==-1)id=v;
        else if(deg[v]==3)return 0;
    }
    return id!=-1;
}
bool chk_chain(){
    for(int v:now){
        if(deg[v]>2)return 0;
    }
    return 1;
}
signed main(){
    freopen("li.in","r",stdin);
    freopen("li.out","w",stdout);
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v;scanf("%lld%lld",&u,&v);
        add(u,v);
    }
    for(int i=1;i<=n;i++){
        if(!vis[i]){
            now.clear();
            dfs(i,0);
            if(chk_cir()){
                cir+=now.size();
                if(!s)s=1;
            }
            else if(chk_4()){
                cir+=3;
                if(!s)s=1;
            }
            else if(chk_chain()){
                ln+=now.size()*(now.size()+1)/2;
            }
            else s=-1;
        }
    }
    if(s==-1)cout<<s,exit(0);
    cout<<s<<' ';
    if(!s)cout<<ln;
    else cout<<cir;
    return 0;
}