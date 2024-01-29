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
const int maxn = 1e5 + 10, maxk = 20;
int n, q;
vector<int> edg[maxn];
int fa[maxk + 1][maxn];
int dep[maxn], cf[maxn];
int dfn[maxn], idx;
void dfs(int u,int f){
    fa[0][u] = f;dep[u] = dep[f] + 1;dfn[u] = ++idx;
    for(int i = 1;i <= maxk;i++){fa[i][u] = fa[i - 1][fa[i - 1][u]];}
    for(int v : edg[u])if(v != f){dfs(v, u);cf[u] += cf[v];}
}
int lca[1010][1010];
int LCA(int u,int v){
    if(dep[v] >= dep[u])swap(u, v);
    for(int i = maxk;i + 1;i--)if(dep[fa[i][u]] >= dep[v])u = fa[i][u];
    if(u == v)return u;
    for(int i = maxk;i + 1;i--)
        if(fa[i][u] != fa[i][v]){
            u = fa[i][u];v = fa[i][v];
        }
    return fa[0][u];
}

pair<int,int> st[21][maxn];
int lg[maxn];
vector<pair<int,int> > qry[maxn];
int ans[maxn];
struct BIT{
    int c[maxn];
    inline int lowbit(int x){return x & (-x);}
    void upd(int x,int add){for(;x <= n;x += lowbit(x))c[x] += add;}
    int qry(int x){int s = 0;for(;x;x -= lowbit(x))s += c[x];return s;}
    int qry(int l,int r){return qry(r) - qry(l - 1);}
}tr;

void main(){
    n = read();int u, v;
    for(int i = 1;i < n;i++){
        u = read(); v = read();
        edg[u].push_back(v);edg[v].push_back(u);
    }
    dfs(1, 0); q = read();
    auto solve = [](int l,int r){
        int res = 0;
        for(int i = 1;i <= n;i++)cf[i] = 0;
        for(int i = l;i <= r;i++)
            for(int j = i + 1;j <= r;j++){
                cf[i]++;cf[j]++;cf[lca[i][j]] -= 2;
            }
        dfs(1, 0);
        for(int i = 1;i <= n;i++){if(cf[i] > 0)res++;}
        return res;
    };
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= n;j++){
            lca[i][j] = LCA(i,j);
        }
    }
    if(n <= 50){
        for(int i = 1;i <= q;i++){
            u = read(); v = read();
            int ans = 0;
            for(int l = u;l <= v;l++){
                for(int r = l + 1;r <= v;r++){
                    ans += solve(l, r);
                }
            }
            printf("%d\n",ans);
        }
    }
    else{
        lg[0] = -1;
        for(int i = 1;i <= n;i++){st[0][i] = make_pair(dfn[i],dfn[i]);lg[i] = lg[i >> 1] + 1;}
        for(int j = 1;j <= 20;j++){
            for(int i = 1;i + (1 << j) - 1 <= n;i++){
                st[j][i].first = min(st[j - 1][i].first,st[j - 1][i + (1 << (j - 1))].first);
                st[j][i].second = max(st[j - 1][i].second,st[j - 1][i + (1 << (j - 1))].second);
            }
        }
        auto query = [](int l,int r){
            int k = lg[r - l + 1];
            return make_pair(min(st[k][l].first,st[k][r - (1 << k) + 1].first),max(st[k][l].second,st[k][r - (1 << k) + 1].second));
        };
        for(int i = 1;i <= q;i++){
            int u = read(), v = read();
            qry[v].push_back(make_pair(u,i));
        }
        for(int r = 1;r <= n;r++){
            for(int l = 1;l < r;l++){
                auto tmp = query(l,r);
                tr.upd(l,tmp.second - tmp.first);
            }
            for(auto i : qry[r]){ans[i.second] = tr.qry(i.first,r);}
        }
        for(int i = 1;i <= q;i++)printf("%d\n",ans[i]);
    }
    return;
}
};
bool edmemory;
signed main(){
    freopen("babawu.in","r",stdin);
    freopen("babawu.out","w",stdout);
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}