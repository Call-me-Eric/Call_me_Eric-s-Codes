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
const int maxn = 1e6 + 10, mod = 998244353;
int n, m, L ,R, K;
int qpow(int x,int a){
    int res = 1;
    while(a){
        if(a & 1)res = res * x % mod;
        x = x * x % mod;a >>= 1;
    }
    return res;
}
namespace Subtask1{
    int fa[maxn], cnt;
    int getf(int x){return fa[x] == x ? x : fa[x] = getf(fa[x]);}
    int merg(int u,int v){
        int fu = getf(u), fv = getf(v);
        if(fu == fv)return 0;
        fa[fu] = fv;return 1;
    }
    void main(){
        for(int i = 0;i < n + m;i++)fa[i] = i,cnt++;
        for(int i = 1;i <= K;i++){
            int u = read(), v = read();
            cnt -= merg(u, v);
        }
        int ans = 0;
        for(int i = 1;i <= n + m - 1 && i <= R;i++){
            int u = (i - 1) % n, v = (i - 1) % m;
            cnt -= merg(u,v + n);
            if(L <= i && i <= R)ans = (ans + cnt) % mod;
            if(cnt == 1){
                ans = (ans + (R - i)) % mod;
                break;
            }
        }
        if(cnt != 1 && R > (n + m - 1))
            ans = (ans + (R - (n + m - 1)) * cnt % mod) % mod;
        printf("%lld\n",ans % mod);
    }
};
namespace Subtask2{
    void main(){
        int ans = max(0ll,R - (n + m - 1));
        if(R >= n + m - 1)R = n + m - 1;
        R = (n + m - 1) - R + 1;L = (n + m - 1) - L + 1;
        ans = (ans + (R + L) % mod * ((L - R + 1) % mod) % mod * qpow(2,mod - 2) % mod) % mod;
        printf("%lld\n",ans % mod);
    }
};
void main(){
    n = read(); m = read(); L = read(); R = read(); K = read();
    if(n <= 2e5 && m <= 2e5 && K <= 3e5)Subtask1::main();
    else if(K == 0)Subtask2::main();
    return;
}
};
bool edmemory;
signed main(){
    freopen("proton.in","r",stdin);
    freopen("proton.out","w",stdout);
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}
/*
3 3 1 4 2
0 1
1 2
*/