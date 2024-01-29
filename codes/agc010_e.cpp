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
const int maxn = 2e3 + 10;
bool e[maxn][maxn];
vector<int> edg[maxn];
int n, a[maxn], in[maxn];
bool vis[maxn];
typedef pair<int,int> pii;
void dfs(int u){vis[u] = 1;for(int i = 1;i <= n;i++)if(!vis[i] && e[u][i]){in[i]++;edg[u].push_back(i);dfs(i);}}

void main(){
    n = read();for(int i = 1;i <= n;i++){a[i] = read();}
    sort(a + 1,a + 1 + n);
    for(int i = 1;i <= n;i++)
        for(int j = i + 1;j <= n;j++)
            if(__gcd(a[i],a[j]) > 1)e[i][j] = e[j][i] = 1;
    for(int i = 1;i <= n;i++)if(!vis[i])dfs(i);
    priority_queue<pii,vector<pii>,less<pii> > que;
    for(int i = 1;i <= n;i++){if(!in[i])que.push(make_pair(a[i],i));}
    while(!que.empty()){
        int u = que.top().second;que.pop();
        printf("%d ",a[u]);
        for(int v : edg[u]){if(!--in[v])que.push(make_pair(a[v],v));}
    }
    puts("");
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