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
const int maxn = 300 + 10, maxm = 2e3 + 10,INF = 0x3f3f3f3f;
int n, m, k;
typedef pair<int,int> pii;
pii edg[maxm];
vector<pii> e[maxn];
map<pii,int> mp;
int deg[maxn];
int siz[maxn], st[maxn];
int ans[maxn];

void dfs(int u,int v,int posl,int posr){
    for(auto &i : e[v]){
        if(i.first == posl){
            i.first = posr;
            dfs(u,i.second,posr,posl);
        }
    }
    for(auto &i : e[v])if(i.second == u)i.first = posl;
    return;
}
void main(){
    n = read(); m = read(); k = read();
    for(int i = 1;i <= n;i++)read();
    for(int i = 1;i <= m;i++){
        int u = read(), v = read();
        if(u > v)swap(u, v);
        edg[i] = make_pair(u, v + n);
        deg[u]++;deg[v + n]++;
    }
    n <<= 1;st[0] = 1;
    for(int i = 1;i <= n;i++){siz[i] = (deg[i] + k - 1) / k;st[i] = siz[i - 1] + st[i - 1];deg[i] = 0;}
    for(int i = 1;i <= m;i++){
        int u = edg[i].first, v = edg[i].second;
        e[st[u]].push_back(make_pair(INF,st[v]));
        e[st[v]].push_back(make_pair(INF,st[u]));
        edg[i] = make_pair(st[u], st[v]);
        mp[edg[i]] = i;
        deg[u]++;deg[v]++;
        if(deg[u] == k){++st[u];deg[u] = 0;}
        if(deg[v] == k){++st[v];deg[v] = 0;}
    }
    for(int i = 1;i <= m;i++){
        int u = edg[i].first, v = edg[i].second;
        int posl = 0, posr = 0;
        sort(e[u].begin(),e[u].end());sort(e[v].begin(),e[v].end());
        for(int i = 0;i < e[u].size();i++)
            if(e[u][i].first != i + 1){posl = i + 1;break;}
        for(int i = 0;i < e[v].size();i++)
            if(e[v][i].first != i + 1){posr = i + 1;break;}
        for(auto &i : e[u]){if(i.second == v){i.first = posl;}}
        dfs(u, v,posl,posr);
    }
    for(int i = 1;i <= st[n];i++)
        for(auto w : e[i]) if(i < w.second)
            ans[mp[make_pair(i,w.second)]] = w.first;
    for(int i = 1;i <= m;i++)printf("%d\n",ans[i]);
    return;
}
};
bool edmemory;
signed main(){
    auto starttime = clock();
    Call_me_Eric::main();
    auto endtime = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << "Mib cost.\n";
    cerr << 1.0 * (endtime - starttime) / CLOCKS_PER_SEC * 1000.0 << " ms cost.\n";
    return 0;
}