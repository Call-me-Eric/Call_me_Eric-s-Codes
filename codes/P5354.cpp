#include<bits/stdc++.h>
#define ull unsigned long long
using namespace std;
inline int read(){
    int x = 0, f  =1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f=  -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0'; ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10;
const ull limit = 0ULL - 1ULL;
int n, m, k;
int op[maxn];ull a[maxn];

int head[maxn], tot;
struct edge{
    int to, nexte;
    edge(int to = 0,int ne = 0):to(to),nexte(ne){}
}e[maxn * 2];
void add(int u,int v){e[++tot] = edge(v,head[u]);head[u] = tot;}

int fa[maxn][21], dep[maxn], siz[maxn], son[maxn];
void dfs1(int u,int f){
    siz[u] = 1;
    for(int i = 1;i <= 20;i++){fa[u][i] = fa[fa[u][i - 1]][i - 1];}
    for(int i = head[u];i;i = e[i].nexte){
        int v = e[i].to; if(v == f)continue;
        fa[v][0] = u; dep[v] = dep[u] + 1;
        dfs1(v,u);siz[u] += siz[v];
        son[u] = (siz[son[u]] > siz[v]) ? son[u] : v;
    }
}
int lca(int u,int v){
    if(dep[u] < dep[v])swap(u,v);
    for(int i = 20;i + 1;i--){
        if(dep[fa[u][i]] >= dep[v]){
            u = fa[u][i];
        }
    }
    if(u == v)return u;
    for(int i = 20;i + 1;i--){
        if(fa[u][i] != fa[v][i]){
            u = fa[u][i]; v = fa[v][i];
        }
    }
    return fa[u][0];
}

int inv[maxn];//i -> 线段树编号, inv[i] -> 原树上编号
int id[maxn];//i ->原树上编号, id[i] -> 线段树编号
int top[maxn], idx;
void dfs2(int u,int t){
    id[u] = ++idx;top[u] = t;inv[id[u]] = u;
    if(!son[u])return;
    dfs2(son[u],t);
    for(int i = head[u];i;i = e[i].nexte){
        int v = e[i].to;
        if(v == fa[u][0] || v == son[u])continue;
        dfs2(v,v);
    }
    return;
}


struct node{
    ull pos0,pos1,inv0,inv1;//p0 = 正序0 p1 = 正序1 i0 = 反序0 i1 = 反序1
    node(ull p0 = 0,ull p1 = 0,ull i0 = 0,ull i1 = 0
        ):pos0(p0), pos1(p1),  inv0(i0),  inv1(i1){}
}d[maxn << 2];
node mergenode(node l,node r){
    return node((l.pos0 & r.pos1) | ((~l.pos0) & r.pos0),(l.pos1 & r.pos1) | ((~r.pos1) & l.pos0),
                (r.inv0 & l.inv1) | ((~r.inv0) & l.inv0),(r.inv1 & l.inv1) | ((~l.inv1) & r.inv0));
}
class Segment_Tree{
    private:
    ull calc(ull x,int opt){
        switch(op[opt]){
            case 1:return (x & a[opt]);break;
            case 2:return (x | a[opt]);break;
            case 3:return (x ^ a[opt]);break;
            default:break;
        }
    }
    void build(int l,int r,int p){
        if(l == r){d[p] = node(calc(0,inv[l]),calc(limit,inv[l]),calc(0,inv[l]),calc(limit,inv[l]));return;}
        int mid = l + r >> 1; build(l,mid,p << 1);build(mid + 1,r,p << 1 | 1);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
    node query(int l,int r,int s,int t,int p){
        if(s <= l && r <= t){return d[p];}
        int mid = l + r >> 1;
        if(t <= mid)return query(l,mid,s,t,p << 1);
        else if(mid < s)return query(mid + 1,r,s,t,p << 1 | 1);
        else return mergenode(query(l,mid,s,t,p << 1),query(mid + 1,r,s,t,p << 1 | 1));
    }
    void update(int l,int r,int goal,int p,int opt,ull val){
        if(l == r && l == id[goal]){
            op[goal] = opt;a[goal] = val;
            d[p] = node(calc(0,goal),calc(limit,goal),calc(0,goal),calc(limit,goal));
            return;
        }
        int mid = l + r >> 1;
        if(id[goal] <= mid)update(l,mid,goal,p << 1,opt,val);
        else update(mid + 1,r,goal,p << 1 | 1,opt,val);
        d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
    }
    public:
    void build(int n){build(1,n,1);}
    node query(int l,int r){return query(1,n,l,r,1);}
    void update(int goal,int opt,ull val){update(1,n,goal,1,opt,val);}
}tree;

node ans1[maxn], ans2[maxn];
node query(int x,int y){
    int cnt1 = 0,cnt2 = 0;
    while(top[x] != top[y]){
        if(dep[top[x]] >= dep[top[y]]){
            ans1[++cnt1] = tree.query(id[top[x]],id[x]);
            x = fa[top[x]][0];
        }
        else{
            ans2[++cnt2] = tree.query(id[top[y]],id[y]);
            y = fa[top[y]][0];
        }
    }
    if(dep[x] > dep[y])ans1[++cnt1] = tree.query(id[y],id[x]);
    else ans2[++cnt2] = tree.query(id[x],id[y]);
    node ans = node();
    for(int i = 1;i <= cnt1;i++){swap(ans1[i].inv0,ans1[i].pos0);swap(ans1[i].inv1,ans1[i].pos1);}
    if(cnt1){
        ans = ans1[1];
        for(int i = 2;i <= cnt1;i++){ans = mergenode(ans,ans1[i]);}
        if(cnt2){ans = mergenode(ans,ans2[cnt2]);}
    }
    else ans = ans2[cnt2];
    for(int i = cnt2 - 1;i >= 1;i--){ans = mergenode(ans,ans2[i]);}
    return ans;
}

signed main(){
    n = read(); m = read(); k = read(); int u, v, opt;ull w;
    for(int i = 1;i <= n;i++){op[i] = read(); scanf("%llu",&a[i]);}
    for(int i = 1;i < n;i++){
        u = read(); v = read();
        add(u,v); add(v,u);
    }
    fa[1][0] = 1;dep[1] = 1;
    dfs1(1,0);dfs2(1,1);tree.build(n);
    for(int i = 1;i <= m;i++){
        opt = read(); u = read(); v = read();scanf("%llu",&w);
        if(opt == 2){tree.update(u,v,w);}
        else{
            node ans = query(u,v); bool tmp0 = 0,tmp1 = 0;ull res = 0;
            for(int i = 63;i >= 0;i--){
                tmp0 = (ans.pos0 >> i) & 1ULL;
                tmp1 = (ans.pos1 >> i) & 1ULL;
                if(tmp0 >= tmp1 || (1ULL << i) > w)res |= (tmp0 ? (1ULL << i) : 0);
                else res |= (tmp1 ? (1ULL << i) : 0), w -= (1ULL << i);
            }
            printf("%llu\n",res);
        }
    }
    return 0;
}
