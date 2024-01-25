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
int n, q;
int fa[maxn];
int edg[2][maxn];
int a[maxn], b[maxn];
void dfs(int u){
    // cerr << "u = " << u << "\n";
    if(edg[0][u]){dfs(edg[0][u]);dfs(edg[1][u]);}
    b[u] = a[u] + abs(b[edg[0][u]] - b[edg[1][u]]);
}
void main(){
    n = read();
    for(int i = 1;i <= n;i++){
        int u = read(), v = read();
        edg[0][i] = u;edg[1][i] = v;
        fa[u] = fa[v] = i;
    }fa[0] = 0;
    for(int i = 1;i <= n;i++)a[i] = read();
    dfs(1);q = read();
    while(q--){
        int u = read();a[u] = read(); 
        while(u){b[u] = a[u] + abs(b[edg[0][u]] - b[edg[1][u]]);u = fa[u];}
        printf("%d\n",b[1]);
    }
    return;
}
};
bool edmemory;
signed main(){
    freopen("hypnotic.in","r",stdin);
    freopen("hypnotic.out","w",stdout);
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}