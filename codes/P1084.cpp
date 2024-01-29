#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0'; ch = getchar();}
    return x * f;
}
const int maxn = 5e4 + 10;
int n, m;
int army[maxn];

int head[maxn] ,tot;
struct edge{
    int topoint, nextedge, weight;
    edge(int to = 0,int ne = 0,int we = 0):topoint(to),nextedge(ne),weight(we){}
}e[maxn * 2];
void add(int u,int v,int w){e[++tot] = edge(v,head[u],w); head[u] = tot;}

int dep[maxn], fa[maxn][21], dis[maxn][21], rootdis[maxn];
void dfs(int u,int f){
    for(int i = head[u];i;i = e[i].nextedge){
        int v = e[i].topoint, w = e[i].weight;
        if(v == f)continue;
        fa[v][0] = u; dep[v] = dep[u] + 1;
        rootdis[v] = rootdis[u] + w; dis[v][0] = w;
        dfs(v,u);
    }
}

pair<int,int> h[maxn];
bool stay[maxn], need[maxn];
int htot = 0, timetot = 0, nedtot = 0;
int _time[maxn], ned[maxn];
bool dfs1(int u){
    bool leafpoint = true;
    if(stay[u])return true;
    for(int i = head[u];i;i = e[i].nextedge){
        int v = e[i].topoint;
        if(v == fa[u][0])continue;
        leafpoint = false;
        if(!dfs1(v))return 0;
    }
    if(leafpoint)return 0;
    return 1;
}
bool check(int mid){
    memset(stay,0,sizeof(stay));
    memset(need,0,sizeof(need));
    memset(h,0,sizeof(h));
    memset(_time,0,sizeof(_time));
    memset(ned,0,sizeof(ned));

    htot = 0; timetot = 0; nedtot = 0;
    for(int i = 1;i <= m;i++){
        int u = army[i], cnt = 0;
        for(int j = 20;j + 1;j--){
            if(fa[u][j] > 1 && cnt + dis[u][j] <= mid){
                cnt += dis[u][j];
                u = fa[u][j];
            }
        }
        if(fa[u][0] == 1 && cnt + dis[u][0] <= mid)
            h[++htot] = make_pair(mid - cnt - dis[u][0],u);
        else stay[u] = true;
    }

    for(int i = head[1];i;i = e[i].nextedge)
        if(!dfs1(e[i].topoint))need[e[i].topoint] = true;

    sort(h + 1,h + 1 + htot);
    for(int i = 1;i <= htot;i++){
        if(need[h[i].second] && h[i].first < dis[h[i].second][0])need[h[i].second] = false;
        else _time[++timetot] = h[i].first;
    }
    
    for(int i = head[1];i;i = e[i].nextedge){int v = e[i].topoint; if(need[v])ned[++nedtot] = dis[v][0];}

    if(timetot < nedtot)return 0;
    sort(ned + 1,ned + 1 + nedtot);sort(_time + 1,_time + 1 + timetot);
    int i = 1, j = 1;
    while(i <= nedtot && j <= timetot){
        if(_time[j] >= ned[i]){i++; j++;}
        else j++;
    }
    if(i > nedtot)return 1;
    return 0;
}

signed main(){
    int l = 0, r = 0, mid = 0, ans = -1;
    n = read(); int u, v, w;
    for(int i = 1;i < n;i++){
        u = read(); v = read(); w = read();
        add(u, v, w); add(v, u, w);
        r += w;
    }

    m = read();
    for(int i = 1;i <= m;i++)army[i] = read();

    dep[1] = 0;fa[1][0] = 1; dis[1][0] = 0; rootdis[1] = 0;
    dfs(1,0);
    for(int i = 1;i <= 20;i++){
        for(int u = 1;u <= n;u++){
            fa[u][i] = fa[fa[u][i - 1]][i - 1];
            dis[u][i] = dis[u][i - 1] + dis[fa[u][i - 1]][i - 1];
        }
    }

    while(l <= r){
        int mid = (l + r) >> 1;
        if(check(mid)){
            r = mid - 1;
            ans = mid;
        }
        else l = mid + 1;
    }

    printf("%lld\n",ans);
    return 0;
}