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
const int maxn = 3e5 + 10, mod = 998244353;
int qpow(int x,int a){
    int res = 1;
    while(a){
        if(a & 1)res = res * x % mod;
        x = x * x % mod;a >>= 1;
    }
    return res;
}
int n, m;
vector<pair<int,int> > edg[maxn], e[maxn];
int f[maxn], fa[21][maxn], dep[maxn];
int dfn[maxn], idx, siz[maxn];
int deg[maxn];
void dfs(int u,int fat){
    dfn[u] = ++idx;siz[u] = 1;dep[u] = dep[fat] + 1;
    fa[0][u] = fat;for(int i = 1;i <= 20;i++)fa[i][u] = fa[i - 1][fa[i - 1][u]];
    for(auto i : edg[u]){
        int v = i.first, w = i.second;
        if(v != fat && !dfn[v]){
            f[v] = f[u] * w % mod;
            dfs(v, u);siz[u] += siz[v];
        }
    }
    // printf("u = %lld,dfn = %lld,siz = %lld,f[u] = %lld\n",u,dfn[u],siz[u],f[u]);
}
int LCA(int u,int v){
    if(dep[u] < dep[v])swap(u, v);
    for(int i = 20;i + 1;i--)
        if(dep[fa[i][u]] >= dep[v])
            u = fa[i][u];
    if(u == v)return u;
    for(int i = 20;i + 1;i--)
        if(fa[i][u] != fa[i][v])
            u = fa[i][u],v = fa[i][v];
    return fa[0][u];
}
int x;
int dfs1(int u){
    if(x == u)return 0;int ans = 1;
    for(auto i : edg[u]){
        // printf("%lld -> %lld,%lld\n",u,i.first,i.second);
        ans = (ans * ((1 - i.second + mod) % mod + i.second * dfs1(i.first) % mod) % mod) % mod;
    }
    // printf("x = %lld,ans =  %lld\n",u,ans);
    return ans;
}
void main(){
    n = read(); m = read();
    for(int i = 1;i <= m;i++){
        int u, v, p, q;
        u = read(); v = read();p = read(); q = read();
        int x = p * qpow(q,mod - 2) % mod;
        edg[u].push_back(make_pair(v,x));
    }
    f[1] = 1;dfs(1, 0);
    for(int u = 1;u <= n;u++)
        for(auto i : edg[u]){
            int v = i.first, w = i.second;
            if(dfn[u] < dfn[v] || dfn[u] >= dfn[v] + siz[v]){e[v].push_back(make_pair(u, w));}
        }
    // for(int u = 1;u <= n;u++){
    //     for(auto i : e[u]){
    //         printf("u = %lld, v = %lld, w = %lld\n",u,i.first,i.second);
    //     }
    // }
    puts("1");
    auto cmp = [](int x,int y){return dfn[x] < dfn[y];};
    for(int i = 1;i <= n;i++)edg[i].clear();
    for(int u = 2;u <= n;u++){
        // printf("e[%lld].siz = %lld\n",u,e[u].size());
        vector<int> vec;vec.push_back(1);for(auto i : e[u]){vec.push_back(i.first);}
        sort(vec.begin(),vec.end(),cmp);vec.erase(unique(vec.begin(),vec.end()),vec.end());
        for(int i = 1,s = vec.size();i < s;i++)vec.push_back(LCA(vec[i],vec[i - 1]));
        sort(vec.begin(),vec.end(),cmp);vec.erase(unique(vec.begin(),vec.end()),vec.end());
        for(int i = 1;i < vec.size();i++){
            int l = LCA(vec[i],vec[i - 1]);
            edg[l].push_back(make_pair(vec[i],f[vec[i]] * qpow(f[l],mod - 2) % mod));
        }
        for(auto i : e[u]){edg[i.first].push_back(make_pair(u,i.second));}
        x = u;printf("%lld\n",(1 - dfs1(1) + mod) % mod);
        for(int i = 0;i < vec.size();i++)edg[vec[i]].clear();
    }
    // printf("%lld,%lld\n",qpow(8,mod - 2) * 5 % mod,qpow(8,mod - 2) * 3 % mod);
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
4 4
1 2 1 2
2 3 1 2
2 4 1 2
4 3 1 1

*/