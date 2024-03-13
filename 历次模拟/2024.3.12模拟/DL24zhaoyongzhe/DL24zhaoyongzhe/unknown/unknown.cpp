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
const int maxn = 2e3 + 10;
int n;
int val[maxn];
vector<int> edg[maxn];
int deg[maxn];
namespace Subtask2{
int ans[maxn], p[maxn], rev[maxn];
bool con[maxn];
void main(){
    int u = -1;
    for(int i = 1;i <= n;i++)
        if(deg[i] == 1){u = i;break;}
    p[1] = u;int cnt = 1;
    int v = -1;
    while(cnt <= n){
        for(int i : edg[u])
            if(i != v){v = i;break;}
        swap(u, v);
        p[++cnt] = u;
    }
    for(int i = 1;i <= n;i++){
        rev[p[i]] = i;con[i] = 1;
    }
}
};
pair<int,int> ed[maxn];
int p[maxn];
int ans[maxn];
int tmp[maxn];
void solve(){
    n = read();
    for(int i = 1;i <= n;i++){edg[i].clear();deg[i] = 0;val[i] = read();ans[i] = n;}
    bool Sub2 = true;
    for(int i = 1;i < n;i++){
        int u = read(), v = read();
        edg[u].push_back(v);edg[v].push_back(u);
        ed[i] = make_pair(u, v);
        deg[u]++;deg[v]++;
        if(deg[u] > 2 || deg[v] > 2)Sub2 = false;
    }
    for(int i = 1;i < n;i++){p[i] = i;}
    do{
        for(int i = 1;i <= n;i++)tmp[i] = val[i];
        for(int i = 1;i < n;i++)swap(tmp[ed[i].first],tmp[ed[i].second]);
        bool flag = true;
        for(int i = 1;i <= n;i++){
            if(ans[i] != tmp[i]){flag = tmp[i] < ans[i];break;}
        }
        if(flag){for(int i = 1;i <= n;i++)ans[i] = tmp[i];}
    }while(next_permutation(p + 1,p + n));
    for(int i = 1;i <= n;i++)printf("%d ",tmp[i]);puts("");
    // if(Sub2){Subtask2::main();return;}
}
void main(){int T = read();while(T--)solve();return;}
};
bool edmemory;
signed main(){
    freopen("unknown.in","r",stdin);
    freopen("unknown.out","w",stdout);
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}
/*
5
3 4 2 1 5
1 2
2 3
3 4
4 5
*/