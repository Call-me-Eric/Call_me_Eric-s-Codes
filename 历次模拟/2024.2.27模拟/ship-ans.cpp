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
const int maxn = 3e5 + 10;
int n, m, K;
vector<int> edg[maxn];
int a[maxn];
int tot, col[maxn], dfn[maxn], low[maxn], idx;
vector<int> scc[maxn];stack<int> stk;
bool book[maxn];
void dfs(int u){
    dfn[u] = low[u] = ++idx;stk.push(u);book[u] = 1;
    for(int v : edg[u]){
        if(!dfn[v]){dfs(v);low[u] = min(low[u],low[v]);}
        else if(book[v]){low[u] = min(low[u],dfn[v]);}
    }
    if(low[u] == dfn[u]){
        tot++;int v = stk.top();
        do{
            book[v = stk.top()] = false;stk.pop();
            scc[col[v] = tot].push_back(v);
        }while(v != u);
    }
}
void main(){
    n = read(); m = read(); K = read();
    int u, v, w;
    for(int i = 1;i <= m;i++){
        u = read(); v = read(); w = (K - read() % K) % K;
        edg[u].push_back(v);a[u] += w;a[v] -= w;
    }
    for(int i = 1;i <= n;i++){if(!dfn[i])dfs(i);}
    priority_queue<int> que;int ans = 0,cnt = 0;
    for(int i = tot;i;i--){
        vector<int> vec, tmp;
        for(int j : scc[i]){int r = (a[j] % K + K) % K;vec.push_back(r);cnt += (a[j] - r) / K;}
        sort(vec.begin(),vec.end(),greater<int>());
        while(!que.empty() && cnt > 0){ans += (K - que.top());que.pop();cnt--;}
        for(int j : vec){
            if(cnt < 0){cnt++;tmp.push_back(K - j);}
            else if(!que.empty() && que.top() + j >= K){ans += (K - que.top());que.pop();tmp.push_back(K - j);}
            else ans += j;
        }
        for(int j : tmp){que.push(j);}
        if(cnt > 0){ans += K * cnt;cnt = 0;}
    }
    while(!que.empty()){ans += que.top();que.pop();}
    printf("%lld\n",(ans + K * abs(cnt)) / 2);
    return;
}
};
bool edmemory;
signed main(){
    freopen("ship.in","r",stdin);
    freopen("ship.out","w",stdout);
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}
/*
5 6 3
1 4 1
2 5 2
3 5 0
4 3 2
5 4 1
5 1 2
*/