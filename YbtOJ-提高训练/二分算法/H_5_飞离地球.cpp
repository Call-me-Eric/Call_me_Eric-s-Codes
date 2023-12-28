#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0';ch = getchar();}
    return x * f;
}
int T, n, m;
const int maxn = 110;
int head[maxn], tot, dis[maxn], cnt[maxn];
bool edg[maxn][maxn], book[maxn];
struct edge{int topoint, weight,nextedge;}e[maxn * maxn];
void add(int u,int v,int w){e[++tot] = {v,w,head[u]};head[u] = tot;}
bool floyd(){
    for(int i = 1;i <= n;i++)edg[i][i] = true;
    for(int k = 1;k <= n;k++)
        for(int i = 1;i <= n;i++)
            if(edg[i][k])
                for(int j = 1;j <= n;j++)
                    if(edg[i][k] && edg[k][j])edg[i][j] = true;
    return edg[1][n];
}
bool check(int d){
    dis[1] = 0;book[1] = true;
    queue<int> que;que.push(1);
    while(!que.empty()){
        int u = que.front();que.pop();
        book[u] = false;
        for(int i = head[u];i;i = e[i].nextedge){
            int v = e[i].topoint, w = e[i].weight;
            if(dis[v] > dis[u] + w + d && edg[v][n]){
                dis[v] = dis[u] + w + d;
                cnt[v] = cnt[u] + 1;
                if(cnt[v] > n)return false;
                if(!book[v]){que.push(v);book[v] = true;}
            }
        }
    }
    return dis[n] >= 0 && dis[n] != 0x3f3f3f3f;
}
signed main(){
    T = read();
while(T--){
    n = read(); m = read();
    memset(e,0,sizeof(e));tot = 0;memset(head,0,sizeof(head));
    memset(edg,0,sizeof(edg));
    int u, v, w, l = -1e6, r = 1e6;
    for(int i = 1;i <= m;i++){
        u = read(); v = read(); w = read();
        add(u,v,w); edg[u][v] = true;
    }
    if(!floyd()){puts("-1");continue;}
    int ans = -1;
    while(l <= r){
        memset(book,0,sizeof(book));
        memset(cnt,0,sizeof(cnt));memset(dis,0x3f,sizeof(dis));
        int mid = (l + r) >> 1;
        if(check(mid)){r = mid - 1;ans = dis[n];}
        else l = mid + 1;
    }
    printf("%d\n",ans);
}
    return 0;
}
