#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e6 + 10;
bool st;
int n, m;
int head[maxn], tot;
struct edge{
    int to, nexte;
    edge(int to = 0,int ne = 0):to(to),nexte(ne){}
}e[maxn << 1];
void add(int u,int v){e[++tot] = edge(v,head[u]);head[u] = tot;}
int val[maxn];ll ans;

bool visited[maxn];bool book[maxn];

ll f[maxn][2];int x, y, edg;
bool ed;

void getcircle(int u,int f){
    // printf("getcir : u = %d\n",u);
    book[u] = 1;
    for(int i = head[u];i;i = e[i].nexte){
        int v = e[i].to;
        if(i != f && (i != (f ^ 1))){
            if(book[v]){x = u, y = v;edg = i;return;}
            getcircle(v,i);
        }
    }
    book[u] = 0;
}
void getbook(int u){
    if(visited[u])return; visited[u] = 1;f[u][0] = f[u][1] = 0;
    for(int i = head[u];i;i = e[i].nexte){int v = e[i].to;getbook(v);}
}
void dfs(int u,int fa){
    f[u][1] = val[u];
    for(int i = head[u];i;i = e[i].nexte){
        int v = e[i].to;
        if(i != fa && i != (fa ^ 1) && i != edg && i != (edg ^ 1)){
            dfs(v, i);
            f[u][0] += max(f[v][0],f[v][1]);
            f[u][1] += f[v][0];
        }
    }
}
void clear(int u,int fa){
    f[u][0] = f[u][1] = 0;
    for(int i = head[u];i;i = e[i].nexte){
        int v = e[i].to;
        if(i != fa && i != edg && i != (edg ^ 1)){dfs(v, i ^ 1);}
    }
}
void solve(int st){
    edg = 0;getcircle(st,0);
    dfs(x,0);ll ans1 = f[x][0];getbook(x);
    dfs(y,0);ans1 = max(ans1,f[y][0]);
    ans += ans1;
}

signed main(){
    n = read(); int u, v;tot = 1;
    for(int i = 1;i <= n;i++){val[i] = read();}
    for(int i = 1;i <= n;i++){
        u = read() + 1;v = read() + 1;
        add(u, v);add(v, u);
    }
    for(int i = 1;i <= n;i++){if(!visited[i])solve(i);}
    double k;scanf("%lf",&k);
    printf("%.1lf\n",(double)ans * k);
    return 0;
}