#include<bits/stdc++.h>
using namespace std;
bool stmemory;
namespace Call_me_Eric{
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10;
int n, q;
struct node{
    int ch[2];
    int maxx, summ;
    node(int maxx = 0,int summ =  0,int lp = 0,int rp = 0
    ):maxx(maxx),summ(summ){ch[0] = lp;ch[1] = rp;}
}d[maxn * 50];
#define C(p,x) d[p].ch[x]
node mergenode(node l,node r,node p = node()){return node(max(l.maxx,r.maxx),l.summ + r.summ,p.ch[0],p.ch[1]);}
int tot, head[maxn];
struct Segment_Tree{
    void update(int l,int r,int pos,int &p,int upd){
        if(!p)p = ++tot;
        if(l == r && l == pos){d[p] = node(upd,upd);return;}
        int mid = l + r >> 1;
        if(pos <= mid){update(l,mid,pos,C(p,0),upd);}
        else{update(mid + 1,r,pos,C(p,1),upd);}
        d[p] = mergenode(d[C(p,0)],d[C(p,1)],d[p]);
    }
    node query(int l,int r,int s,int t,int p){
        if(s <= l && r <= t)return d[p];
        int mid = l + r >> 1;
        if(t <= mid)return query(l,mid,s,t,C(p,0));
        if(mid < s)return query(mid + 1,r,s,t,C(p,1));
        return mergenode(query(l,mid,s,t,C(p,0)),query(mid + 1,r,s,t,C(p,1)));
    }
    node query(int l,int r,int p){return query(1,n,l,r,p);}
    void update(int pos,int upd,int &p){update(1,n,pos,p,upd);}
}tree;
int w[maxn], c[maxn];
vector<int> edg[maxn];
int fa[maxn], dep[maxn], siz[maxn], son[maxn];
void dfs1(int u,int f){
    fa[u] = f;dep[u] = dep[f] + 1;siz[u] = 1;
    for(int v : edg[u]){
        if(v != f){
            dfs1(v, u);siz[u] += siz[v];
            son[u] = siz[v] > siz[son[u]] ? v : son[u];
        }
    }
}
int top[maxn], dfn[maxn], rev[maxn], idx;
void dfs2(int u,int t){
    dfn[u] = ++idx;rev[idx] = u;top[u] = t;
    if(!son[u])return; dfs2(son[u],t);
    for(int v : edg[u])if(v != fa[u] && v != son[u])dfs2(v, v);
}
void main(){
    n = read(); q = read();int u, v;
    for(int i = 1;i <= 1e5;i++){head[i] = ++tot;}
    for(int i = 1;i <= n;i++){w[i] = read();c[i] = read();}
    for(int i = 1;i < n;i++){
        u = read(), v = read();
        edg[u].push_back(v);edg[v].push_back(u);
    }
    dfs1(1,1);dfs2(1,1);
    for(int i = 1;i <= n;i++){tree.update(dfn[i],w[i],head[c[i]]);}
    char opt[20];
    for(int i = 1;i <= q;i++){
        scanf("%s",opt);u = read(), v = read();
        if(opt[0] == 'C'){
            
        }
        else{
        }
    }
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