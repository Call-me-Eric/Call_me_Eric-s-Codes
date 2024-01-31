#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f =1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1100;

int n, m, S, T;

struct edge{
    int to, nexte, wei;
    edge(int to = 0,int ne = 0,int we = 0):to(to),nexte(ne),wei(we){}
}e[maxn * maxn * 2][2];
int tot[2],head[maxn][2];
void add(int u,int v,int w,int opt){e[++tot[opt]][opt] = edge(v,head[u][opt],w);head[u][opt] = tot[opt];}

struct node{
    int first, second;
    node(int f = 0,int s = 0):first(f),second(s){}
    friend bool operator < (node a,node b){return a.first != b.first ? a.first < b.first : a.second < b.second;}
    friend bool operator > (node a,node b){return a.first != b.first ? a.first > b.first : a.second > b.second;}
};

typedef priority_queue<node , vector<node> , greater<node> > prique;

int dis[maxn];bool book[maxn];
void kruskal(int S,int opt){
    memset(dis,0x3f,sizeof(dis));memset(book,0,sizeof(book));
    dis[S] = 0;prique que;que.push(node(dis[S],S));
    while(!que.empty()){
        int u = que.top().second;que.pop();
        if(book[u])continue;book[u] = 1;
        for(int i = head[u][opt];i;i = e[i][opt].nexte){
            int v = e[i][opt].to, w = e[i][opt].wei;
            if(dis[v] > dis[u] + w){
                dis[v] = dis[u] + w;
                que.push(node(dis[v],v));
            }
        }
    }
}

signed main(){
    n = read(); m = read(); S = read(); T = read();
    int u, v, w;
    for(int i = 1;i <= m;i++){
        u = read(); v = read(); w = read();
        add(u, v, w, 0); add(v, u, w, 0);
    }
    for(int i = 1;i <= n;i++){
        kruskal(i, 0);
        u = read(); v = read();
        for(int j = 1;j <= n;j++)
            if(dis[j] <= u){add(i,j,v,1);}
    }
    kruskal(S,1);
    printf("%lld",dis[T] == 0x3f3f3f3f3f3f3f3f ? -1 : dis[T]);
    return 0;
}