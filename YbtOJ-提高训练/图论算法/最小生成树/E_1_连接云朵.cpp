#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0';ch = getchar();}
    return x * f;
}
int n, m, k;
const int maxn = 1010, maxm = 1e4 + 10;
int head[maxn], tot;
struct edge{
    int topoint, nextedge,frompoint,weight;
}e[maxm * 2];
void add(int u,int v,int w){
    e[++tot].topoint = v;
    e[tot].frompoint = u;
    e[tot].weight = w;
    e[tot].nextedge = head[u];
    head[u] = tot;
}
struct cmp{
    bool operator ()(edge a,edge b){
        return a.weight < b.weight;
    }
};
int fa[maxn];
int getf(int x){if(fa[x] != x)fa[x] = getf(fa[x]);return fa[x];}
signed main(){
    n = read(); m = read(); k = read();
    int u, v, w;
    for(int i = 1;i <= m;i++){
        u = read(); v  = read(); w = read();
        add(u,v,w);
    }
    for(int i = 1;i <= n;i++)fa[i] = i;
    sort(e + 1,e + 1 + tot,cmp());
    int cnt = n, ans = 0;
    for(int i = 1;i <= m;i++){
        u = e[i].frompoint; v = e[i].topoint;
        int fu = getf(u), fv = getf(v);
        if(fu != fv){
            fa[fu] = fv;
            cnt--;
            ans += e[i].weight;
            if(cnt == k)break;
        }
    }
    if(cnt != k){puts("No Answer");}
    else printf("%d\n",ans);
    return 0;
}
