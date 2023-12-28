#include<bits/stdc++.h>
#include<ext/pb_ds/priority_queue.hpp>
#define ll long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 2.5e5 + 10;
const ll INF = 1e13;
int n;
ll x[maxn], y[maxn];

int tot, head[maxn];
struct edge{
    int to, nexte;ll wei;
    edge(int to = 0,int ne = 0,ll we = 0):to(to),nexte(ne),wei(we){}
}e[maxn << 1];
void add(int u,int v,ll w){e[++tot] = edge(v,head[u],w);head[u] = tot;}

ll ans, cnt, dep[maxn];
__gnu_pbds::priority_queue<ll,greater<ll> > A[maxn],B[maxn];

void dfs(int u,int f){
    for(int i = x[u] + 1;i <= y[u];i++)
        A[u].push(dep[u] - INF),cnt++;
    for(int i = y[u] + 1;i <= x[u];i++)
        B[u].push(dep[u]);
    for(int i = head[u];i;i = e[i].nexte){
        int v = e[i].to;ll w = e[i].wei;
        if(v == f)continue;
        dep[v] = dep[u] + w;dfs(v, u);
        A[u].join(A[v]);B[u].join(B[v]);
    }
    while(!A[u].empty() && !B[u].empty() && A[u].top() + B[u].top() < 2LL * dep[u]){
        ll xx = A[u].top(), yy = B[u].top(); A[u].pop(); B[u].pop();
        ans += xx + yy - 2LL * dep[u];
        A[u].push(2 * dep[u] - yy);B[u].push(2 * dep[u] - xx);
    }
}

signed main(){
    freopen("thunder.in","r",stdin);
    freopen("thunder.out","w",stdout);
    n = read();int u, v, w;
    for(int i = 1;i < n;i++){
        u =  read();v = read(); w = read();
        add(u, v, w);add(v, u, w);
    }
    for(int i = 1;i <= n;i++){x[i] = read();y[i] = read();}
    dfs(1 ,1);
    printf("%lld\n",ans + cnt * INF);
    return 0;
}