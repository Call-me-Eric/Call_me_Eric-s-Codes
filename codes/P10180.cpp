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
int n, q;
struct DSU{
    int fa[maxn], siz[maxn], dep[maxn];
    void init(){for(int i = 1;i <= n;i++){fa[i] = i;siz[i] = dep[i] = 1;}}
    struct node{
        int x, y, dep, sizy;
        node(int x = 0,int y = 0,int dep = 0,int sizy = 0
        ):x(x),y(y),dep(dep),sizy(sizy){}
    };
    int ver;stack<node> stk;
    int getf(int x){return fa[x] == x ? x : getf(fa[x]);}
    int merge(int x,int y){
        int fx = getf(x), fy = getf(y);
        if(fx == fy)return 0;if(dep[fx] > dep[fy])swap(fx,fy);
        stk.push(node(fx,fy,dep[fx] == dep[fy],siz[fy]));
        int det = ((siz[fx] + siz[fy]) * (siz[fx] + siz[fy])) - (siz[fx] * siz[fx] + siz[fy] * siz[fy]);
        siz[fy] += siz[fx];  dep[fy] += dep[fy] == dep[fx];fa[fx] = fy;
        return det;
    }
    void trace(int s){
        while(stk.size() > s){
            auto u = stk.top();stk.pop();
            int fx = u.x, fy = u.y, dp = u.dep, sy = u.sizy;
            fa[fx] = fx;siz[fy] = sy;dep[fy] -= dp;
        }
    }
}dsu;
typedef pair<int,int> pii;
int col[maxn];
map<pii,vector<pii> > mp;
map<pii,int> mem;
int sum[maxn];
void main(){
    n = read(); q = read();int u, v;
    for(int i = 1;i <= n;i++)col[i] = read();
    dsu.init(); 
    for(int i = 2;i <= n;i++){
        u = read(); v = i;
        if(col[v] == col[u]){dsu.merge(u, v);}
        else{
            int x = col[u], y = col[v];
            if(x > y)swap(x, y);
            mp[make_pair(x, y)].push_back(make_pair(u, v));
        }
    }
    for(int i = 1;i <= n;i++)if(dsu.fa[i] == i)sum[col[i]] += dsu.siz[i] * dsu.siz[i];
    while(q--){
        int x = read(), y = read();if(x > y)swap(x, y);
        int ans = mem[make_pair(x, y)];
        if(ans != 0){printf("%lld\n",ans);continue;}

        int ver = dsu.ver;
        ans = sum[x] + sum[y];
        auto tmp = mp[make_pair(x, y)];
        for(auto i : tmp){
            u = i.first, v = i.second;
            ans += dsu.merge(u, v);
        }
        printf("%lld\n",ans);
        mem[make_pair(x, y)] = ans;
        dsu.trace(ver);
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