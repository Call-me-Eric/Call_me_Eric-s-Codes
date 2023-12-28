#include <bits/stdc++.h>
#define int long long
using namespace std;
int r,g,b,m,n,cnt,lst[255],cntn,lstn[255],f[255][255][255];
int dep[255],fat[255],sz[255];
int h[255][255];
bool vis[555],ans[250005];
struct edge{
    int f,t,col,id,lst;
    edge(int f=0,int t=0,int col=0,int id=0,int lst=0):
        f(f),t(t),col(col),id(id),lst(lst){}
}e[250005],ne[555];
void add(int u,int v,int w,int h){
    e[++cnt]=edge(u,v,w,h,lst[u]);lst[u]=cnt;
    e[++cnt]=edge(v,u,w,h,lst[v]);lst[v]=cnt;
}
void addn(int u,int v,int w){
    ne[++cntn]=edge(u,v,w,0,lstn[u]);lstn[u]=cntn;
    ne[++cntn]=edge(v,u,w,0,lstn[v]);lstn[v]=cntn;
}
int getcol(char c){
    if(c=='r')return 0;
    if(c=='g')return 1;
    return 2;
}
void dfs(int u){
    vis[u]=1;
    for(int i=lst[u];i;i=e[i].lst){
        int v=e[i].t;
        if(vis[v])continue;
        dfs(v),addn(u,v,e[i].col);
    }
}
vector<int> com[255][255][255],moc[255][255];
struct node{
    int first,second,zym;
    bool operator<(node b)const{
        if(first!=b.first)return first<b.first;
        return second<b.second;
    }
    bool operator==(node b)const{
        return first==b.first&&second==b.second;
    }
};
void add(vector<int> &a,vector<int> &b){
    for(auto it:b)a.push_back(it);
}
void dfs2(int u,int fa){
    f[u][0][0]=1;dep[u]=dep[fa]+1;fat[u]=fa;
    for(int i=lstn[u];i;i=ne[i].lst){
        int v=ne[i].t;
        if(v==fa)continue;
        dfs2(v,u);
    }
    vector<node> son;
    for(int i=lst[u];i;i=e[i].lst){
        int v=e[i].t;int tv=v;
        if(dep[v]<dep[u])continue;
        while(dep[v]>dep[u]+1)v=fat[v];
        son.push_back({v,e[i].col,e[i].id});
    }
    sort(son.begin(),son.end());
    son.resize(unique(son.begin(),son.end())-son.begin());
    for(int i=0;i<son.size();i++){
        if(i==0||son[i].first!=son[i-1].first){
            if(i)sz[u]+=sz[son[i-1].first]+1;
            for(int j=0;j<=min(r,sz[u]);j++){
                for(int k=0;k<=min(g,sz[u]);k++){
                    h[j][k]=f[u][j][k],f[u][j][k]=0;
                    moc[j][k]=com[u][j][k],com[u][j][k].clear();
                }
            }
        }
        int v=son[i].first;
        for(int j=0;j<=min(r,sz[u]);j++){
            for(int k=0;k<=min(g,sz[u]);k++){
                for(int c=0;j+c<=r&&c<=sz[v];c++){
                    for(int d=0;d+k<=g&&d<=sz[v];d++){
                        if(son[i].second==0){
                            f[u][j+c+1][k+d]|=h[j][k]&f[v][c][d];
                            if(h[j][k]&f[v][c][d]){
                                com[u][j+c+1][k+d].clear();
                                add(com[u][j+c+1][k+d],moc[j][k]);
                                add(com[u][j+c+1][k+d],com[v][c][d]);
                                com[u][j+c+1][k+d].push_back(son[i].zym);
                            }
                        }
                        if(son[i].second==1){
                            f[u][j+c][k+d+1]|=h[j][k]&f[v][c][d];
                            if(h[j][k]&f[v][c][d]){
                                com[u][j+c][k+d+1].clear();
                                add(com[u][j+c][k+d+1],moc[j][k]);
                                add(com[u][j+c][k+d+1],com[v][c][d]);
                                com[u][j+c][k+d+1].push_back(son[i].zym);
                            }
                        }
                        if(son[i].second==2){
                            f[u][j+c][k+d]|=h[j][k]&f[v][c][d];
                            if(h[j][k]&f[v][c][d]){
                                com[u][j+c][k+d].clear();
                                add(com[u][j+c][k+d],moc[j][k]);
                                add(com[u][j+c][k+d],com[v][c][d]);
                                com[u][j+c][k+d].push_back(son[i].zym);
                            }
                        }
                            
                    }
                }
            }
        }
    }
    if(son.size())sz[u]++;
}
int fa[255],af[255];
int find(int x,int *fa){
    if(x==fa[x])return x;
    return fa[x]=find(fa[x],fa);
}
void subB(){
    for(int i=1;i<=n;i++)fa[i]=af[i]=i;
    for(int i=1;i<=cnt;i+=2){
        int u=e[i].f,v=e[i].t;
        if(e[i].col==1)fa[find(u,fa)]=find(v,fa);
    }
    int tot=0;
    for(int i=1;i<=cnt;i+=2){
        int u=e[i].f,v=e[i].t;
        if(find(u,fa)==find(v,fa))continue;
        if(e[i].col==0){
            fa[find(u,fa)]=find(v,fa),tot++,af[find(u,af)]=find(v,af);
            ans[e[i].id]=1;
        }
    }
    if(tot>r){
        puts("NO");
        return;
    }
    for(int i=1;i<=cnt;i+=2){
        int u=e[i].f,v=e[i].t;
        if(find(u,af)==find(v,af)||e[i].col!=0)continue;
        if(tot==r)break;
        fa[find(u,af)]=find(v,af);tot++;ans[e[i].id]=1;
    }
    if(tot!=r){
        puts("NO");
        return;
    }
    tot=0;
    for(int i=1;i<=cnt;i+=2){
        int u=e[i].f,v=e[i].t;
        if(find(u,af)==find(v,af)||e[i].col!=1)continue;
        fa[find(u,af)]=find(v,af),ans[e[i].id]=1;tot++;
    }
    if(tot!=g){
        puts("NO");
        return;
    }
    puts("YES");
    for(int i=1;i<=m;i++)printf("%d",ans[i]);
}
bool chk(){
    for(int i=1;i<=n;i++)fa[i]=i;
    int c[5];memset(c,0,sizeof(c));
    for(int i=1;i<=m;i++){
        if(ans[i]){
            c[e[i*2].col]++;
            fa[find(e[i*2].f,fa)]=find(e[i*2].t,fa);
        }
    }
    if(c[0]!=r||c[1]!=g||c[2]!=b)return 0;
    for(int i=1;i<=n;i++)if(find(i,fa)!=find(1,fa))return 0;
    return 1;
}
bool qfs(int st){
    if(st==m+1){
        return chk();
    }
    ans[st]=0;
    if(qfs(st+1))return 1;
    ans[st]=1;
    return qfs(st+1);
}
void sub1(){
    if(!qfs(1))puts("NO");
    else {
        puts("YES");
        for(int i=1;i<=m;i++)printf("%d",ans[i]);
    }
}
int E[255][255],di[255][255];
void subA(){
    int pre=clock();
    int c[5];memset(c,0,sizeof(c));
    memset(E,-1,sizeof(E));
    for(int i=1;i<=cnt;i++)E[e[i].f][e[i].t]=e[i].col,di[e[i].f][e[i].t]=e[i].id;
    vector<edge> q[3];
    for(int i=1;i<=cnt;i+=2)q[e[i].col].push_back(e[i]);
    mt19937 rnd(time(0));
    for(int i=1;i<=n;i++)fa[i]=i;
    for(int i=2;i<=n;i++){
        int top=100;
        while(top--&&find(i,fa)!=find(1,fa)){
            int d=rnd()%n+1;
            if(E[i][d]<0||find(i,fa)==find(d,fa))continue;
            if(E[i][d]==0&&r==c[0])continue;
            if(E[i][d]==1&&g==c[1])continue;
            if(E[i][d]==2&&b==c[2])continue;
            fa[find(i,fa)]=find(d,fa);ans[di[i][d]]=1;
            c[E[i][d]]++;
        }
    }
    if(c[0]!=r||c[1]!=g||c[2]!=b)return;
    for(int i=1;i<=n;i++){
        if(find(i,fa)!=find(1,fa))return;
    }
    puts("YES");
    for(int i=1;i<=m;i++)printf("%d",ans[i]);
}
signed main(){
    freopen("rgb.in","r",stdin);
    freopen("rgb.out","w",stdout);
    cin>>r>>g>>b>>m;n=r+g+b+1;
    for(int i=1;i<=m;i++){
        int u,v;char c;
        scanf("%lld %lld %c",&u,&v,&c);
        add(u,v,getcol(c),i);
    }
    if(b==0)subB(),exit(0);
    if(n<=5)sub1(),exit(0);
    subA();
    dfs(1);
    dfs2(1,0);
    if(f[1][r][g]){
        puts("YES");
        memset(ans,0,sizeof(ans));
        for(int i:com[1][r][g])ans[i]=1;
        for(int i=1;i<=m;i++)printf("%d",ans[i]);
    }
    else puts("NO");
    return 0;
}