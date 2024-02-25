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
int n;
vector<int> edg[maxn];
int siz[maxn];bool flag = true;
vector<int> center;
void dfs1(int u,int f){
    siz[u] = 1;int mx = 0;
    for(int v : edg[u]){
        if(v != f){
            dfs1(v, u);
            siz[u] += siz[v];
            mx = max(mx,siz[v]);
        }
    }
    mx = max(mx,n - siz[u]);
    if(flag && mx <= n / 2)center.push_back(u);
}
typedef unsigned long long ull;
const ull mask = std::chrono::steady_clock::now().time_since_epoch().count();
ull prime[maxn];int tot;bool book[maxn];
ull shift(ull x){
    x ^= mask;
    x ^= x << 13;
    x ^= x >> 6;
    x ^= x << 9;
    x ^= mask;
    return x;
}
ull hsh[maxn];
void dfs(int u,int f,int rt){
    hsh[u] = 1;
    for(int v : edg[u]){
        if(v != f && v != rt){
            dfs(v, u,rt);
            hsh[u] += shift(hsh[v]);
        }
    }
}
vector<int> vec;
int sz, si[maxn];
void dfs2(int u,int f){
    si[u] = 1;int mx = 0;
    for(int v : edg[u]){
        if(v != f){
            dfs2(v, u);
            si[u] += si[v];
            mx = max(mx,si[v]);
        }
    }
    mx = max(mx,sz - si[u]);
    if(mx <= sz / 2)vec.push_back(u);
}
int solve(int u){
    ull hhh = 0;bool val = 0;
    for(int v : edg[u]){
        sz = siz[v];vec.clear();
        dfs2(v, u);
        ull x = 0;
        for(int j : vec){
            dfs(j,0,u);
            x = max(x,hsh[j]);
        }
        if(!val){hhh = x;val = 1;}
        else if(hhh != x){return -1;}
    }
    return edg[u].size();
}
void main(){
    n = read(); int u, v;
    for(int i = 2;i < 1e5;i++){
        if(!book[i])prime[++tot] = i;
        for(int j = 1;j <= tot && i * prime[j] < 1e5;i++){
            book[i * prime[j]] = 1;
            if(i % prime[j] == 0)break;
        }
    }
    for(int i = 1;i < n;i++){
        u = read(); v = read();
        edg[u].push_back(v);edg[v].push_back(u);
    }
    dfs1(1, 0);int ans = -1;flag = false;
    for(int cen : center){dfs1(cen,0);ans = max(ans,solve(cen));}
    printf("%d\n",ans);
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