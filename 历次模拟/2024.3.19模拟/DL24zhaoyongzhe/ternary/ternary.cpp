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
const int maxn = 5e3 + 10, maxm = 1e6 + 10, mod = 1e9 + 7;
int qpow(int x,int a){
    int res = 1;
    while(a){
        if(a & 1){res = res * x % mod;}
        x = x * x % mod;a >>= 1;
    }
    return res;
}
int n, m;
pair<pair<int,int>, int> limit[maxm];
int ans;
int val[maxn];
bool buc[5];
bool check(){
    for(int i = 1;i <= m;i++){
        buc[0] = buc[1] = buc[2] = 0;
        for(int j = limit[i].first.first;j <= limit[i].first.second;j++){
            buc[val[j]] = 1;
        }
        int sum = buc[0] + buc[1] + buc[2];
        if(sum != limit[i].second)return false;
    }
    return true;
}
void dfs(int u){
    if(u == n + 1){
        if(check())ans++;
        return;
    }
    val[u] = 0;dfs(u + 1);
    val[u] = 1;dfs(u + 1);
    val[u] = 2;dfs(u + 1);
}
void solve(){
    n = read(); m = read();
    for(int i = 1;i <= m;i++){
        int l = read(), r = read(), x = read();
        limit[i] = make_pair(make_pair(l,r),x);
    }
    if(m == 1){
        int res[10] = {1}, tmp[10] = {0};
        for(int i = 1;i <= limit[1].first.second - limit[1].first.first + 1;i++){
            for(int i = 0;i < (1 << 3);i++){tmp[i] = res[i];res[i] = 0;}
            for(int i = 0;i < (1 << 3);i++){
                for(int j = 0;j < 3;j++){
                    res[i | (1 << j)] = (res[i | (1 << j)] + tmp[i]) % mod;
                }
            }
        }
        ans = qpow(3,limit[1].first.first - 1) * qpow(3,n - limit[1].first.second) % mod;
        if(limit[1].second == 1){ans = ans * (res[1] + res[2] + res[4]) % mod;}
        if(limit[1].second == 2){ans = ans * (res[3] + res[5] + res[6]) % mod;}
        if(limit[1].second == 3){ans = ans * (res[7]) % mod;}
        printf("%lld\n",ans);
        return;
    }
    ans = 0;dfs(1);printf("%lld\n",ans);
}
void main(){int T = read();while(T--)solve();return;}
};
bool edmemory;
signed main(){
    freopen("ternary.in","r",stdin);
    freopen("ternary.out","w",stdout);
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}