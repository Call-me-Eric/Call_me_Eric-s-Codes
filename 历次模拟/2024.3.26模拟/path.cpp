#include<bits/stdc++.h>
#define int long long
using namespace std;
bool stmemory;
namespace Call_me_Eric{
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 2e5 + 10;
int n, m, k;
int a[maxn], b[maxn], c[maxn];
typedef pair<int,int> pii;
vector<pii> edg[maxn];
inline int cost(int x,int y){
    int pwx[6] = {x != 0}, pwy[6] = {1}, ans = 0;
    for(int i = 1;i <= 5;i++){pwx[i] = pwx[i - 1] * x;pwy[i] = pwy[i - 1] * y;}
    for(int i = 1;i <= k;i++){ans += c[i] * pwx[a[i]] * pwy[b[i]];}
    return ans;
}
namespace BF{
int upp[maxn];
map<int,int> dis[maxn];
map<int,bool> book[maxn];
priority_queue<pair<int,pii>,vector<pair<int,pii> >,greater<pair<int,pii> > > que;
void dijkstra(int S){
    dis[S][0] = 0;que.push(make_pair(dis[S][0],make_pair(0,S)));
    for(int i = 1;i <= n;i++)upp[i] = 0x3f3f3f3f3f3f3f3f;
    while(!que.empty()){
        int u = que.top().second.second, w1 = que.top().second.first;que.pop();
        if(book[u].find(w1) != book[u].end() || w1 >= upp[u])continue;book[u][w1] = 1;upp[u] = w1;
        for(auto i : edg[u]){
            int v = i.first, w = i.second;
            if(dis[v].find(w) == dis[v].end() || dis[v][w] > dis[u][w1] + cost(w1,w)){
                dis[v][w] = dis[u][w1] + cost(w1,w);
                que.push(make_pair(dis[v][w],make_pair(w,v)));
            }
        }
    }
}
void main(){
    dijkstra(1);
    for(int i = 2;i <= n;i++){
        int ans = 0x3f3f3f3f3f3f3f3f;
        if(dis[i].empty()){puts("-1");continue;}
        for(auto j : dis[i]){ans = min(ans,j.second);}
        printf("%lld\n",ans);
    }
}
};
void main(){
    n = read(); m = read(); k = read();int u, v, w;
    for(int i = 1;i <= k;i++){a[i] = read();b[i] = read();c[i] = read();}
    for(int i = 1;i <= m;i++){
        u = read(); v = read(); w = read();
        edg[u].push_back(make_pair(v, w));
    }
    BF::main();
    return;
}
};
bool edmemory;
signed main(){
    freopen("path.in","r",stdin);
    freopen("path.out","w",stdout);
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}
/*
4 4 1
1 1 1
1 2 10
2 3 1
3 2 1 
2 4 10
*/