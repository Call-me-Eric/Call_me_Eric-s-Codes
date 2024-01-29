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
const int maxn = 5e5 + 10, maxm = 2e6 + 10;
vector<int> edg[maxn];
int n, m;
int dfn[maxn], low[maxn], idx;
stack<int> stk;
vector<vector<int> > ans;
void dfs(int u,int f){
    dfn[u] = low[u] = ++idx;
    int son = 0;stk.push(u);
    for(int v : edg[u]){
        if(!dfn[v]){
            ++son;dfs(v ,u);
            low[u] = min(low[u],low[v]);
            if(low[v] >= dfn[u]){
                vector<int> tmp;tmp.clear();
                while(stk.top() != v){tmp.push_back(stk.top());stk.pop();}
                tmp.push_back(v);stk.pop(); tmp.push_back(u);
                ans.push_back(tmp);
            }
        }else if(v != f){low[u] = min(low[u],dfn[v]);}
    }
    if(f == 0 && son == 0){ans.push_back(vector<int>(1,u));}
}
void main(){
    n = read(); m = read();int u, v;
    for(int i = 1;i <= m;i++){
        u = read(); v = read();
        edg[u].push_back(v);edg[v].push_back(u);
    }
    for(int i = 1;i <= n;i++)
        if(!dfn[i]){while(!stk.empty())stk.pop();dfs(i, 0);}
    printf("%d\n",ans.size());
    for(auto vec : ans){
        printf("%d ",vec.size());
        for(int i : vec)printf("%d ",i);
        puts("");
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