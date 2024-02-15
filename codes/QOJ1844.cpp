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
const int maxn = 1e6 + 10;
int n, m;
vector<int> edg[maxn], ans;
bool deg[maxn], dl[maxn];
inline void op(int x){ans.push_back(x);}
inline void del(int x){
    op(x);deg[x] = 0;dl[x] = 1;
    for(int v : edg[x])if(!dl[v])deg[v] ^= 1;
    for(int v : edg[x])if(!dl[v] && deg[v])del(v);
}
int idx, dfn[maxn], low[maxn], cnt;
stack<int> stk;
vector<int> e2[maxn];//建立一颗圆方树方便找答案
void dfs(int u){
    dfn[u] = low[u] = ++idx;stk.push(u);
    for(int v : edg[u]){
        if(!dfn[v]){
            dfs(v);
            if(low[v] >= dfn[u]){
                cnt++;int w = stk.top();
                do{
                    w = stk.top();stk.pop();
                    e2[w].push_back(cnt);e2[cnt].push_back(w);
                }while(w != v);
                e2[u].push_back(cnt);e2[cnt].push_back(u);
            }
            else low[u] = min(low[v],low[u]);
        }
        else low[u] = min(dfn[v],low[u]);
    }
}
bool vis[maxn];
void work(int u,int pre){
    vis[u] = 1;
    for(int v : e2[u])if(v != pre)work(v, u);
    if(u <= n){if(!pre)op(u);return;}//特判一下最后一个环
    int pos = 0;//找与其他环相邻的那个点p。
    for(int j = 0;j < e2[u].size();j++)if(e2[u][j] == pre)pos = j;

    vector<int> a;a.clear();//以p为开始将整个环展开
    for(int j = 0;j < e2[u].size();j++){a.push_back(e2[u][(j + pos) % e2[u].size()]);}
    
    int m = a.size() - 1;
    for(int j = 1;j <= m;j++)op(a[j] + ((j & 1) == 0) * n);
    op(a[m] + (m & 1) * n);op(a[1] + n);
}
void main(){
    n = read(); m = read();int u, v;cnt = n;
    for(int i = 1;i <= m;i++){
        u = read(), v = read();
        deg[u] ^= 1;deg[v] ^= 1;
        edg[u].push_back(v);edg[v].push_back(u);
    }
    for(int i = 1;i <= n;i++)if(deg[i])del(i);
    for(int i = 1;i <= n;i++)
        if(!dl[i]){
            vector<int> tmp;tmp.clear();
            for(int v : edg[i])if(!dl[v]){tmp.push_back(v);}
            edg[i] = tmp;
        }
        else edg[i].clear();
    ans.push_back(0);
    for(int i = 1;i <= n;i++)if(!dfn[i])dfs(i);
    for(int i = 1;i <= n;i++)if(!vis[i])work(i,0);
    printf("0 %d\n",(int)ans.size());
    for(int i : ans){
        if(i)printf("1 %d\n",i);
        else puts("2");
    }
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
/*
7 7
1 2
1 3
2 3
2 4
2 5
3 6
3 7
*/