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
const int maxn = 5e5 + 10;
struct tree{
    int fa[maxn];vector<int> edg[maxn];
    void add(int u,int v){edg[u].push_back(v);edg[v].push_back(u);}
    void dfs(int u,int f){fa[u] = f;for(int v : edg[u])if(v != f)dfs(v, u);}
}g1, g2;
int n;

int fa[maxn];
int getf(int x){return fa[x] == x ? x : fa[x] = getf(fa[x]);}
vector<pair<pair<int,int>,pair<int,int> > > ans;
void dfs(int u,int f){
    for(int v : g1.edg[u]){
        if(v != f){
            dfs(v, u);
            if(getf(u) != getf(v))
                ans.push_back(make_pair(make_pair(u, v),make_pair(getf(v),g2.fa[getf(v)])));
        }
    }
}
void main(){
    n = read();int u, v;
    for(int i = 1;i < n;i++){u = read();v = read();g1.add(u, v);}
    for(int i = 1;i < n;i++){u = read();v = read();g2.add(u, v);}
    g1.dfs(1,1);g2.dfs(1,1);
    fa[1] = 1;
    for(int i = 2;i <= n;i++){
        int f = g2.fa[i];
        if(g1.fa[f] == i || g1.fa[i] == f)fa[i] = f;
        else fa[i] = i;
    }
    dfs(1, 0);
    printf("%d\n",ans.size());
    for(auto i : ans){
        int x = i.first.first, y = i.first.second, u = i.second.first, v = i.second.second;
        printf("%d %d %d %d\n",x,y,u,v);
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