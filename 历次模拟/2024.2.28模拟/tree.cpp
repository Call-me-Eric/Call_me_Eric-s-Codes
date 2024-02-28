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
const int maxn = 2e5 + 10;
int n, m;
vector<int> edg[maxn];
int dep[maxn],fa[21][maxn];
void dfs(int u,int f){
    fa[0][u] = f;dep[u] = dep[f] + 1;
    for(int i = 1;i <= 20;i++)fa[i][u] = fa[i - 1][fa[i - 1][u]];
    for(int v : edg[u])if(v != f)dfs(v, u);
}
int LCA(int u,int v){
    if(dep[u] <= dep[v])swap(u, v);
    for(int i = 20;i + 1;i--)
        if(dep[fa[i][u]] >= dep[v])
            u = fa[i][u];
    if(u == v)return u;
    for(int i = 20;i + 1;i--)
        if(fa[i][u] != fa[i][v])
            u = fa[i][u], v = fa[i][v];
    return fa[0][u];
}
namespace Subtask1{
    int ans = 0;
    int col[maxn];
    int lca[100][100];
    vector<int> vec[100];
    int check(){
        int res = 0;
        for(int i = 1;i <= m;i++)vec[i].clear();
        for(int i = 1;i <= n;i++)vec[col[i]].push_back(i);
        for(int i = 1;i <= m;i++){
            if(!vec[i].size())continue;
            for(int j = vec[i].size() - 1;j;j--){
                vec[i].push_back(lca[vec[i][j]][vec[i][j - 1]]);
            }
            sort(vec[i].begin(),vec[i].end());
            vec[i].erase(unique(vec[i].begin(),vec[i].end()),vec[i].end());
            res += vec[i].size();
        }
        return res;
    }
    void getval(int u){
        if(u == n + 1){
            ans = max(ans,check());
            return;
        }
        for(int i = 1;i <= m;i++){
            col[u] = i;getval(u + 1);
        }
        col[u] = 0;
    }
    void solve(){
        for(int i = 1;i <= n;i++)
            for(int j = 1;j <= n;j++)
                lca[i][j] = LCA(i,j);
        getval(1); printf("%d\n",ans);return;
    }
};
namespace Subtask2{
    void solve(){printf("%d\n",n);return;}
};
namespace Subtask3{
    void solve(){
        m--;int ans = 0;
        for(int i = 2;i <= n;i += 2){
            if(m == 0){ans += (n - i + 1) + 1;break;}
            ans += 3;m--;
        }
        printf("%d\n",ans);
    }
};
void main(){
    n = read();m = read();int u, v;bool Sub3 = 1, Sub2 = 1;
    for(int i = 1;i < n;i++){
        u = read(); v = read();
        edg[u].push_back(v);edg[v].push_back(u);
        if(u != 1)Sub3 = false; if(u + 1 != v)Sub2 = false;
    }
    dfs(1, 0);
    if(n <= 5 && m <= 5){Subtask1::solve();return;}
    if(Sub2){Subtask2::solve();return;}
    if(Sub3){Subtask3::solve();return;}
    return;
}
};
bool edmemory;
signed main(){
    freopen("tree.in","r",stdin);
    freopen("tree.out","w",stdout);
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}
/*
5 3
1 2
1 3
1 4
4 5

*/