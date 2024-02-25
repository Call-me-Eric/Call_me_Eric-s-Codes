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
const int maxn = 2e5 + 10;
int n, q;
char ch[maxn];
int val[maxn];
vector<int> edg[maxn];
namespace Subtask1{
    int ans;
    int anc[20][20];
    int calc(){
        int res = 0;
        for(int i = 1;i <= n;i++){
            for(int j = 1;j <= n;j++){
                res += (anc[i][j] * (val[i] < val[j]));
            }
        }
        // for(int i = 1;i <= n;i++)printf("%d ",val[i]);
        // printf("\nres = %d\n",res);
        return res;
    }
    void dfs(int u){
        if(u == n + 1){
            ans = max(ans,calc());
            return;
        }
        if(val[u] != -1){dfs(u + 1);return;}
        val[u] = 0;dfs(u + 1);
        val[u] = 1;dfs(u + 1);
        val[u] = -1;
    }
    int solve(){ans = 0;dfs(1);return ans;}
    void main(){
        for(int i = 1;i <= n;i++)
            for(int v : edg[i])anc[i][v] = 1;
        for(int k = 1;k <= n;k++)
        for(int i = 1;i <= n;i++)
        for(int j = 1;j <= n;j++)
            if(anc[i][k] & anc[k][j])anc[i][j] = 1;
        for(int i = 1;i <= q;i++){
            int u = read();char c = getchar();
            while(c != '0' && c != '1' && c != '?')c = getchar();
            // printf("u = %d, c = %c\n",u,c);
            val[u] = (isdigit(c) ? (c - '0') : -1);
            printf("%lld\n",solve());
        }
    }
};
namespace Subtask2{
    int fa[maxn], siz[maxn], son[maxn], dep[maxn];
    void dfs1(int u,int f){
        fa[u] = f;siz[u] = 1;dep[u] = dep[f] + 1;
        for(int v : edg[u]){
            dfs1(v, u);siz[u] += siz[v];
            son[u] = siz[v] > siz[son[u]] ? v : son[u];
        }
    }
    int dfn[maxn], low[maxn], idx, top[maxn],rev[maxn];
    void dfs2(int u,int t){
        dfn[u] = ++idx;low[u] = dfn[u] + siz[u] - 1;top[u] = t;rev[idx] = u;
        if(!son[u])return; dfs2(son[u],t);
        for(int v : edg[u])if(v != son[u])dfs2(v,v);
    }
    struct node{
        int sum0, sum1;
        node(int s0 = 0,int s1 = 0):sum0(s0),sum1(s1){}
    }d[maxn << 2];
    node mergenode(node l,node r){return node(l.sum0 + r.sum0,l.sum1 + r.sum1);}
    struct Segment_Tree{
        void build(int l,int r,int p){
            if(l == r){d[p] = node(!val[rev[l]],val[rev[l]]);return;}
            int mid = l + r >> 1;
            build(l,mid,p << 1);build(mid + 1,r,p << 1 | 1);
            d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
        }
        void update(int l,int r,int pos,int p,int upd){
            if(l == r && l == pos){d[p] = node(!upd,upd);return;}
            int mid = l + r >> 1;
            if(pos <= mid)update(l,mid,pos,p << 1,upd);
            else update(mid + 1,r,pos,p << 1 | 1,upd);
            d[p] = mergenode(d[p << 1],d[p << 1 | 1]);
        }
        node query(int l,int r,int s,int t,int p){
            if(s <= l && r <= t)return d[p];
            int mid = l + r >> 1;
            if(t <= mid)return query(l,mid,s,t,p << 1);
            if(mid < s)return query(mid + 1,r,s,t,p << 1 | 1);
            return mergenode(query(l,mid,s,t,p << 1),query(mid + 1,r,s,t,p << 1 | 1));
        }
        void update(int pos,int upd){update(1,n,pos,1,upd);}
        node query(int l,int r){return query(1,n,l,r,1);}
    }tr;
    void update(int pos,int upd){tr.update(dfn[pos],upd);}
    int calc(int u){
        auto tmp1 = tr.query(dfn[u],low[u]);
        int vl = tr.query(dfn[u],low[u]).sum1;
        node tmp2 = node();
        while(u){
            tmp2 = mergenode(tmp2,tr.query(dfn[top[u]],dfn[u]));
            u = fa[top[u]];
        }
        if(vl){return tmp2.sum0;}
        else return tmp1.sum1;
    }
    void main(){
        if(val[1] == -1)val[1] = 0;
        for(int i = 2;i <= n;i++)if(val[i] == -1)val[i] = 1;
        dfs1(1,0);dfs2(1, 1);tr.build(1,n,1);
        int ans = 0;
        for(int i = 1;i <= n;i++)ans += tr.query(dfn[i],low[i]).sum1 * (!val[i]);
        for(int i = 1;i <= q;i++){
            int u = read();char c = getchar();
            while(c != '0' && c != '1' && c != '?')c = getchar();
            int upd = (isdigit(c) ? (c - '0') : -1);
            if(upd == -1){
                if(u == 1)upd = 0;
                else upd = 1;
            }
            ans -= calc(u);
            update(u,upd);
            ans += calc(u);
            printf("%lld\n",ans);
        }
    }
};
void main(){
    freopen("partial.in","r",stdin);
    freopen("partial.out","w",stdout);
    n = read(); q = read();scanf("%s",ch + 1);
    for(int i = 1;i <= n;i++)val[i] = (isdigit(ch[i]) ? (ch[i] - '0') : -1);
    for(int i = 2;i <= n;i++)edg[read()].push_back(i);
    if(q <= 10 && n <= 10)Subtask1::main();
    else Subtask2::main();
    return;
}
};
bool edmemory;
signed main(){
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}