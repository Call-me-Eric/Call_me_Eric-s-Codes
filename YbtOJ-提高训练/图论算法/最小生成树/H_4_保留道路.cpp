#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0';ch = getchar();}
    return x * f;
}
int n, m;
int wG, wS;
const int maxn = 410, maxm = 50010;
int head[maxn], tot;
int st[maxm], top;
int fa[maxn];
int getf(int x){if(fa[x] != x)fa[x] = getf(fa[x]);return fa[x];}
struct edge{int topoint, g,s,nextedge,frompoint;}e[maxm * 2];
void add(int u,int v,int g,int s){
    e[++tot].topoint = v;
    e[tot].frompoint = u;
    e[tot].g = g;
    e[tot].s = s;
    e[tot].nextedge = head[u];
    head[u] = tot;
}
struct cmp{bool operator()(edge a,edge b){return a.g < b.g;}};
signed main(){
    n = read(); m = read();
    wG = read(); wS = read();
    int u,v,g,s;
    for(int i = 1;i <= m;i++){
        u = read(); v = read(); g = read(); s = read();
        add(u,v,g,s);add(v,u,g,s);
    }
    int ans = 9999999999999990;
    sort(e + 1,e + 1 + tot,cmp());
    for(int i = 1;i <= tot;i++){
        for(int j = 1;j <= n;j++)fa[j] = j;
        int j = 0;
        for(j = top;j;j--){
            if(e[st[j]].s > e[i].s)st[j + 1] = st[j];
            else break;
        }
        top++;
        st[j + 1] = i;
        int cnt = 0;
        for(j = 1;j <= top;j++){
            u = e[st[j]].frompoint, v = e[st[j]].topoint;
            int fu = getf(u), fv = getf(v);
            if(fu != fv){
                fa[fu] = fv;
                st[++cnt] = st[j];
            }
        }
        if(cnt == n - 1){
            ans = min(ans,wG * e[i].g + wS * e[st[cnt]].s);
        }
        top = cnt;
    }
    printf("%lld\n",ans);
    return 0;
}
