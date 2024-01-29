#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 610, maxk = 4100 * 5;
int n, k;
int head[maxk], tot;
struct edge{
    int to, nexte, wei;int id;
    edge(int to = 0,int ne = 0,int wei = 0,int id = -1):to(to),nexte(ne),wei(wei),id(id){}
}e[maxk * 200];
void add(int u,int v,int w,int id = -1){e[++tot] = edge(v,head[u],w,id);head[u] = tot;}

struct node{
    int first, second, third;
    node(int f = 0,int s = 0,int t = 0):first(f),second(s),third(t){}
    friend bool operator < (node a,node b){return a.first == b.first 
    ? (a.second == b.second ? a.third < b.third : a.second < b.second) : a.first < b.first;}
    friend bool operator > (node a,node b){return a.first == b.first 
    ? (a.second == b.second ? a.third > b.third : a.second > b.second) : a.first > b.first;}
};
priority_queue<node, vector<node>, greater<node> > que;

int dis[maxk][1 << 8];bool book[maxk][1 << 8];

signed main(){
    n = read(); k = read();
    for(int j = 1;j <= k;j++){
        for(int i = 1;i <= n;i++){add(i,i + j * n,read(),j - 1);}
        for(int i = 1;i <= n;i++){add(i + j * n,i,read());}
        int m = read();int u, v, w;
        for(int i = 1;i <= m;i++){
            u = read(); v = read(); w = read();
            add(u + j * n,v + j * n,w);add(v + j * n,u + j * n,w);
        }
    }
    memset(dis,0x3f,sizeof(dis));dis[1][(1 << k) - 1] = 0; que.push(node(0,1,(1 << k) - 1));
    while(!que.empty()){
        node u = que.top();que.pop();if(book[u.second][u.third])continue;book[u.second][u.third] = 1;
        for(int i = head[u.second];i;i = e[i].nexte){
            int v = e[i].to, w = e[i].wei, id = e[i].id;
            if(id != -1){
                if((u.third & (1 << id)) == 0)continue;
                if(dis[v][u.third ^ (1 << id)] > dis[u.second][u.third] + w){
                    dis[v][u.third ^ (1 << id)] = dis[u.second][u.third] + w;
                    que.push(node(dis[v][u.third ^ (1 << id)],v,u.third ^ (1 << id)));
                }
            }
            else{
                if(dis[v][u.third] > dis[u.second][u.third] + w){
                    dis[v][u.third] = dis[u.second][u.third] + w;
                    que.push(node(dis[v][u.third],v,u.third));
                }
            }
        }
    }
    int ans = 0x3f3f3f3f3f3f3f3f;
    for(int sta = 0;sta < (1 << k);sta++)
        ans = min(ans,dis[n][sta]);
    printf("%lld\n",ans);
    return 0;
}