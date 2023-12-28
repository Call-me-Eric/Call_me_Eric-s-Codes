#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0';ch = getchar();}
    return x * f;
}
int T, n, sum;
const int maxn = 2e4 + 10;
int fa[maxn], tot[maxn];
int getf(int x){if(fa[x] == x)return x;tot[fa[x]] += tot[x];tot[x] = 0;return fa[x] = getf(fa[x]);}
struct edge{int topoint, frompoint, weight;}e[maxn];
struct cmp{bool operator()(edge a,edge b){return a.weight < b.weight;}};
signed main(){
    T = read();
    while(T--){
    n = read(); memset(e,0,sizeof(e)); fa[n] = n; tot[n] = 1; sum = 0;
    for(int i = 1;i < n;i++){e[i] = {read(),read(),read()};sum += e[i].weight;fa[i] = i;tot[i] = 1;}
    sort(e + 1,e + n,cmp());
    for(int i = 1;i < n;i++){
        int u = e[i].topoint, v = e[i].frompoint, w = e[i].weight;
        int fu = getf(u), fv = getf(v);
        if(fu == fv)continue;
        sum += (tot[fu] * tot[fv] - 1) * (w + 1);
        fa[fu] = fv;getf(u);
    }
    printf("%lld\n",sum);
    }
    return 0;
}
