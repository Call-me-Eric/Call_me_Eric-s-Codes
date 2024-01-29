#include<bits/stdc++.h>
using namespace std;
const int maxn=250+3;
int n,lim[3],m;
int r,g,b,cnt,num[3],ad[3],hed[maxn],dep[maxn],fr[maxn],fa[maxn],rep[maxn*maxn];
bool vis[maxn*maxn],can[maxn*maxn],use[maxn*maxn];
bool type;
vector<int>son[maxn];
struct node_ku{
    int id,to,co,ty;
};
vector<node_ku>cso[3][maxn];
struct node_edge{
    int nxt,to,val;
}G[maxn*maxn];
struct node{
    int id,dp,co,ty;
    bool operator < (const node &A)const{
        return (dp!=A.dp)?(dp>A.dp):(ty<A.ty);
    }
};
// set<node>s[maxn];
// set<node>::iterator it;
vector<node>s[maxn];
void add(int u,int v,int w){
    G[++cnt]=(node_edge){hed[u],v,w};
    hed[u]=cnt;
    return ;
}
void dfs(int x){
    // printf("dfs %d\n",x);
    vis[x]=1;
    for(int i=hed[x],v;i;i=G[i].nxt){
        v=G[i].to;
        if(vis[v])continue;
        dep[v]=dep[x]+1;
        fr[v]=i/2,use[i/2]=1,fa[v]=x;
        num[G[i].val]++;
        son[x].push_back(v);
        dfs(v);
    }
    return ;
}
bool check(int val){
    return (!type)?(val==r&&num[r]>lim[r]||val==g&&num[g]>lim[g]):(val==r&&num[r]>lim[r]);
}
void solve(int x){
    vector<node>ne;
    int mi;
    for(int i=0,v;i<son[x].size();i++){
        v=son[x][i];
        solve(v);
        // while(!s[v].empty()&&s[v].begin()->dp>dep[x])s[v].erase(s[v].begin());
        ne.clear(),mi=-1;
        for(int j=0;j<s[v].size();j++){
            if(use[s[v][j].id]||num[s[v][j].co]+ad[s[v][j].co]==lim[s[v][j].co])continue;
            if(s[v][j].dp<=dep[x]){
                ne.push_back(s[v][j]);
                if(mi==-1||s[v][j]<ne[mi])mi=((int)ne.size())-1;
            }
        }
        if(mi!=-1&&check(G[fr[v]*2].val)){
            num[G[fr[v]*2].val]--;
            rep[fr[v]]=ne[mi].id;
            // if(G[rep[fr[v]]*2].val==g)printf("pas rep %d\n",rep[fr[v]]);
            use[ne[mi].id]=1,use[fr[v]]=0;
            ad[ne[mi].co]++;
            swap(ne[0],ne[mi]);
            ne.erase(ne.begin());
        }
        for(int j=0;j<ne.size();j++)s[x].push_back(ne[j]);
    }
    for(int i=0;i<cso[b][x].size();i++){
        if(!use[cso[b][x][i].id]&&num[cso[b][x][i].co]+ad[cso[b][x][i].co]<lim[cso[b][x][i].co])s[x].push_back((node){cso[b][x][i].id,dep[cso[b][x][i].to],b,cso[b][x][i].ty});
    }
    if(type){
        for(int i=0;i<cso[g][x].size();i++){
            if(!use[cso[g][x][i].id]&&num[cso[g][x][i].co]+ad[cso[g][x][i].co]<lim[cso[g][x][i].co])s[x].push_back((node){cso[g][x][i].id,dep[cso[g][x][i].to],g,cso[g][x][i].ty});
        }
    }
    return ;
}
void repla(int x){
    vector<node>ne;
    int mi;
    s[x].clear();
    for(int i=0,v;i<son[x].size();i++){
        v=son[x][i];
        repla(v);
        // while(!s[v].empty()&&s[v].begin()->dp>dep[x])s[v].erase(s[v].begin());
        ne.clear(),mi=-1;
        for(int j=0;j<s[v].size();j++){
            // if(rep[fr[v]]==13&&s[v][j].dp<=dep[x])printf("no!!!!\n");
            if(use[s[v][j].id])continue;
            if(s[v][j].dp<=dep[x]){
                // if(rep[fr[v]]==13)printf("ka\n");
                ne.push_back(s[v][j]);
                if(mi==-1||s[v][j]<ne[mi])mi=((int)ne.size())-1;
            }
        }
        // if(rep[fr[v]]==13)printf("boom %d %d\n",mi,x);
        if(mi!=-1&&G[rep[fr[v]]*2].val==g&&ad[b]+num[b]<lim[b]){
            use[rep[fr[v]]]=0,use[ne[mi].id]=1;
            ad[g]--;
            ad[b]++;
            swap(ne[0],ne[mi]);
            ne.erase(ne.begin());
        }
        for(int i=0;i<ne.size();i++)s[x].push_back(ne[i]);
    }
    for(int i=0;i<cso[b][x].size();i++){
        if(!use[cso[b][x][i].id])s[x].push_back((node){cso[b][x][i].id,dep[cso[b][x][i].to],b,cso[b][x][i].ty});
    }
    return ;
}
int gtlca(int u,int v){
    if(dep[u]<dep[v])swap(u,v);
    while(dep[u]>dep[v])u=fa[u];
    if(u==v)return u;
    while(fa[u]!=fa[v])u=fa[u],v=fa[v];
    return fa[u];
}
int main(){
    freopen("rgb.in","r",stdin);
    freopen("rgb.out","w",stdout);
    scanf("%d%d%d%d",&lim[0],&lim[1],&lim[2],&m);
    n=lim[0]+lim[1]+lim[2]+1;
    cnt=1;
    int u,v,w;
    char c;
    for(int i=1;i<=m;i++){
        cin>>u>>v>>c;
        if(c=='r')w=0;
        if(c=='g')w=1;
        if(c=='b')w=2;
        add(u,v,w);
        add(v,u,w);
    }
    dfs(1);
    if(num[0]>lim[0]){
        r=0;
        if(num[2]>lim[2])g=2,b=1;
        else g=1,b=2;
    }
    else {
        b=0;
        if(num[1]>lim[1])r=1,g=2;
        else r=2,g=1;
    }
    if(num[g]>lim[g])type=0;
    else type=1;
    int lca;
    for(int i=1;i<=n;i++){
        for(int j=hed[i],v;j;j=G[j].nxt){
            if(use[j/2])continue;
            v=G[j].to;
            lca=gtlca(v,i);
            if(lca==v)cso[G[j].val][i].push_back((node_ku){j/2,v,G[j].val,0});
            else{
                cso[G[j].val][i].push_back((node_ku){j/2,lca,G[j].val,1});
                cso[G[j].val][v].push_back((node_ku){j/2,lca,G[j].val,1});
            }
        }
    }
    // printf("before\n");
    // for(int i=1;i<=m;i++)putchar((use[i])?'1':'0');
    // printf("\n");
    // printf("%d %d %d\n",r,g,b);
    // printf("after dfs (%d %d %d) (%d %d %d) (%d %d %d) %d\n",lim[r],ad[r],num[r],lim[g],ad[g],num[g],lim[b],ad[b],num[b],type);
    solve(1);
    // printf("after solve (%d %d %d) (%d %d %d) (%d %d %d)\n",lim[r],ad[r],num[r],lim[g],ad[g],num[g],lim[b],ad[b],num[b]);
    // for(int i=1;i<=m;i++)putchar((use[i])?'1':'0');
    // printf("\n");
    if(type){
        if(ad[g]+num[g]<lim[g]&&ad[b]+num[b]>lim[b]){
            swap(g,b);
            repla(1);
        }
        else if(ad[g]+num[g]>lim[g]&&ad[b]+num[b]<lim[b]){
            // printf("chao!\n");
            repla(1);
        }
        if(ad[g]+num[g]<lim[g]||ad[b]+num[b]<lim[b])printf("NO\n");
        else {
            printf("YES\n");
            // for(int i=1;i<=m;i++)putchar((use[i])?'1':'0');
        }
    }
    else {
        if(ad[b]+num[b]<lim[b])printf("NO\n");
        else {
            printf("YES\n");
            // for(int i=1;i<=m;i++)putchar((use[i])?'1':'0');
        }
    }
    return 0;
}