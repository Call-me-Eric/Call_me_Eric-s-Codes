#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 5e3 + 10, maxm = 5e5 + 10, INF = 0x3f3f3f3f;

int n, m;

int head[maxn], tot = 1;
struct edge{
    int to, nexte, cap, flow;
    edge(int to = 0,int ne = 0,int ca = 0,int fl = 0):to(to),nexte(ne),cap(ca),flow(fl){}
}e[maxm * 2];
void add(int u,int v,int cap){e[++tot] = edge(v,head[u],cap);head[u] = tot;}
void addd(int u,int v,int cap){add(u,v,cap);add(v, u, 0);}

int dep[maxn], cur[maxn];
int dfs(int u,int flow,int T){
    // printf("%lld\n",u);
    if(u == T)return flow;
    int rest = 0, tmp = 0;
    for(int i = cur[u];i && flow;i = e[i].nexte){
        cur[u] = i; int v = e[i].to;
        if(e[i].cap - e[i].flow > 0 && (dep[v] == dep[u] + 1)){
            tmp = dfs(v,min(flow,e[i].cap - e[i].flow),T);
            if(tmp == 0)dep[v] = INF;
            e[i].flow += tmp; e[i ^ 1].flow -= tmp;
            flow -= tmp;rest += tmp;
            if(!flow)return rest;
        }
    }
    return rest;
}
bool bfs(int S,int T){
    queue<int> que;
    for(int i = 1;i <= T;i++){dep[i] = INF;cur[i] = 0;}
    que.push(S);dep[S] = 1; cur[S] = head[S];
    while(!que.empty()){
        int u = que.front(); que.pop();
        for(int i = head[u];i;i = e[i].nexte){
            int v = e[i].to;
            if(e[i].cap - e[i].flow > 0 && dep[v] == INF){
                que.push(v);
                cur[v] = head[v];
                dep[v] = dep[u] + 1;
                if(v == T)return 1;
            }
        }
    }
    return 0;
}
int Dinic(int S,int T){
    int mxflow = 0;
    while(bfs(S,T)){mxflow += dfs(S,INF,T);}
    return mxflow;
}

int a, b, c;
int id[3][maxn];

bool used[maxn];
void solve(){
    int cnt = 0;
    a = read(); b = read(); c = read();
    int minn = min(a, min(b, c));
    for(int i = 1;i <= a;i++)
        for(int j = 1;j <= b;j++)
            for(int k = 1;k <= c;k++)
                if(read()){id[0][++cnt] = i; id[1][cnt] = j; id[2][cnt] = k;}
    if(b == minn){swap(a, b);swap(id[0],id[1]);}
    else if(c == minn){swap(a, c);swap(id[0],id[2]);}
    int ans = INF;
    // printf("%d %d %d\n",a,b,c);
    // for(int i = 1;i <= cnt;i++)printf("%d %d %d\n",id[0][i],id[1][i],id[2][i]);
    int S = b + c + 1,T = b + c + 2, tmp = 0;
    for(int sta = 0;sta < (1 << a);sta++){
        memset(head,0,sizeof(head));tot = 1;tmp = 0;
        for(int j = 0;j < a;j++){
            if((1 << j) & sta){used[j + 1] = 1;tmp++;}
            else{used[j + 1] = 0;}
        }
        int tmp1 = 0;
        for(int j = 1;j <= cnt;j++){
            if(!used[id[0][j]]){
                addd(id[1][j],id[2][j] + b,INF);tmp1++;
            }
        }
        for(int i = 1;i <= b;i++)addd(S,i,1);
        for(int i = b + 1;i <= b + c;i++)addd(i,T,1);
        // int t = Dinic(S,T);
        // printf("i = %d, tmp1 = %d, Dinic = %d, tmp = %d\n",sta,tmp1,t,tmp);
        ans = min(ans,Dinic(S,T) + tmp);
    }
    printf("%d\n",ans);
}

signed main(){
    int T = read();
    while(T--)solve();
    return 0;
}