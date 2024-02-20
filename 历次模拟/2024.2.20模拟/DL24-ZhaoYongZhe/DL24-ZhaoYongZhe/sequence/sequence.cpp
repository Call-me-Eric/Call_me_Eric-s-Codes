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
const int maxn = 5e5 + 10, mod = 998244353;
int n;
int buc[maxn];
int qpow(int x,int a){
    int res = 1;
    while(a){
        if(a & 1)res = res * x % mod;
        x = x * x % mod;a >>= 1;
    }
    return res;
}
namespace Subtask1{//a_i\le 2
    void solve(){
        for(int k = 0;k <= n - 1;k++){
            if(buc[1] < k || buc[2] < k){putchar('0');putchar(' ');continue;}
            int res1 = buc[1] - k, res2 = buc[2] - k;
            printf("%lld ",qpow(k + 1,res1) * qpow(k + 1,res2) % mod);
        }
        puts("");
    }
};
namespace Subtask2{
    int ans[maxn];
    int b[maxn];
    void dfs(int u,int cnt){
        if(u == n + 1){ans[cnt]++;return;}
        for(int i = 1;i <= n;i++){
            if(buc[i] > 0){
                b[u] = i;buc[i]--;
                dfs(u + 1,(b[u] > b[u - 1]) + cnt);
                b[u] = 0;buc[i]++;
            }
        }
    }
    void solve(){dfs(1, 0);for(int i = 1;i <= n;i++)printf("%lld ",ans[i]);puts("");}
};
void main(){
    n = read(); for(int i = 1;i <= n;i++)buc[read()]++;
    if(buc[1] + buc[2] == n){Subtask1::solve();}
    else if(n <= 10){Subtask2::solve();}
    return;
}
};
bool edmemory;
signed main(){
    freopen("sequence.in","r",stdin);
    freopen("sequence.out","w",stdout);
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}