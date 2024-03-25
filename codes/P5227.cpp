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
const int maxn = 2e5 + 10;
int n, m;
pair<int,int> edg[maxn];
int k;
struct DSU{
    int fa[maxn], dep[maxn], siz[maxn];
    struct node{
        int fx, fy, depy, sizy;
        node(int fx = 0,int fy = 0,int depy = 0,int sizy = 0
        ):fx(fx),fy(fy),depy(depy),sizy(sizy){}
    }stk[maxn];
    int top;
    void init(int n){top = 0;for(int i = 1;i <= n;i++){fa[i] = i;dep[i] = siz[i] = 1;}}
    int getf(int x){return fa[x] == x ? x : getf(fa[x]);}
    void merge(int x,int y){
        x = getf(x);y = getf(y);
        if(x == y)return;
        if(dep[x] > dep[y])swap(x, y);
        stk[++top] = node(x,y,dep[x] == dep[y],siz[y]);
        siz[y] += siz[x];dep[y] += (dep[x] == dep[y]);fa[x] = y;
    }
    void trace(int x = -1){
        if(x < 0){x += top;}
        while(top > x){
            node tp = stk[top];top--;
            int x = tp.fx, y = tp.fy, sizy = tp.sizy, depy = tp.depy;
            fa[x] = x;siz[y] = sizy;dep[y] = depy;
        }
    }
}dsu;
bool ans[maxn];
struct Segment_Tree{
    vector<int> d[maxn << 2];
    void update(int l,int r,int s,int t,int p,int upd){
        if(s <= l && r <= t){d[p].push_back(upd);return;}
        int mid = l + r >> 1;
        if(s <= mid)update(l,mid,s,t,p << 1,upd);
        if(mid < t)update(mid + 1,r,s,t,p << 1 | 1,upd);
    }
    void getans(int l,int r,int p){
        // printf("%d %d %d\n",l,r,p);
        int mid = l + r >> 1, ver = dsu.top;
        for(int i : d[p]){dsu.merge(edg[i].first,edg[i].second);}
        if(l == r){ans[l] = dsu.siz[dsu.getf(1)] == n;}
        else{getans(l,mid,p << 1);getans(mid + 1,r,p << 1 | 1);}
        dsu.trace(ver);
    }
    void update(int l,int r,int upd){if(r < l)return;update(1,k,l,r,1,upd);}
    void getans(){getans(1,k,1);}
}tree;
int lst[maxn];
void main(){
    n = read(); m = read();int u, v;dsu.init(n);
    for(int i = 1;i <= m;i++){u = read(), v = read();edg[i] = make_pair(u, v);}
    for(int i = 1;i <= m;i++){lst[i] = 0;}
    k = read();
    for(int i = 1;i <= k;i++){
        for(int j = read();j;j--){
            int x = read();
            tree.update(lst[x] + 1,i - 1,x);
            lst[x] = i;
        }
    }
    for(int i = 1;i <= m;i++){tree.update(lst[i] + 1,k,i);}
    tree.getans();
    for(int i = 1;i <= k;i++){puts(ans[i] ? "Connected" : "Disconnected");}
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