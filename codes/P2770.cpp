#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x  << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 110, INF = 0x3f3f3f3f;
string name[maxn];
map<string,int> mp;
int n, m;

int head[maxn], tot = 1;
struct edge{
    int to, nexte, cap, flow, cost;
    edge(int to = 0,int ne = 0,int ca = 0,int co = 0,int fl = 0):to(to),nexte(ne),cap(ca),cost(co),flow(fl){}
}e[maxn * maxn * 2];
void add(int u,int v,int cap,int cost){e[++tot] = edge(v,head[u],cap,cost,0);head[u] = tot;}
void addd(int u,int v,int cap,int cost){add(u, v, cap,cost);add(v ,u ,0,-cost);}
int in[maxn], out[maxn], S, T;

int pre[maxn], dis[maxn];
bool book[maxn];
bool SPFA(){
    memset(book,0,sizeof(book));
    memset(dis,0x3f,sizeof(dis));
    memset(pre,0,sizeof(pre));
    queue<int> que;
    que.push(S);dis[S] = 0;book[S] = 1;
    while(!que.empty()){
        int u = que.front();que.pop(); book[u] = 0;
        // cout << u << '\n';
        for(int i = head[u];i;i = e[i].nexte){
            int v = e[i].to, w = e[i].cost;
            if(e[i].cap - e[i].flow > 0){
                if(dis[v] > dis[u] + w){
                    dis[v] = dis[u] + w; pre[v] = i;
                    if(!book[v]){que.push(v);book[v] = 1;}
                }
            }
        }
    }
    return pre[T];
}

bool book1[maxn << 1];
void dfs1(int u){
    book1[u] = 1;cout << name[u - n] << '\n';
    for(int i = head[u];i;i = e[i].nexte){
        int v = e[i].to;
        if(v <= n && 1 == e[i].flow || 2 == e[i].flow){dfs1(v + n);break;}
    }
}
void dfs2(int u){
    for(int i = head[u];i;i = e[i].nexte){
        int v = e[i].to;
        if(v <= n &&(1 == e[i].flow || 2 == e[i].flow) && !book1[v + n]){dfs2(v + n);break;}
    }
    cout << name[u - n] << '\n';
}

signed main(){
    ios::sync_with_stdio(false);
    cin >> n >> m; int u, v, w;
    for(int i = 1;i <= n;i++)in[i] = i,out[i] = i + n;
    for(int i = 1;i <= n;i++){
        cin >> name[i]; mp[name[i]] = i;
        // in[i] = ++cntnod; out[i] = ++cntnod;
        if(i == 1 || i == n){
            addd(in[i],out[i],2, -1);
            if(i == 1)S = in[i];
            if(i == n)T = out[i];
        }
        else addd(in[i],out[i],1, -1);
    }
    bool flag = 0;
    for(int i = 1;i <= m;i++){
        string t1, t2; cin >> t1 >> t2;
        u = min(mp[t1],mp[t2]), v = max(mp[t2],mp[t1]);
        if(u == 1 && v == n)flag = 1;
        addd(out[u],in[v],INF, 0);
    }
    int maxflow = 0, maxcost = 0;
    while(SPFA()){
        // puts("111111");
        int fl = INF;
        for(int i = pre[T];i;i = pre[e[i ^ 1].to]){
            fl = min(fl,e[i].cap - e[i].flow);
        }
        maxflow += fl;maxcost += fl * dis[T];
        for(int i = pre[T];i;i = pre[e[i ^ 1].to]){
            e[i].flow += fl;e[i ^ 1].flow -= fl;
        }
    }
    maxcost = -maxcost;
    if(maxflow == 2){
        cout << maxcost - 2 << '\n';
        dfs1(out[1]); dfs2(out[1]);
    }
    else if(flag){
        // cout << "38253483258738484593\n";
        cout << "2\n";
        cout << name[1] << '\n' << name[n] << '\n' << name[1] << '\n';
    }
    else cout << "No Solution!\n";
    return 0;
}