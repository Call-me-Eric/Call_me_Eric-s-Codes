#include<bits/stdc++.h>
using namespace std;
bool stmemory;
namespace Call_me_Eric{
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 5e5 + 10,INF = 0x3f3f3f3f;
vector<pair<int,int> > edg[maxn];
int n, m, dis[maxn][2];
bool book[maxn];
typedef pair<int,int> pii;
priority_queue<pii,vector<pii>,greater<pii> > que;
void main(){
    n = read(); m = read();
    for(int i = 1;i <= m;i++){
        int u = read(), v = read();
        edg[v].push_back(make_pair(u,read()));
    }
    if(n == 1){puts("0\n0");return;}
    memset(dis,0x3f,sizeof(dis));dis[n][0] = dis[n][1] = 0;
    que.push(make_pair(0,n));
    while(!que.empty()){
        int u = que.top().second;que.pop();
        if(book[u])continue;book[u] = 1;
        int d = max(dis[u][0],dis[u][1]);
        for(auto i : edg[u]){
            int v = i.first, c = i.second;
            if(dis[v][c] > d + 1){
                dis[v][c] = d + 1;int x = max(dis[v][0],dis[v][1]);
                if(x < INF){que.push(make_pair(x,v));}
            }
        }
    }
    int x = max(dis[1][0],dis[1][1]);
    printf("%d\n",x < INF ? x : -1);
    for(int i = 1;i <= n;i++)putchar('0' + (dis[i][0] < dis[i][1]));puts("");
    return;
}
};
bool edmemory;
signed main(){
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}