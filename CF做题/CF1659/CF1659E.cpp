#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10;
int n, m, q;

int head[maxn], tot;
struct edge{
    int to, nexte, wei;
    edge(int to = 0,int ne = 0,int we = 0):to(to),nexte(ne),wei(we){}
}e[maxn << 1];
void add(int u,int v,int w){e[++tot] = edge(v,head[u],w);head[u] = tot;}

struct DSU{
    int fa[maxn];
    DSU(){for(int i = 1;i < maxn;i++)fa[i] = i;}
    int getf(int x){return x == fa[x] ? x : fa[x] = getf(fa[x]);}
    bool query(int x,int y){return getf(x) == getf(y);}
    void mergef(int x,int y){if(!query(x,y))fa[getf(x)] = getf(y);}
}x[31], y[31];

bool book[maxn];

signed main(){
    n = read(); m = read();int u, v, w;
    for(int i = 1;i <= m;i++){
        u = read(); v = read(); w = read();
        add(u,v , w);add(v, u, w);if((w & 1) == 0)book[u] = book[v] = 1;
        for(int j = 0;j <= 30;j++){if(w & (1 << j))x[j].mergef(u, v);}
    }

    for(int i = 1;i <= 30;i++){
        y[i] = x[i];
        for(int j = 1;j <= n;j++)
            if(book[j])y[i].mergef(j,0);
    }

    q = read();
    for(int i = 1;i <= q;i++){
        u = read(); v = read();
        bool flag = false;
        for(int j = 0;j <= 30;j++)
            if(x[j].query(u,v)){flag = true;break;}
        if(flag){puts("0");continue;}
        for(int j = 1;j <= 30;j++)
            if(y[j].query(u,0)){flag = true;break;}
        if(flag){puts("1");continue;}
        puts("2");
    }
    return 0;
}