#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0';ch = getchar();}
    return x * f;
}
int T, n;
const int maxn = 2e6 + 10;
struct node{int u,v,opt;}e[maxn];
int fa[maxn], op[maxn],a[maxn];
struct cmp{bool operator()(node a,node b){return a.opt > b.opt;}};
int getf(int x){if(fa[x] != x)fa[x] = getf(fa[x]);return fa[x];}
signed main(){
    T = read();
    while(T--){
        int tot = 0;
    n = read();int u, v, opt;bool error = false;
    memset(a,0,sizeof(a));memset(e,0,sizeof(e));memset(fa,0,sizeof(fa));
    for(int i = 1;i <= n;i++){e[i] = {read(),read(),read()};a[++tot] = e[i].u;a[++tot] = e[i].v;}
    sort(a + 1,a + 1 + tot); tot = unique(a + 1,a + 1 + tot) - a;
    for(int i = 1;i <= tot;i++){fa[i] = i;}
    for(int i = 1;i <= n;i++){e[i].u = lower_bound(a + 1,a + 1 + tot,e[i].u) - a;e[i].v = lower_bound(a + 1,a + 1 + tot,e[i].v) - a;}
    sort(e + 1,e + 1 + n,cmp());
    for(int i = 1;i <= n;i++){
        u = e[i].u; v = e[i].v; opt = e[i].opt;
        int fu = getf(u), fv = getf(v);
        if(opt)fa[fu] = fv;
        else if(fu == fv){error = true;break;}
    }
    if(!error)puts("YES");
    else puts("NO");
    }
    return 0;
}
