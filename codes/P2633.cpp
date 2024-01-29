#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0';ch = getchar();}
    return x * f;
}
const int maxn = 2e5 + 10;
int n, m;

int head[maxn], tot;
struct edge{int to, nexte;edge(int to = 0,int ne = 0):to(to),nexte(ne){}}e[maxn << 1];
void add(int u,int v){e[++tot] = edge(v,head[u]);head[u] = tot;}

int val[maxn],a[maxn],b[maxn];

struct node{
    int sum, ls, rs;
    node(int sum = 0,int ls = 0,int rs = 0):sum(sum),ls(ls),rs(rs){}
}d[maxn * 10];
int ver[maxn],total, res;
int query(int p1,int p2,int p3,int p4,int l,int r,int k){//p1:u,p2:v,p3:lca,p4:fa[lca]
    if(l == r)return l;
    int mid = l + r >> 1;
    int tmp = d[d[p1].ls].sum + d[d[p2].ls].sum - d[d[p3].ls].sum - d[d[p4].ls].sum;
    if(tmp >= k)return query(d[p1].ls,d[p2].ls,d[p3].ls,d[p4].ls,l,mid,k);
    else return query(d[p1].rs,d[p2].rs,d[p3].rs,d[p4].rs,mid + 1,r,k - tmp);
}
void build(int p,int r,int l){
    // printf("%d %d %d\n",l,r,p);
    if(l == r){d[p].sum = 0;return;}
    int mid = l + r >> 1;
    d[p].ls = ++total; build(d[p].ls,l,mid);
    d[p].rs = ++total; build(d[p].rs,mid + 1,r);
}
void update(int p,int lst,int l,int r,int k){//p:u,lst:fa[u]
    if(l == r){d[p].sum++;return;}
    int mid = l + r >> 1;
    if(mid >= k){
        if(!d[p].ls)d[p].ls = ++total;
        d[p].rs = d[lst].rs;
        update(d[p].ls,d[lst].ls,l,mid,k);
    }
    else{
        if(!d[p].rs)d[p].rs = ++total;
        d[p].ls = d[lst].ls;
        update(d[p].rs,d[lst].rs,mid + 1,r,k);
    }
    d[p].sum = d[d[p].ls].sum + d[d[p].rs].sum;
}

int fa[maxn][21], dep[maxn];
void dfs(int u,int f){
    for(int i = 1;i <= 20;i++){fa[u][i] = fa[fa[u][i - 1]][i - 1];}
    for(int i = head[u];i;i = e[i].nexte){
        int v = e[i].to; if(v == f)continue;
        dep[v] = dep[u] + 1; fa[v][0] = u;
        ver[v] = ++total;update(ver[v],ver[u],1,res,a[v]); dfs(v,u);
    }
}
int LCA(int u,int v){
    if(dep[u] < dep[v])swap(u,v);
    for(int i = 20;i >= 0;i--){
        if(dep[fa[u][i]] >= dep[v])
            u = fa[u][i];
    }
    if(u == v)return u;
    for(int i = 20;i >= 0;i--){
        if(fa[u][i] != fa[v][i]){
            u = fa[u][i];
            v = fa[v][i];
        }
    }
    return fa[u][0];
}

signed main(){
    #ifndef ONLINE_JUDGE
    freopen("P2633_1.in","r",stdin);
    freopen("P2633.out","w",stdout);
    #endif
    int lastans = 0, u, v, k;
    n = read(); m = read();
    for(int i = 1;i <= n;i++)b[i] = val[i] = read();
    sort(b + 1,b + 1 + n);
    res = unique(b + 1,b + 1 + n) - (b) - 1;
    for(int i = 1;i <= n;i++)a[i] = lower_bound(b + 1,b + 1 + res,val[i]) - (b);
    // printf("res=%d\n",res);
    // for(int i = 1;i <= n;i++){printf("%d\n",b[i]);}
    // for(int i = 1;i <= n;i++){printf("a[%d]=%d ->%d\n",i,a[i],b[a[i]]);}
    for(int i = 1;i < n;i++){u = read(); v = read(); add(u,v); add(v,u);}
    ver[0] = ++total;build(ver[0],1,res);
    ver[1] = ++total;update(ver[1],ver[0],1,res,a[1]);
    dep[1] = 1; dfs(1,0);
    for(int i = 1;i <= m;i++){
        u = read(); v = read();k = read();
        // printf("%lld %lld %lld",u,v,k);
        u = u ^ lastans;
        // printf("u=%lld\n",u);
        int lca = LCA(u,v);
        // printf(" %lld %lld\n",u,lca);
        lastans = b[query(ver[u],ver[v],ver[lca],ver[fa[lca][0]],1,res,k)];
        printf("%lld\n",lastans);
    }
    // printf("u=%lld\n",lastans ^ read());
    return 0;
}