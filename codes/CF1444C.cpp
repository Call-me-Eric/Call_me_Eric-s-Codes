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
const int maxn = 1.5e6 + 10;
int n, m, k;
struct DSU{
    int fa[maxn], dep[maxn];
    int getf(int x){return fa[x] == x ? x : getf(fa[x]);}
    struct node{
        int x, y, dep;
        node(int x = 0,int y = 0,int dep = 0):x(x),y(y),dep(dep){}
    };
    stack<node> stk;
    void merge(int x,int y){
        int fx = getf(x), fy = getf(y);
        if(fx == fy)return;
        if(dep[fx] > dep[fy])swap(fx,fy);
        stk.push(node(fx,fy,dep[fx] == dep[fy]));
        fa[fx] = fy;dep[fy] += dep[fx] == dep[fy];
    }
    void trace(int ver){
        while(stk.size() > ver){
            node x = stk.top();stk.pop();
            fa[x.x] = x.x;dep[x.y] -= x.dep;
        }
    }
    void init(int n){for(int i = 1;i <= n * 2;i++)fa[i] = i,dep[i] = 1;}
}dsu;
int col[maxn];
struct edge{
    int x, y, colx, coly;
    edge(int x = 0,int y = 0,int colx = 0,int coly = 0):x(x),y(y),colx(colx),coly(coly){}
    friend bool operator < (edge a,edge b){
        return a.colx == b.colx ? a.coly < b.coly : a.colx < b.colx;
    }
}e[maxn];int tot;
bool book[maxn];
void main(){
    n = read(); m = read(); k = read();
    for(int i = 1;i <= n;i++)col[i] = read();
    dsu.init(n);int cnt = k;
    for(int i = 1;i <= m;i++){
        int u = read(), v = read();
        if(col[u] != col[v]){
            e[++tot] = edge(u,v,col[u],col[v]);
            if(e[tot].colx > e[tot].coly)swap(e[tot].colx,e[tot].coly);
            continue;
        }
        if(book[col[u]])continue;
        if(dsu.getf(u) == dsu.getf(v)){
            cnt--;book[col[u]] = 1;continue;
        }
        dsu.merge(u,v + n);dsu.merge(v,u + n);
    }
    int ver = dsu.stk.size();
    if(cnt == 0){puts("0");return;}
    long long ans = (cnt - 1ll) * cnt / 2ll;
    sort(e + 1,e + 1 + tot);bool flag = false;
    for(int i = 1;i <= tot;i++){
        edge t = e[i];
        if(book[t.colx] || book[t.coly])continue;
        if(t.colx != e[i - 1].colx || t.coly != e[i - 1].coly){
            dsu.trace(ver);flag = false;
        }
        if(flag)continue;
        if(dsu.getf(t.x) == dsu.getf(t.y)){
            flag = true;ans--;continue;
        }
        dsu.merge(t.x,t.y + n);dsu.merge(t.y,t.x + n);
    }
    printf("%lld\n",ans);
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