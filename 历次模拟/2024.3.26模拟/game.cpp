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
const int maxn = 1e5 + 10;
int n, q, o;
struct edge{
    int u, v, w;
    edge(int u = 0,int v = 0,int w = 0):u(u),v(v),w(w){}
}e[maxn];
int tot = 0;
bool book[maxn][2];
int getans(int sta){
    int ans1 = 0, ans2 = 0;
    for(int i = 1;i <= tot;i++){
        int u = e[i].u, v = e[i].v, w = e[i].w;
        if(!u)continue;
        bool book1 = book[u][0], book2 = book[v][0];
        if(book1 == book2){
            if(book1)ans1 += w;
            else ans2 += w;
        }
    }
    return abs(ans1 - ans2);
}
int dfs(int sta,int opt){
    int ans = opt ? 0x3f3f3f3f : -0x3f3f3f3f;
    if(sta == (1 << n) - 1)return getans(sta);
    for(int i = 1;i <= n;i++){
        if(!((sta >> (i - 1)) & 1)){
            book[i][opt] = 1;
            int res = dfs(sta | (1 << (i - 1)),opt ^ 1);
            book[i][opt] = 0;
            if((!opt && res > ans) || (opt && res < ans)){ans = res;}
        }
    }
    return ans;
}
void main(){
    n = read(); q = read(); o = read();
    int lastans = 0;
    for(int i = 1;i <= q;i++){
        int opt = read(), u = read() ^ (o * lastans);
        if(opt == 1){
            int v = read() ^ (o * lastans), w = read() ^ (o * lastans);
            e[i] = edge(u,v,w);
        }
        else{e[i] = edge();}tot = i;
        printf("%d\n",dfs(0,0));
    }
    return;
}
};
bool edmemory;
signed main(){
    freopen("game.in","r",stdin);
    freopen("game.out","w",stdout);
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}
/*
5 4 0
1 1 2 4
1 1 3 1
1 1 4 1
1 1 5 1
*/