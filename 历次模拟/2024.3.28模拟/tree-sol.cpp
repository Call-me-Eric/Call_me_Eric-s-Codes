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
typedef unsigned long long ull;
default_random_engine rng;
uniform_int_distribution<ull> randint(0, ULONG_MAX);
const int maxn = 1.2e6 + 10, mod = 998244353;
int n, fa[maxn];
int getf(int x){return fa[x] == x ? x : fa[x] = getf(fa[x]);}
vector<int> edg[maxn];
int siz[maxn], root;
bool leaf[maxn];
void getcenter(int u){
    siz[u] = 1;int son = 0;
    for(int v : edg[u])if(!siz[v]){getcenter(v);siz[u] += siz[v];son = max(son,siz[v]);}
    son = max(son,n - siz[u]);if(son <= n / 2)root = u;
}
int pw[maxn];
ull hsh[maxn], sum[maxn];
void ins(int x,int y){
    sum[x] ^= siz[x] * hsh[siz[x]];
    siz[x] += siz[y];sum[x] += sum[y];
    sum[x] ^= siz[x] * hsh[siz[x]];
}
void del(int x,int y){
    sum[x] ^= siz[x] * hsh[siz[x]];
    siz[x] -= siz[y];sum[x] -= sum[y];
    sum[x] ^= siz[x] * hsh[siz[x]];
}
void dfs0(int u,int f){
    siz[u] = 1;sum[u] = 0;leaf[u] = 1;
    for(int v : edg[u])if(v != f){dfs0(v, u);leaf[u] = false;ins(u, v);}
}
ull sumR;int ans;
void dfs1(int u,int f){
    if(f){del(f, u);ins(u, f);}
    if(sum[u] == sumR && ((u > n) ^ (root > n)))ans++;
    for(int v : edg[u])if(v != f)dfs1(v, u);
    if(f){del(u,f);ins(f, u);}
}
int calc(int u,int f){
    int res = 1;map<ull,int> mp;
    for(int v : edg[u])if(v != f){
        res = 1ll * res * calc(v, u) % mod;
        if(!leaf[v]){mp[sum[v]]++;}
    }
    for(auto i : mp)res = 1ll * res * pw[i.second] % mod;
    return res;
}
void solve(){
    n = read();pw[0] = 1;ans = 0;
    for(int i = 1;i <= n * 2;i++){
        edg[i].clear(); fa[i] = i; siz[i] = leaf[i] = sum[i] = 0;
        hsh[i] = randint(rng);pw[i] = 1ll * pw[i - 1] * i % mod;
    }
    for(int i = 1;i <= n;i++){
        for(int j = read();j;j--){
            int x = read();
            edg[i + n].push_back(x);edg[x].push_back(i + n);
            fa[getf(x)] = getf(i + n);
        }
    }
    if(n == 1){puts("1");return;}
    int cnt = 0;for(int i = 1;i <= n * 2;i++)cnt += getf(i) == i;
    if(cnt != 2){puts("0");return;}
    getcenter(1);dfs0(root,0);sumR = sum[root];
    for(int i = 1;i <= n * 2;i++){
        if(!siz[i]){dfs0(i,0);dfs1(i,0);break;}
    }
    ans = 1ll * ans * calc(root,0) % mod;
    printf("%d\n",ans);
    return;
}
void main(){int T = read();while(T--)solve();return;}
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
2
5
1 2
2 1 3
2 2 4
2 3 5
1 4
8
3 2 5 6
1 1
1 1
3 3 7 8
2 2 4
2 1 3
1 4
1 4
*/