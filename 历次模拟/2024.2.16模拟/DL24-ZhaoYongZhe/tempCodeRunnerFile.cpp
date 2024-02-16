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
const int maxn = 1e6 + 10, mod = 998244353;
int n, a[maxn];
void solve(){
    n = read(); int x = 0, y = 0;
    for(int i = 1;i <= n;i++)a[i] = read();
    int ans = 1;
    for(int i = 1;i <= n;i++){
        if(a[i] < a[y]){puts("0");return;}
        else if(a[i - 1] > a[i]){
            if(a[i] >= a[x])for(;a[y] <= a[i];y++)ans = (ans * 2ll) % mod;
            x = i - 1;y = i;
        }
        else if(a[i] < a[x]){y = i;}
    }
    for(;y < n;y++)ans = (ans * 2ll) % mod;
    printf("%d\n",ans);
    return;
}
void main(){int T = read();while(T--)solve();}
};
bool edmemory;
signed main(){
    freopen("color.in","r",stdin);
    freopen("color.out","w",stdout);
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}