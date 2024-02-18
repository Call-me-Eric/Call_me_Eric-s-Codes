#include<bits/stdc++.h>
#define int long long
using namespace std;
bool stmemory;
namespace Call_me_Eric{
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e6 + 10;
int n, val[maxn];
vector<int> edg[maxn];
int head[maxn], cntnode = 0;
struct Segment_Tree{
    struct node{
        int l, r, cnt,lp,rp;
        node(int l = 0,int r = 0,int cnt = 0,int lp = 0,int rp = 0
        ):l(l),r(r),cnt(cnt),lp(lp),rp(rp){}
    }d[maxn * 30];
    #define L(p) d[p].lp
    #define R(p) d[p].rp
    node mergenode(node l,node r,node p = node()){return node(l.l,r.r,l.cnt + r.cnt,p.lp,p.rp);}
    void update(int l,int r,int &p,int his,int val){
        if(!p)p = ++cntnode;//printf("p = %lld,l = %lld, r = %lld, val = %lld\n",p,l,r,val);
        if(l == r){d[p] = node(l,r,1);;return;}
        int mid = l + r >> 1;
        if(val <= mid){
            R(p) = R(his);
            update(l,mid,L(p),L(his),val);
        }
        else{
            L(p) = L(his);
            update(mid + 1,r,R(p),R(his),val);
        }
        d[p] = mergenode(d[L(p)],d[R(p)],d[p]);
    }
    int query(int l,int r,int p1,int p2,int p3,int p4,int k){
        if(l == r)return l; int mid = l + r >> 1;
        int x = d[R(p1)].cnt + d[R(p2)].cnt - d[R(p3)].cnt - d[R(p4)].cnt;
        // printf("l = %lld,r = %lld,k = %lld,x = %lld\n",l,r,k,x);
        if(x >= k)return query(mid + 1,r,R(p1),R(p2),R(p3),R(p4),k);
        else return query(l,mid,L(p1),L(p2),L(p3),L(p4),k - x);
    }
}tree;
int fa[21][maxn], dep[maxn];
void dfs(int u,int f){
    tree.update(1,n,head[u],head[f],val[u]);
    fa[0][u] = f;for(int i = 1;i <= 20;i++)fa[i][u] = fa[i - 1][fa[i - 1][u]];
    for(int v : edg[u])if(v != f){dep[v] = dep[u] + 1;dfs(v, u);}
}
int LCA(int u,int v){
    if(dep[u] < dep[v])swap(u, v);
    for(int i = 20;i + 1;i--)
        if(dep[fa[i][u]] >= dep[v])
            u = fa[i][u];
    if(u == v)return u;
    for(int i = 20;i + 1;i--)
        if(fa[i][u] != fa[i][v])
            u = fa[i][u],v = fa[i][v];
    return fa[0][u];
}
int X[maxn];
void main(){
    n = read();int u, v, k;
    for(int i = 1;i < n;i++){
        u = read(); v = read();
        edg[u].push_back(v);edg[v].push_back(u);
    }
    for(int i = 1;i <= n;i++)X[i] = val[i] = read();
    sort(X + 1,X + 1 + n);int tot = unique(X + 1,X + 1 + n) - X - 1;
    for(int i = 1;i <= n;i++){val[i] = lower_bound(X + 1,X +  1 + tot,val[i]) - X;}
    dep[1] = 1;dfs(1, 0);int q = read(), ans = 0;
    // for(int i = 1;i <= n;i++)printf("i = %lld, siz = %lld\n",i,tree.d[head[i]].cnt);
    for(int test = 1;test <= q;test++){
        u = (read() ^ ans) % n + 1; v = (read() ^ ans) % n + 1;  k = read();
        int lca = LCA(u, v); vector<int> vec;
        for(int i = 1;i <= min(dep[u] + dep[v] - 2 * dep[lca] + 1,(k - 1) * 62 + 1);i++){
            vec.push_back(X[tree.query(1,n,head[u],head[v],head[lca],head[fa[0][lca]],i)]);
        }
        // printf("u = %lld, v = %lld\n",u,v);for(int i : vec)printf("%lld ",i);puts("");
        int res = 0;
        // printf("u = %lld, v = %d\n",u,v);for(int i : vec){printf("%d ",i);}puts("");
        for(int i = 62;i + 1;i--){
            int cnt = 0;
            for(int j : vec){cnt += ((j >> i) & 1);}
            vector<int> tmp;
            if(cnt >= k){for(int j : vec){if((j >> i) & 1)tmp.push_back(j);}res |= (1ll << i);}
            else{tmp = vec;} vec = tmp;
        }
        ans = res;
        printf("%lld\n",ans);
    }
    return;
}
};
bool edmemory;
signed main(){
    freopen("tmp.in","r",stdin);
    freopen("tmp.out","w",stdout);
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}