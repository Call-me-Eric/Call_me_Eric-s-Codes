#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 3) + (x << 1) + ch - '0'; ch = getchar();}
    return x * f;
}

const int maxn = 1e6 + 10;
int n, m;

struct edge{
    int topoint, nextedge, weight;
    edge(int to = 0,int ne = 0,int we = 0):topoint(to),nextedge(ne),weight(we){}
}e[maxn];
int head[maxn], tot;
void add(int u,int v,int w){e[++tot] = edge(v,head[u],w);head[u] = tot;}

stack<int> stk;int color, index;
int col[maxn], dfn[maxn], low[maxn];
int siz[maxn];
void Tarjan(int u){
    low[u] = dfn[u] = ++index;
    stk.push(u);
    for(int i = head[u];i;i = e[i].nextedge){
        int v = e[i].topoint, w = e[i].weight;
        if(!dfn[v]){
            Tarjan(v);
            low[u] = min(low[u], low[v]);
        }else if(!col[v]){
            low[u] = min(low[u], dfn[v]);
        }
    }
    if(low[u] == dfn[u]){
        ++color; int t = 0;
        do{
            t = stk.top(); stk.pop();
            col[t] = color;
        }while(t != u);
    }
}

int head2[maxn], tot2, d[maxn];edge e2[maxn];
void add2(int u,int v,int w){e2[++tot2] = edge(v,head2[u],w); head2[u] = tot2; d[v]++;}
int dp[maxn]; queue<int> que;
int calc(int w){
    int t = sqrt(2 * w + 0.25) - 0.5;
    return w * (t + 1) - (t + 1) * (t + 2) * t / 6;
}

signed main(){
    n = read(); m = read();
    int u, v, w;
    for(int i = 1;i <= m;i++){
        u = read(); v = read(); w = read();
        add(u, v, w);
    }
    int st = read();
    for(int i = 1;i <= n;i++){if(!col[i])Tarjan(i);}
    for(int u = 1;u <= n;u++){
        for(int i = head[u];i;i = e[i].nextedge){
            v = e[i].topoint, w = e[i].weight;
            if(col[v] != col[u]) add2(col[u],col[v],w);
            else siz[col[u]] += calc(w);
        }
    }
    for(int i = 1;i <= color;i++){
        if(!d[i])que.push(i);
        else dp[i] = -0x3f3f3f3f3f3f3f3f;
    }
    dp[col[st]] = siz[col[st]];
    while(!que.empty()){
        int u = que.front();que.pop();
        for(int i = head2[u];i;i = e2[i].nextedge){
            int v = e2[i].topoint, w = e2[i].weight;
            dp[v] = max(dp[v],dp[u] + w + siz[v]);
            d[v]--;
            if(!d[v]) que.push(v);
        }
    }
    int maxx = -1;
    for(int i = 1;i <= color;i++) maxx = max(maxx,dp[i]);
    printf("%lld\n",maxx);
    return 0;
}
//在机房敲了半天发现没有网的网管很emo
//“写完啦，提交一下吧。”
//“诶，这怎么卡住了，你谷又日爆了？”
//“不对呀，这怎么QQ也没动静了。”
//“WTF谁把网掐了？？！”
//“哦我想起来了，今天我们学校作为考点当然要掐网啦。”
//“WK我是不是没办法刷B站了(bushi)”
//“MD还我网！！！！！！！！！！！！！！！！！！！！”