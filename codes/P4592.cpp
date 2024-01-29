#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0'; ch = getchar();}
    return x * f;
}
const int maxn = 2e5 + 10;
int n, m;
int val[maxn];

int head[maxn], tot;
struct edge{
    int topoint, nextedge;
    edge(int t = 0,int n = 0):topoint(t),nextedge(n){}
}e[maxn * 2];
void add(int u,int v){e[++tot] = edge(v,head[u]);head[u] = tot;}

int fa[maxn][31], dep[maxn];
int getdep(int u,int f){
    dep[u] = dep[f] + 1;
    fa[u][0] = f;
    for(int i = 1;i <= 30;i++)fa[u][i] = fa[fa[u][i - 1]][i - 1];
    for(int i = head[u];i;i = e[i].nextedge){
        int v = e[i].topoint;
        if(v == f)continue;
        getdep(v,u);
    }
}
int LCA(int u,int v){
    if(dep[u] < dep[v])swap(u,v);
    for(int i = 30;i + 1;i--)
        if(dep[fa[u][i]] >= dep[v])u = fa[u][i];
    if(u == v)return u;
    for(int i = 30;i + 1;i--){
        if(fa[u][i] != fa[v][i]){
            u = fa[u][i];
            v = fa[v][i];
        }
    }
    return fa[u][0];
}

int trie1[maxn * 40 * 4][2], cnt1[maxn * 40 * 4], tot1;
int head1[maxn * 4];//opt1
int st[maxn], ed[maxn];
int dfn[maxn * 4], ind;
void insert1(int ver,int x){
    head1[ver] = ++tot1;
    int u = head1[ver],v = head1[ver - 1];
    for(int i = 31;i + 1;i--){
        bool opt = (x >> i) & 1;
        trie1[u][opt] = ++tot1;
        trie1[u][!opt] = trie1[v][!opt];
        cnt1[trie1[u][opt]] = cnt1[trie1[v][opt]] + 1;
        cnt1[trie1[u][!opt]] = cnt1[trie1[v][!opt]];
        u = trie1[u][opt]; v = trie1[v][opt];
    }
}
int query1(int x,int l){
    int u = head1[st[l] - 1], v = head1[ed[l]], ans = 0;
    for(int i = 31;i + 1;i--){
        bool opt = (x >> i) & 1;
        if(cnt1[trie1[v][!opt]] - cnt1[trie1[u][!opt]] > 0){opt = !opt;ans += (1 << i);}
        u = trie1[u][opt]; v = trie1[v][opt];
    }
    return ans;
}
void dfs1(int u,int f){
    dfn[++ind] = u;
    ed[u] = st[u] = ind;
    for(int i = head[u];i;i = e[i].nextedge){
        int v = e[i].topoint;
        if(v == f)continue;
        dfs1(v,u);
        dfn[++ind] = u;
        ed[u] = ind;
    }
}
void init1(){
    for(int i = 1;i <= ind;i++)
        insert1(i,val[dfn[i]]);
}

int trie2[maxn * 40 * 4][2],cnt2[maxn * 40 * 4] ,tot2;
int head2[maxn];//opt2
void insert2(int ver1,int ver,int x){
    head2[ver] = ++tot2;
    int u = head2[ver],v = head2[ver1];
    for(int i = 31;i + 1;i--){
        bool opt = (x >> i) & 1;
        trie2[u][opt] = ++tot2;
        trie2[u][!opt] = trie2[v][!opt];
        cnt2[trie2[u][opt]] = cnt2[trie2[v][opt]] + 1;
        cnt2[trie2[u][!opt]] = cnt2[trie2[v][!opt]];
        u = trie2[u][opt]; v = trie2[v][opt];
    }
}
int query(int l,int r,int x){
    int u = head2[fa[l][0]], v = head2[r], ans = 0;
    for(int i = 31;i + 1;i--){
        bool opt = (x >> i) & 1;
        if(cnt2[trie2[v][!opt]] - cnt2[trie2[u][!opt]] > 0){opt = !opt;ans += (1 << i);}
        u = trie2[u][opt]; v = trie2[v][opt];
    }
    return ans;

}
int query2(int x,int u,int v){
    int lca = LCA(u,v);
    return max(query(lca,u,x),query(lca,v,x));
}
void dfs2(int u,int f){
    insert2(f,u,val[u]);
    for(int i = head[u];i;i = e[i].nextedge){
        int v = e[i].topoint;
        if(v == f)continue;
        dfs2(v,u);
    }
}

signed main(){
    n = read(); m = read();int opt, u, v, z;
    for(int i = 1;i <= n;i++)val[i] = read();
    for(int i = 1;i < n;i++){
        u = read(); v = read();
        add(u, v); add(v, u);
    }
    getdep(1,0); dfs1(1,0); dfs2(1,0);
    init1();
    for(int i = 1;i <= m;i++){
        opt = read(); u = read(); v = read();
        if(opt == 1){printf("%d\n",max(v ^ val[u],query1(v,u)));}
        else{z = read();printf("%d\n",query2(z,u,v));}
    }
    return 0;
}