#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 3) + (x << 1) + ch - '0';ch = getchar();}
    return x * f;
}
int n, m, R, K;
const int maxn = 5 * 1e5 + 10;
struct edge{
    int nextedge, topoint, weight;
}e[maxn * 2];
bool book[maxn];
int dist[maxn], times[maxn * 2];
int used[maxn], edgee[maxn], anss[maxn];
int head[maxn], tot, l[maxn], r[maxn];
void add(int u,int v){
    e[++tot].nextedge = head[u];
    e[tot].topoint = v;
    e[tot].weight = 1;
    head[u] = tot;
}
void dij(int s,int t){
    queue<int> que;
    que.push(s);
    book[s] = 1;
    for(int i = 1;i <= n;i++)dist[i] = 0x3f3f3f3f;
    dist[s] = 0;
    while(!que.empty()){
        int tmp = que.front();que.pop();book[tmp] = 0;
        for(int i = head[tmp];i;i = e[i].nextedge){
            int v = e[i].topoint;
            if(dist[v] > dist[tmp] + 1){
                dist[v] = dist[tmp] + 1;
                used[v] = tmp; edgee[v] = i;
                if(!book[v]){
                    book[v] = 1;
                    que.push(v);
                }
            }
        }
    }
    int tmp = t;
    while(tmp != s){
        times[edgee[tmp]]++;
        tmp = used[tmp];
    }
    return;
}
signed main(){
    int u , v;
    freopen("hide.in","r",stdin);
    freopen("hide.out","w",stdout);
    n = read(); m = read(); K = read(); R = read();
    for(int i = 1;i <= m;i++){
        u = read(); v = read();
        add(u, v);
        add(v, u);
    }
    for(int i = 1;i <= K;i++){
        l[i] = read(); r[i] = read();
        dij(l[i],r[i]);
    }
    for(int i = 1;i <= tot;i++)anss[(i - 1) / 2] += times[i];
    sort(anss,anss + tot / 2);
    int ans = 0;
    for(int i = tot / 2 - 1;i >= tot / 2 - R;i--){
        ans += anss[i];
    }
    printf("%d\n",ans);
    return 0;
}