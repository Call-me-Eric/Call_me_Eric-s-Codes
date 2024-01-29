#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f= -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10;
int n, m;
vector<int> edg[maxn];

int dfn[maxn], low[maxn], idx,rev[maxn];
void dfs(int u,int f){
    dfn[u] = low[u] = ++idx;rev[idx] = u;
    for(int v : edg[u])
        if(v != f){dfs(v, u);low[u] = max(low[u],low[v]);}
}

class Segment_Tree{
private:
    struct node{
        int sum, len, l, r;
        node(int l = 0,int r = 0,int sum = 0,int len = 0):l(l),r(r),sum(sum),len(len){}
    }d[maxn << 4];
    void pushup(int p){
        if(d[p].sum)d[p].len = d[p].r - d[p].l + 1;
        else d[p].len = d[p << 1].len + d[p << 1 | 1].len;
    }
    void build(int l,int r,int p){
        d[p] = node(l,r); if(l == r){return;}
        int mid = l + r >> 1;
        build(l,mid,p << 1);build(mid + 1,r,p << 1 | 1);
    }
    void update(int l,int r,int s,int t,int p,int add){
        if(r < s || t < l)return;
        if(s <= l && r <= t){d[p].sum += add;pushup(p);return;}
        int mid = l + r >> 1;
        if(s <= mid)update(l,mid,s,t,p << 1,add);
        if(mid < t)update(mid + 1,r,s,t,p << 1 | 1,add);
        pushup(p);
    }
public:
    int query(){return d[1].len;}
    void update(int s,int t,int add){update(1,n + 1,s,t,1,add);}
    void build(int n){build(1,n,1);}
}tree;
struct scanline{
    int y, xl, xr, opt;
    scanline(int y = 0,int xl = 0,int xr = 0,int opt = 0):y(y),xl(xl),xr(xr),opt(opt){}
    friend bool operator < (scanline a,scanline b){return a.y < b.y;}
}lines[maxn << 4];
int tot1;
void addmatrix(int xl,int yl,int xr,int yr){
    if(yl > yr){swap(yl,yr);swap(xl,xr);}
    lines[++tot1] = scanline(yl,xl,xr,1);
    lines[++tot1] = scanline(yr + 1,xl,xr,-1);
}
int ans[maxn];
signed main(){
    n = read(); m = read();int u, v;
    for(int i = 1;i < n;i++){
        u = read(); v =read();
        edg[u].push_back(v);edg[v].push_back(u);
    }
    dfs(1, 0);
    for(int i = 1;i <= m;i++){
        u = read(); v = read();
        addmatrix(dfn[u],dfn[u],low[u],low[u]);
        addmatrix(dfn[v],dfn[v],low[v],low[v]);
        addmatrix(dfn[u],dfn[v],low[u],low[v]);
        addmatrix(dfn[v],dfn[u],low[v],low[u]);
    }
    sort(lines + 1,lines + 1 + tot1);
    tree.build(n + 1);
    // puts("11111");
    for(int i = 1, j = 0;i <= n;i++){
        while(lines[j + 1].y == i && j <= tot1){j++;tree.update(lines[j].xl,lines[j].xr,lines[j].opt);}
        ans[i] = tree.query();
        ans[i] = ans[i] ? (ans[i] - 1) : 0;
        // puts("222222");
    }
    for(int i = 1;i <= n;i++)printf("%d ",ans[dfn[i]]);puts("");
    // for(int i = 1;i <= n;i++)printf("i=%d dfn = %d, low = %d\n",i,dfn[i],low[i]);
    // for(int i = 1;i <= tot1;i++){printf("i = %d:y = %d, l = %d, r = %d, opt = %d\n",i,lines[i].y,lines[i].xl,lines[i].xr,lines[i].opt);}
    return 0;
}