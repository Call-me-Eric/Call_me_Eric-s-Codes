#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 3) + (x << 1) + ch - '0'; ch = getchar();}
    return x * f;
}
int n, m;
const int maxn = 1e5 + 10,maxm = 3e5 + 10;
const int INF = 1e10;
int head[maxn], tot;
bool used[maxm];
struct edge{
    int frompoint,topoint, nextedge, weight;
    edge(int fr = 0,int to = 0, int ne = 0,int w = 0){frompoint = fr;topoint = to;nextedge = ne;weight = w;}
}e1[maxm],e[maxm * 2];
void add(int u,int v,int w){e[++tot] = edge(u,v,head[u],w);head[u] = tot;}
//kruskal init
bool operator < (edge a,edge b){return a.weight < b.weight;}
int f[maxn];
int getf(int x){if(f[x] != x)return f[x] = getf(f[x]);return x;}
//LCA
int fa[maxn][21],mx[maxn][21],mx2[maxn][21];
int dep[maxn];
void dfs(int u){
    dep[u] = dep[fa[u][0]] + 1;
    for(int i = 1;i <= 20;i++){
        fa[u][i] = fa[fa[u][i - 1]][i - 1];
        if(mx[u][i - 1] == mx[fa[u][i - 1]][i - 1]){
            mx[u][i] = mx[u][i - 1];
            mx2[u][i] = max(mx2[fa[u][i - 1]][i - 1],mx2[u][i - 1]);
        }
        if(mx[u][i - 1] > mx[fa[u][i - 1]][i - 1]){
            mx[u][i] = mx[u][i - 1];
            mx2[u][i] = max(mx[fa[u][i - 1]][i - 1],mx2[u][i - 1]);
        }
        if(mx[u][i - 1] < mx[fa[u][i - 1]][i - 1]){
            mx[u][i] = mx[fa[u][i - 1]][i - 1];
            mx2[u][i] = max(mx2[fa[u][i - 1]][i - 1],mx[u][i - 1]);
        }
    }
    for(int i = head[u];i;i = e[i].nextedge){
        int v = e[i].topoint, w = e[i].weight;
        if(v == fa[u][0])continue;
        fa[v][0] = u; mx[v][0] = w;
        dfs(v);
    }
    return;
}
int LCA(int u,int v){
    if(dep[u] < dep[v])swap(u,v);
    for(int i = 20;i + 1;i--)
        if(dep[u] - dep[v] >= (1 << i))u = fa[u][i];
    if(u == v)return u;
    for(int i = 20;i + 1;i--)
        if(fa[u][i] != fa[v][i]){
            u = fa[u][i];
            v = fa[v][i];
        }
    return fa[u][0];
}
//untitled
int ans = 0, cnt = 0, res = INF;
int cal(int index){
    int u = e1[index].frompoint, v = e1[index].topoint, w = e1[index].weight;
    int l = LCA(u, v), maxx = 0, maxx2 = 0;
    for(int i = 20;i + 1;i--){
        if(dep[fa[u][i]] >= dep[l]){
            if(mx[u][i] == maxx){maxx2 = max(maxx2,mx2[u][i]);}
            if(mx[u][i] > maxx){maxx2 = max(maxx2,mx[u][i]);}
            if(mx[u][i] < maxx){maxx2 = max(maxx,mx2[u][i]);maxx = mx[u][i];}
            u = fa[u][i];
        }
        if(dep[fa[v][i]] >= dep[l]){
            if(mx[v][i] == maxx){maxx2 = max(maxx2,mx2[v][i]);}
            if(mx[v][i] > maxx){maxx2 = max(maxx2,mx[v][i]);}
            if(mx[v][i] < maxx){maxx2 = max(maxx,mx2[v][i]);maxx = mx[v][i];}
            v = fa[u][i];
        }
    }
    if(w != maxx)return ans - maxx + w;
    if(maxx2)return ans - maxx2 + w;
    return INF;
}
//untitled
signed main(){
    int u, v, w;
    n = read(); m = read();
    for(int i = 1;i <= m;i++){
        u = read(); v = read(); w = read();
        e1[i] = edge(u,v,0,w);
    }
    //kruskal starts
    sort(e1 + 1,e1 + 1 + m);
    for(int i = 1;i <= n;i++){f[i] = i;}
    for(int i = 1;i <= m;i++){
        int fu = getf(e1[i].frompoint), fv = getf(e1[i].topoint);
        if(fu != fv){
            ans += e1[i].weight;
            cnt++; f[fu] = fv;
            used[i] = 1;
            add(u,v,w); add(v,u,w);
            if(cnt == n - 1)break;
        }
    }
    //kruskal ends
    //LCA init starts
    dfs(1);
    //LCA init ends
    for(int i = 1;i <= m;i++)
        if(!used[i]){res = min(res,cal(i));}
    printf("%d\n",res);
    return 0;
}