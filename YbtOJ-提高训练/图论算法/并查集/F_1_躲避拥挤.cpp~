#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0';ch = getchar();}
    return x * f;
}
int n, m, q;
int T;
const int maxn = 2e4 + 10, maxm = 1e5 + 10;
struct edge{int topoint, frompoint, weight;}e[maxm];
int fa[maxn], cnt[maxn],res[maxm];
struct questions{int limit, id;}a[maxm];
int getf(int x){if(fa[x] == x)return x;cnt[fa[x]] += cnt[x];cnt[x] = 0;return fa[x] = getf(fa[x]);}
struct cmp1{bool operator()(edge a,edge b){return a.weight < b.weight;}};
struct cmp2{bool operator()(questions a,questions b){return a.limit < b.limit;}};
signed main(){
    T = read();
    while(T--){
    n = read(); m = read(); q = read();
    for(int i = 1;i <= m;i++){e[i] = {read(),read(),read()};}
    for(int i = 1;i <= n;i++){fa[i] = i;cnt[i] = 1;}
    for(int i = 1;i <= q;i++){a[i] = {read(),i};}
    sort(e + 1,e + 1 + m,cmp1());
    sort(a + 1,a + 1 + q,cmp2());
    int ans = 0;
    for(int i = 1,j = 1;i <= q && j <= m;i++){
        for(;j <= m && e[j].weight <= a[i].limit;j++){
            int u = e[j].frompoint, v = e[j].topoint;
            int fu = getf(u), fv = getf(v);
            if(fu != fv){
                ans += cnt[fu] * cnt[fv] * 2;
                fa[fu] = fv;
                getf(u);
            }
        }
        res[a[i].id] = ans;
    }
    for(int i = 1;i <= q;i++)printf("%d\n",res[i]);
    }
    return 0;
}
