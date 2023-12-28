#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0';ch = getchar();}
    return x * f;
}
int n, m, k,s,t;
const int maxn = 10010, maxm = 50010, maxk = 11;
int head[maxn], tot, dis[maxn][maxk];
bool book[maxn][maxk];
struct edge{int topoint, nextedge, weight;}e[maxm * 2];
void add(int u,int v,int w){e[++tot] = {v,head[u],w};head[u] = tot;}
signed main(){
    int u, v, w;
    n = read(); m = read(); k = read();
    s = read() + 1; t = read() + 1;
    for(int i = 1;i <= m;i++){
        u = read() + 1; v = read() + 1; w = read();
        add(u,v,w); add(v,u,w);
    }
    memset(dis,0x3f,sizeof(dis));
    queue<pair<int,int> > que;
    que.push(make_pair(s,0));book[s][0] = true;dis[s][0] = 0;
    while(!que.empty()){
        pair<int,int> u = que.front();que.pop();book[u.first][u.second] = false;
        for(int i = head[u.first];i;i = e[i].nextedge){
            int v = e[i].topoint, w = e[i].weight;
            if(dis[v][u.second] > dis[u.first][u.second] + w){
                dis[v][u.second] = dis[u.first][u.second] + w;
                if(!book[v][u.second]){
                    book[v][u.second] = true;
                    que.push(make_pair(v,u.second));
                }
            }
            if(u.second < k && dis[v][u.second + 1] > dis[u.first][u.second]){
                dis[v][u.second + 1] = dis[u.first][u.second];
                if(!book[v][u.second + 1]){
                    book[v][u.second + 1] = true;
                    que.push(make_pair(v,u.second + 1));
                }
            }
        }
    }
    int ans = 0x3f3f3f3f;
    for(int i = 0;i <= k;i++){ans = min(ans,dis[t][i]);}
    printf("%d\n",ans);
    return 0;
}
