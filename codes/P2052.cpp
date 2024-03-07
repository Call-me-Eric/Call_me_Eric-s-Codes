#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 1e6 + 10;
int head[maxn], tot;
struct edge{
    int to, nexte, weight;
    edge(int t = 0,int ne = 0,int w = 0):to(t),nexte(ne),weight(w){}
}e[maxn * 2];
void add(int u,int v,int w){e[++tot] = edge(v,head[u],w);head[u] = tot;}

int n;
int siz[maxn];
int ans;

void dfs(int u,int f){
    siz[u] = 1;
    for(int i = head[u];i;i = e[i].nexte){
        int v = e[i].to, w = e[i].weight;
        if(v == f)continue;
        dfs(v,u); siz[u] += siz[v];
        ans += w * abs(2 * siz[v] - n);
    }
}

signed main(){
    scanf("%lld",&n);int u, v, w;
    for(int i = 1;i < n;i++){
        scanf("%lld%lld%lld",&u,&v,&w);
        // printf("%lld %lld %lld\n",u,v,w);
        add(u,v,w);add(v,u,w);
    }
    dfs(1,0);
    printf("%lld\n",ans);
    return 0;
}