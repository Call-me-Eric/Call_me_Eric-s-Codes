#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0';ch = getchar();}
    return x * f;
}
int n;
const int maxn = 1e5 + 10;

int head[maxn], tot;
struct edge{
    int topoint, nextedge, weight;
    edge(int t = 0,int n = 0,int w = 0):topoint(t),nextedge(n),weight(w){}
}e[maxn * 2];
void add(int u,int v,int w){e[++tot] = edge(v,head[u],w);head[u] = tot;}
int we[maxn];
void dfs(int u,int fa){
    for(int i = head[u];i;i = e[i].nextedge){
        int v = e[i].topoint, w = e[i].weight;
        if(v == fa)continue;
        we[v] = we[u] ^ w;
        dfs(v, u);
    }
}

int trie[2000010][2], total;
void insert(int x){
    int u = 0;
    for(int i = (1 << 30);i;i >>= 1){
        bool v = x & i;
        if(!trie[u][v])trie[u][v] = ++total;
        u = trie[u][v];
    }
}

signed main(){
    n = read(); int u, v, w;
    for(int i = 1;i < n;i++){
        u = read(); v = read(); w = read();
        add(u, v, w); add(v, u, w);
    }
    dfs(1,0);
    for(int i = 1;i <= n;i++)insert(we[i]);
    int maxx = -1;
    for(int i = 1;i <= n;i++){
        int tmp = we[i], ans = 0; u = 0;
        for(int i = (1 << 30);i;i >>= 1){
            bool v = tmp & i;
            if(trie[u][!v]){
                ans += i;
                u = trie[u][!v];
            }
            else u = trie[u][v];
        }
        maxx = max(maxx, ans);
    }
    printf("%d\n",maxx);
    return 0;
}