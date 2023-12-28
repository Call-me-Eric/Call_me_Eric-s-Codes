#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0';ch = getchar();}
    return x * f;
}
int n, m, k;
const int maxn = 1e5 + 10, maxm = 5e5 + 10;
bool book[maxn];
int fa[maxn];
int getf(int x){if(fa[x] != x)fa[x] = getf(fa[x]);return fa[x];}
int head[maxn], tot;
struct edge{int topoint, nextedge,weight,frompoint;}e[maxm * 2];
void add(int u,int v,int w){
    e[++tot].topoint = v;
    e[tot].frompoint = u;
    e[tot].weight = w;
    e[tot].nextedge = head[u];
    head[u] = tot;
}
struct cmp{bool operator() (edge a,edge b){return a.weight > b.weight;}};
signed main(){
    int u, v, w, sum = 0;
    n = read(); m = read(); k = read();
    for(int i = 1;i <= k;i++)book[read() + 1] = 1;
    for(int i = 1;i <= m;i++){
        u = read() + 1; v = read() + 1; w = read();
        add(u,v,w); sum += w;
    }
    for(int i = 1;i <= n;i++){fa[i] = i;}
    sort(e + 1,e + 1 + tot,cmp());
    int ans = 0;
    for(int i = 1;i <= tot;i++){
        int u = e[i].frompoint, v = e[i].topoint;
        int fu = getf(u), fv = getf(v);
        if(fu == fv)ans += e[i].weight;
        else if(book[fu] + book[fv] != 2){
            ans += e[i].weight;
            if(book[fu])fa[fv] = fu;
            else fa[fu] = fv;
        }
    }
    printf("%lld\n",sum - ans);
    return 0;
}
