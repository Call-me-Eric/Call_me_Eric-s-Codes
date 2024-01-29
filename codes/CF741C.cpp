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
const int maxn = 3e5 + 10;
vector<int> edg[maxn];
int n;
int c[maxn];
pair<int,int> pr[maxn];
void dfs(int u,int col){for(int v : edg[u]){if(!c[v]){c[v] = 3 - col;dfs(v, c[v]);}}}
void main(){
    n = read();
    for(int i = 1;i <= n;i++){
        int u = read(), v = read(); edg[u].push_back(v);edg[v].push_back(u);
        pr[i] = make_pair(u, v);
    }
    for(int i = 1;i <= n * 2;i++)if(i & 1){edg[i].push_back(i + 1);edg[i + 1].push_back(i);}
    for(int i = 1;i <= n * 2;i++)if(!c[i]){dfs(i,1);c[i] = 1;}
    for(int i = 1;i <= n * 2;i++)for(int j : edg[i])if(c[i] == c[j]){puts("-1");return;}
    for(int i = 1;i <= n;i++)printf("%d %d\n",c[pr[i].first],c[pr[i].second]);
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