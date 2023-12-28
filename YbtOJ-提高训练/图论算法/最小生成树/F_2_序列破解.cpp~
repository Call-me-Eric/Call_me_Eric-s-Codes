#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0';ch = getchar();}
    return x * f;
}
int n;
const int maxn = 2100;
int head[maxn], tot;
struct edge{
    int frompoint, topoint, weight,nextedge;
}e[maxn * maxn];
void add(int u,int v,int w){
    e[++tot].topoint = v;
    e[tot].frompoint = u;
    e[tot].weight = w;
    e[tot].nextedge = head[u];
    head[u] = tot;
}
int fa[maxn];
int getf(int x){if(fa[x] != x)fa[x] = getf(fa[x]);return fa[x];}
struct cmp{
    bool operator() (edge a,edge b){
        return a.weight < b.weight;
    }
};
signed main(){
    n = read();
    for(int i = 1;i <= n;i++)
        for(int j = i;j <= n;j++)
            add(i - 1,j,read());
    sort(e + 1,e + 1 + tot,cmp());
    for(int i = 0;i <= n;i++)fa[i] = i;
    int ans = 0, cnt = 0;
    for(int i = 1;i <= tot;i++){
        int u = e[i].frompoint, v = e[i].topoint;
        int fu = getf(u), fv = getf(v);
        if(fu != fv){
            fa[fu] = fv;
            ans += e[i].weight;
            cnt++;
            if(cnt == n)break;
        }
    }
    printf("%d\n",ans);
    return 0;
}
