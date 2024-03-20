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
const int maxn = 2e3 + 10, maxm = 1e6 + 10;
int n, m;
vector<int> edg[maxn];
int dfn[maxn], low[maxn], col[maxn],color, idx;
bool instack[maxn];
stack<int> stk;
void Tarjan(int u){
    dfn[u] = low[u] = ++idx;stk.push(u);instack[u] = 1;
    for(int v : edg[u]){
        if(!dfn[v]){Tarjan(v);low[u] = min(low[u],low[v]);}
        else if(instack[v]){low[u] = min(low[u],dfn[v]);}
    }
    if(dfn[u] == low[u]){
        color++;int v = 0;
        do{
            v = stk.top();stk.pop();
            col[v] = color;instack[v] = 0;
        }while(v != u);
    }
}
void solve(){
    for(int i = 0;i < n * 2;i++){edg[i].clear();dfn[i] = low[i] = col[i] = instack[i] = 0;}
    m = read();int u, v, a, b;color = idx = 0;while(!stk.empty())stk.pop();
    for(int i = 1;i <= m;i++){
        u = read(); v = read(); a = read(); b = read();
        edg[u * 2 + a].push_back(2 * v + 1 - b);
        edg[v * 2 + b].push_back(2 * u + 1 - a);
    }
    for(int i = 0;i < n * 2;i++)if(!dfn[i])Tarjan(i);
    for(int i = 0;i < n * 2;i += 2)if(col[i] == col[i + 1]){puts("NO");return;}
    puts("YES");
}
void main(){while(scanf("%d",&n) != EOF)solve();return;}
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