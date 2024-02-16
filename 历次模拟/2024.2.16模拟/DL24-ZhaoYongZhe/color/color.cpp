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
const int maxn = 1e6 + 5, mod = 998244353;
int n;
vector<int> a, c;
int qpow(int x,int a1){
    int res = 1;
    while(a1){
        if(a1 & 1){res = 1ll * res * x % mod;}
        x = 1ll * x * x % mod;a1 >>= 1;
    }
    return res;
}
inline int lowbit(int x){return x & (-x);}
int qry(int x){int s = 0;for(;x;x -= lowbit(x))s = max(s,c[x]);return s;}
void upd(int x,int add){for(;x <= n;x += lowbit(x)){c[x] = max(c[x],add);}}
void solve(){
    n = read();a.resize(n + 10);c.resize(n + 10);
    for(int i = 1;i <= n;i++){c[i] = a[i] = read();}
    sort(c.begin(),c.end());c.erase(unique(c.begin(),c.end()),c.end());
    for(int i = 1;i <= n;i++){a[i] = lower_bound(c.begin(),c.end(),a[i]) - c.begin() + 1;}
    c.resize(n + 10);
    for(int i = 1;i <= n;i++)c[i] = 0;
    for(int i = n;i;i--){
        int f = qry(a[i] - 1) + 1;
        if(f >= 3){puts("0");return;}
        upd(a[i],f);
    }
    c[n + 1] = n + 1;a[n + 1] = 0x3f3f3f3f;
    for(int i = n;i;i--){
        c[i] = a[c[i + 1]] <= a[i] ? c[i + 1] : i;
    }
    int cnt = 0;
    for(int i = 1, r = i;i <= n;i = r + 1){
        r = a[c[i + 1]] >= a[i] ? i : c[i + 1];int p = i, mx = a[i];
        while(p < r){
            p++;mx = max(mx,a[p]);
            if(a[c[r + 1]] < mx){r = c[r + 1];}
        }
        cnt++;
        // printf("[%d,%d],cnt = %d\n",i,r,cnt);
    }
    printf("%d\n",qpow(2,cnt));
}
void main(){int T = read();while(T--)solve();return;}
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