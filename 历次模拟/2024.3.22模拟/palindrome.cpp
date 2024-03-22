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
const int maxn = 3e6 + 10, mod = 998244353;
int qpow(int x,int a){
    int res = 1;
    while(a){
        if(a & 1)res = res * x % mod;
        x = x * x % mod;a >>= 1;
    }
    return res;
}
int n, a[maxn], c, ans, b[maxn];
bool check(){
    for(int i = 1;i <= n;i++){
        for(int j = i + 1;j <= n;j++){
            bool flag1 = true, flag2 = true;int m = j - i;
            for(int k = 0;k <= j - i;k++){
                if(a[i + k] != a[i + (m - k)])flag1 = false;
                if(b[i + k] != b[i + (m - k)])flag2 = false;
                if(!flag1 && !flag2)break;
            }
            if(flag1 != flag2)return false;
        }
    }
    return true;
}
void dfs(int u,int col){
    if(u == n + 1){
        if(check()){
            // for(int i = 1;i <= n;i++)printf("%lld ",b[i]);puts("");
            int res = 1;
            for(int i = 0;i < col;i++)res = res * (c - i) % mod;
            ans = (ans + res) % mod;
        }
        return;
    }
    for(int i = 1;i <= col + 1;i++){
        b[u] = i;dfs(u + 1,max(col,i));
    }
}
void solve(){
    n = read(); c = read();
    for(int i = 1;i <= n;i++)a[i] = read();
    if(c == 2){puts("2");return;}
    ans = 0;dfs(1,0);
    printf("%lld\n",ans);
}
void main(){int T = read();while(T--)solve();return;}
};
bool edmemory;
signed main(){
    freopen("palindrome.in","r",stdin);
    freopen("palindrome.out","w",stdout);
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}