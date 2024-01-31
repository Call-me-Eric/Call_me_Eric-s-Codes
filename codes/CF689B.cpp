#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 2e5 + 10,INF = 0x3f3f3f3f;
int n;

int head[maxn], tot;
struct edge{
    int to, nexte, wei;
    edge(int to = 0,int ne = 0,int wei = 0):to(to),nexte(ne),wei(wei){}
}e[maxn << 2];
void add(int u,int v,int w){e[++tot] = edge(v,head[u],w);head[u] = tot;}

int dis[maxn];bool book[maxn];
typedef pair<int,int> pii;
priority_queue<pii,vector<pii>,greater<pii> > que;

signed main(){
    n = read();
    for(int i = 1;i <= n;i++)add(i,read(),1), dis[i] = INF;
    for(int i = 1;i < n;i++) add(i,i + 1,1),add(i + 1,i,1);
    dis[1] = 0;que.push(make_pair(0, 1));
    while(!que.empty()){
        int u = que.top().second;que.pop();
        if(book[u])continue;book[u] = 1;
        for(int i = head[u];i;i = e[i].nexte){
            int v = e[i].to;
            if(dis[v] > dis[u] + e[i].wei){
                dis[v] = dis[u] + e[i].wei;
                que.push(make_pair(dis[v],v));
            }
        }
    }
    for(int i = 1;i <= n;i++)printf("%d ",dis[i]);
    return 0;
}