#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0'; ch = getchar();}
    return x * f;
}
const int maxn = 3e3 + 10, maxm = 1e4 + 10;
const double eps = 1e-10;

int n, m;
int head[maxn], tot;
struct edge{int to, nexte;double wei;edge(int t = 0,int ne = 0,double w = 0):to(t),nexte(ne),wei(w){}}e[maxm];
void add(int u,int v,double w){e[++tot] = edge(v,head[u],w);head[u] = tot;}

bool book[maxn];
double dis[maxn];
bool spfa(double mid,int u){
    book[u] = 1;
    for(int i = head[u];i;i = e[i].nexte){
        int v = e[i].to; double w = e[i].wei - mid;
        if(dis[v] > dis[u] + w){
            dis[v] = dis[u] + w;
            if(book[v] || spfa(mid,v))return true;
        }
    }
    book[u] = 0;
    return false;
}
bool check(double mid){
    bool flag = 0;
    memset(dis,0,sizeof(dis));
    memset(book,0,sizeof(book));
    for(int i = 1;i <= n;i++){
        if(spfa(mid, i))return true;
    }
    return false;
}

signed main(){
    n = read(); m = read(); int u, v;double w;
    for(int i = 1;i <= m;i++){
        u = read(); v = read();scanf("%lf",&w);
        add(u, v, w * 1.0);
    }
    double l = -1e7 - 10, r = 1e7 + 10, mid = 0;
    while(r - l >= eps){
        mid = (l + r) / 2.0;
        if(check(mid)){r = mid;}
        else l = mid;
    }
    printf("%.8lf\n",l);
    return 0;
}