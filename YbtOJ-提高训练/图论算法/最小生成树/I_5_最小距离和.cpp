#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0';ch = getchar();}
    return x * f;
}
int n;
const int maxn = 100100;
int tot;
struct edge{int topoint, frompoint, weight;}e[maxn * 4];
void add(int u,int v,int w){
    e[++tot].topoint = v;
    e[tot].frompoint = u;
    e[tot].weight = w;
}
int fa[maxn];
int getf(int x){if(fa[x] != x)fa[x] = getf(fa[x]);return fa[x];}
struct node{int x, y, z,id;}a[maxn];
struct cmpx{bool operator()(node a,node b){return a.x < b.x;}};
struct cmpy{bool operator()(node a,node b){return a.y < b.y;}};
struct cmpz{bool operator()(node a,node b){return a.z < b.z;}};
struct cmp{bool operator()(edge a,edge b){return a.weight < b.weight;}};
signed main(){
    n = read();
    for(int i = 1;i <= n;i++){a[i].x = read(); a[i].y = read();a[i].z = read();a[i].id = i;}
    //addedge
    sort(a + 1,a + 1 + n,cmpx());
    for(int i = 2;i <= n;i++){add(a[i - 1].id,a[i].id,a[i].x - a[i - 1].x);}
    sort(a + 1,a + 1 + n,cmpy());
    for(int i = 2;i <= n;i++){add(a[i - 1].id,a[i].id,a[i].y - a[i - 1].y);}
    sort(a + 1,a + 1 + n,cmpz());
    for(int i = 2;i <= n;i++){add(a[i - 1].id,a[i].id,a[i].z - a[i - 1].z);}
    //ed
    sort(e + 1,e + 1 + tot,cmp());
    int ans = 0, cnt = 0;
    for(int i = 1;i <= n;i++){fa[i] = i;}
    for(int i = 1;i <= tot;i++){
        int u = e[i].frompoint, v = e[i].topoint;
        int fu = getf(u), fv = getf(v);
        if(fu != fv){
            fa[fu] = fv;
            ans += e[i].weight;
            cnt++;
            if(cnt == n - 1)break;
        }
    }
    printf("%lld\n",ans);
    return 0;
}
