#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0';ch = getchar();}
    return x * f;
}
int n, m;
int T;
const int maxn = 2e3 + 10, maxm = 3e3 + 10;
int head[maxn],cnt[maxn],dis[maxn], tot;
bool book[maxn];
struct edge{
    int topoint, nextedge, weight;
}e[maxm * 5];
void add(int u,int v,int w){
    e[++tot].nextedge = head[u];
    e[tot].topoint = v;
    e[tot].weight = w;
    head[u] = tot;
}
bool SPFA(){
    dis[1] = 0;book[1] = true;
    queue<int> que;que.push(1);
    cnt[1] = 0;
    while(!que.empty()){
        int u = que.front();que.pop();
        for(int i = head[u];i;i = e[i].nextedge){
            int v = e[i].topoint, w = e[i].weight;
            if(dis[v] > dis[u] + w){
                cnt[v] = cnt[u] + 1;
                dis[v] = dis[u] + w;
                if(cnt[v] >= n)return true;
                if(!book[v]){que.push(v);book[v] = true;}
            }
        }
        book[u] = false;
    }
    return false;
}
signed main(){
    T = read();
    while(T--){
        memset(book,0,sizeof(book));
        memset(head,0,sizeof(head));
        memset(dis,0x7f,sizeof(dis));
        memset(e,0,sizeof(e));tot = 0;
        n = read(); m = read();int u, v, w;
        for(int i = 1;i <= m;i++){
            u = read(); v = read(); w = read();
            add(u,v,w);
            if(w >= 0) add(v,u,w);
        }
        if(SPFA())puts("YE5");
        else puts("N0");
    }
    return 0;
}
