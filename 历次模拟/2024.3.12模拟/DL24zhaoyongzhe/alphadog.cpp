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
const int maxn = 5e5 + 10, mod = 1e9 + 7;
int n, M;
int fa[maxn];
int getf(int x){return fa[x] == x ? x : fa[x] = getf(fa[x]);}

typedef pair<int,int> pii;

vector<int> edg[maxn];
vector<pair<pii ,int> > e;
int pw[maxn];

pii operator + (pii a,pii b){
    return make_pair((a.first * pw[b.second] % mod + b.first) % mod,a.second + b.second);
}

int dfn[maxn], idx, rev[maxn], siz[maxn];
void dfs(int u){
    dfn[u] = ++idx;rev[idx] = u;siz[u] = 1;
    // cerr << "idx = " << idx << endl;
    for(int v : edg[u]){dfs(v);siz[u] += siz[v];}
}
struct Segment_Tree{
    struct node{
        bool leaf;pii sum; pii tag;
        node(bool leaf = false,pii sum = make_pair(0,0),pii tag = make_pair(0,0)):sum(sum),tag(tag),leaf(leaf){}
    }d[maxn << 2];
    void build(int l,int r,int p){
        if(l == r){d[p] = node(1);return;}
        int mid = l + r >> 1;
        build(l,mid,p << 1);build(mid + 1,r,p << 1 | 1);
        d[p] = node(0);
    }
    void upda(int p,pii upd){
        d[p].tag = d[p].tag + upd;
        if(d[p].leaf){d[p].sum = d[p].sum + upd;}
    }
    void pushdown(int p){
        if(d[p].tag.second != 0){
            upda(p << 1,d[p].tag);upda(p << 1 | 1,d[p].tag);
            d[p].tag = make_pair(0,0);
        }
    }
    void update(int l,int r,int s,int t,int p,pii tag){
        if(s <= l && r <= t){upda(p,tag);return;}
        int mid = l + r >> 1;pushdown(p);
        if(s <= mid)update(l,mid,s,t,p << 1,tag);
        if(mid < t)update(mid + 1,r,s,t,p << 1 | 1,tag);
    }
    node query(int l,int r,int pos,int p){
        if(l == r && l == pos){return d[p];}
        int mid = l + r >> 1;pushdown(p);
        if(pos <= mid)return  query(l,mid,pos,p << 1);
        else return query(mid + 1,r,pos,p << 1 | 1);
    }
    node query(int pos){return query(1,n,pos,1);}
    void update(int l,int r,pii upd){update(1,n,l,r,1,upd);}
}tree;

void main(){
    n = read(); M = read(); int u, v, tmp = n;
    pw[0] = 1;for(int i = 1;i <= n * 2;i++){pw[i] = (pw[i - 1] * 10ll) % mod;fa[i] = i;}
    for(int i = 1;i <= M;i++){
        u = read(); v = read();
        if(getf(u) != getf(v)){
            n++;int fu = getf(u), fv = getf(v);
            edg[n].push_back(fu);edg[n].push_back(fv);
            e.push_back(make_pair(make_pair(u, v), i));
            fa[fu] = n;fa[fv] = n;fa[n] = n;
        }
    }
    // assert(e.size() == tmp - 1);
    // cerr << "1113111111111111\n";
    dfs(n);for(int i = 1;i <= n;i++)fa[i] = i;
    tree.build(1,n,1);
    // cerr << "2222222222222222\n";
    int tmpp = tmp;
    for(auto i : e){
        int u = i.first.first, v = i.first.second, w = i.second;
        // printf("(%lld,%lld) %lld\n",u,v,w);
        tmp++;int fu = getf(u), fv = getf(v);
        pii au = tree.query(dfn[u]).sum, av = tree.query(dfn[v]).sum;
        tree.update(dfn[fu],dfn[fu] + siz[fu] - 1,make_pair(w,1) + av);
        tree.update(dfn[fv],dfn[fv] + siz[fv] - 1,make_pair(w,1) + au);
        fa[fu] = fa[fv] = tmp;fa[tmp] = tmp;
    }
    // for(int i = 1;i <= n;i++){
    //     for(int j : edg[i]){
    //         printf("%lld-> %lld\n",i,j);
    //     }
    //     printf("i = %lld, dfn = %lld, siz = %lld\n",i,dfn[i],siz[i]);
    // }
    for(int i = 1;i <= tmpp;i++)printf("%lld\n",tree.query(dfn[i]).sum.first);
    return;
}
};
bool edmemory;
signed main(){
    freopen("alphadog.in","r",stdin);
    freopen("alphadog.out","w",stdout);
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}