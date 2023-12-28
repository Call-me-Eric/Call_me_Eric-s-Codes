#include<bits/stdc++.h>
#define add(u,v,w) e[++tot] = {(v),head[(u)],(w)};head[(u)] = tot;
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0';ch = getchar();}
    return x * f;
}
int n, m;
const int maxn = 100010;
int que[maxn * 3], top;
int cnt[maxn];
int head[maxn], tot, dis[maxn]; bool book[maxn];
struct edge{int topoint, nextedge, weight;}e[maxn * 2];
//inline void add(int u,int v,int w){e[++tot] = {v,head[u],w};head[u] = tot;}
signed main(){
    n = read(); m = read();
    int u, v, opt;
    for(int i = 1;i <= m;i++){
        opt = read(); u = read(); v = read();
        switch(opt){
            case 1:{add(u,v,0);add(v,u,0);break;}
            case 2:{add(u,v,1);break;}
            case 3:{add(v,u,0);break;}
            case 4:{add(v,u,1);break;}
            case 5:{add(u,v,0);break;}
        }
    }
    int i;
    for(i = 1;i + 3 <= n;i += 4){
        add(0,i,1); add(0,i + 1,1);add(0,i + 2,1);add(0,i + 3,1);
        dis[i] = dis[i + 1] = dis[i + 2] = dis[i + 3] = -0x3f3f3f3f3f;
    }
    if(i == n - 2){
        dis[i] = dis[i + 1] = dis[i + 2] = -0x3f3f3f3f3f;add(0,i,1);add(0,i + 1,1);add(0,i + 2,1);
    }
    else if(i == n - 1){
        dis[i] = dis[i + 1] = -0x3f3f3f3f3f;add(0,i,1);add(0,i + 1,1);
    }
    else if(i == n){
        dis[i] = -0x3f3f3f3f3f;add(0,i,1);
    }
    bool flag = false;
    top = 1; que[top] = 0;
    book[0] = true; dis[0] = 0;
    while(top){
        int u = que[top]; top--; book[u] = false;
        for(int i = head[u];i;i = e[i].nextedge){
            int v = e[i].topoint, w = e[i].weight;
            if(dis[v] < dis[u] + w){
                dis[v] = dis[u] + w;
                cnt[v] = cnt[u] + 1;
                if(cnt[v] > n){flag = true;break;}
                if(!book[v]){book[v] = true; que[++top] = v;}
            }
        }
        if(flag)break;
    }
    int ans = 0;
    if(flag){puts("-1");return 0;}
    for(int i = 1;i <= n;i += 4)ans += (dis[i] + dis[i + 1] + dis[i + 2] + dis[i + 3]);
    printf("%lld\n", ans);
    return 0;
}
