#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch  = getchar();
    while(ch  < '0' || ch > '9'){if(ch == '-') f = -1;ch =  getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
typedef long long ll;
const int maxn = 5e3 + 10;
const ll mod = 998244353;
int testcase, n;
vector<int> edg[maxn];
ll qpow(ll x,int a){
    ll res = 1;
    while(a){
        if(a & 1)res = res * x % mod;
        x = x * x % mod;a >>= 1;
    }
    return res;
}
namespace subtask2{
void solve2(){
    ll ans = ((ll)n + qpow(2,n - 1) - 1 - 1 - 1 + mod) % mod * qpow(qpow(2,n),mod - 2) % mod;
    printf("%lld\n",ans);return;
}
};
namespace subtask1{
ll ans;
int col[maxn],dep[maxn];
vector<int> vec[maxn];
void dfs1(int u,int f){
    dep[u] = dep[f] + 1;vec[dep[u]].push_back(u);
    for(int v : edg[u])if(v != f)dfs1(v, u);
}
int check(){
    int ans = -1,cnt = 0;
    for(int rt = 1;rt <= n;rt++){
        if(!col[rt])continue;else cnt++;
        for(int i = 1;i <= n;i++){dep[i] = 0;vec[i].clear();}
        dfs1(rt,rt);int j = 0;
        for(j = 1;j <= n;j++){
            bool flag = true;
            for(int v : vec[j])
                if(!col[v]){flag = false;break;}
            if(!flag)break;
        }
        ans = max(ans,j - 2);
    }
    if(cnt == n)return n;
    if(cnt == 0)return -1;
    return ans;
}
void dfs(int u){
    if(u == n + 1){
        ans = (ans + check()) % mod;
        return;
    }
    col[u] = 0;dfs(u + 1);
    col[u] = 1;dfs(u + 1);
}
void solve1(){
    int u, v;
    for(int i = 1;i < n;i++){
        u = read(); v = read();
        edg[u].push_back(v);
        edg[v].push_back(u);
    }
    dfs(1);
    printf("%lld\n",ans * qpow(qpow(2,n),mod - 2) % mod);
}
};
signed main(){
    freopen("summer.in","r",stdin);
    freopen("summer.out","w",stdout);
    testcase = read(); n = read();
    if(testcase == 1){subtask1::solve1();return 0;}
    if(testcase == 2){subtask2::solve2();return 0;}
    return 0;
}