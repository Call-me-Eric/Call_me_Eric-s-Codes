#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0';ch = getchar();}
    return x * f;
}
int n, m, k;
const int maxn = 1e3 + 10,maxm = 1e4 + 10;
int head[maxn], tot, dis[maxn];bool book[maxn];
struct edge{int topoint, weight,nextedge;}e[maxm * 2];
void add(int u,int v,int w){e[++tot] = {v,w,head[u]};head[u] = tot;}
bool check(int mid){
    queue<int> que;
    memset(dis,0x3f,sizeof(dis));
    que.push(1);book[1] = true;dis[1] = 0;
    while(!que.empty()){
        int u = que.front(); que.pop();
        book[u] = false;
        for(int i = head[u];i;i = e[i].nextedge){
            int v = e[i].topoint, w = (e[i].weight > mid);
            if(dis[v] > dis[u] + w){
                dis[v] = dis[u] + w;
                if(!book[v]){
                    que.push(v);book[v] = 1;
                }
            }
        }
    }
    return dis[n] <= k;
}
signed main(){
    int u, v, w;
    n = read(); m = read(); k = read();
    for(int i = 1;i <= m;i++){
        u = read(); v = read(); w = read();
        add(u,v,w); add(v,u,w);
    }
    int l = 0, ans = -1, r = 1e6;
    while(l <= r){
        int mid = (l + r) >> 1;
        if(check(mid)){ans = mid;r = mid - 1;}
        else l = mid + 1;
    }
    printf("%d\n",ans);
    return 0;
}
