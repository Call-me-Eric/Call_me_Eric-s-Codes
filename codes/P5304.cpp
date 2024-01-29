#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 2e5 + 10, maxm = 2e6 + 10;
int n, m, k;
int id[maxn];

int head[maxn], tot;
struct edge{
    int to, nexte, wei;
    edge(int to = 0,int ne = 0,int we = 0):to(to),nexte(ne),wei(we){}
}e[maxm];
void add(int u,int v,int w){e[++tot] = edge(v,head[u],w);head[u] = tot;}

int dis[maxn];bool book[maxn];
struct node{
    int first, second;
    friend bool operator < (node a,node b){return a.first != b.first ? a.first < b.first : a.second < b.second;}
    friend bool operator > (node a,node b){return a.first != b.first ? a.first > b.first : a.second > b.second;}
    node(int f = 0,int s = 0):first(f),second(s){}
};
priority_queue<node,vector<node>,greater<node> > que;
int dijsktra(int S,int T){
    memset(dis,0x3f,sizeof(dis));memset(book,0,sizeof(book));
    dis[S] = 0;que.push(node(dis[S],S));
    while(!que.empty()){
        int u = que.top().second;que.pop();
        if(book[u])continue;book[u] = 1;
        for(int i = head[u];i;i = e[i].nexte){
            int v = e[i].to, w = e[i].wei;
            if(dis[v] > dis[u] + w){
                dis[v] = dis[u] + w;
                que.push(node(dis[v],v));
            }
        }
    }
    return dis[T];
}

signed main(){
int T = read();
while(T--){
    memset(head,0,sizeof(head));tot = 0;
    n = read(); m = read(); k = read();int u, v, w;
    for(int i = 1;i <= m;i++){
        u = read(); v = read(); w = read();
        add(u, v, w);
    }
    for(int i = 1;i <= k;i++)id[i] = read();
    int nod = n, S, T, ans = 0x3f3f3f3f3f3f3f;
    for(int pos = 0;(1 << pos) <= n;pos++){
        S = ++nod; T = ++nod;
        for(int i = 1;i <= k;i++){
            if((id[i] >> pos) & 1)add(S,id[i],0);
            else add(id[i],T,0);
        }
        ans = min(ans,dijsktra(S,T));
        
        S = ++nod; T = ++nod;
        for(int i = 1;i <= k;i++){
            if(!((id[i] >> pos) & 1))add(S,id[i],0);
            else add(id[i],T,0);
        }
        ans = min(ans,dijsktra(S,T));
    }
    printf("%lld\n",ans);
}
    return 0;
}