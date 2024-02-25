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
const int maxn = 2e6 + 10, mod = 998244353;
char ch[maxn];
int n;
int qpow(int x,int a){
    int res = 1;
    while(a){
        if(a & 1){res = res * x % mod;}
        x = x * x % mod;a >>= 1;
    }
    return res;
}
void main(){
    scanf("%s",ch + 1);n = strlen(ch + 1);
    int p = 1, pa = 0, pb = 0, pba = 0, pw = 1;
    int ans = 0, inv2 = qpow(2,mod - 2);
    for(int i = 1;i <= n;i++){
        int t = 0, ta = 0, tb = 0,tba = 0;
        if(ch[i] == '+'){
            ans = (ans + pa) % mod;
            t = p;
            tb = pb + pba + pa;
            ta = 0;tba = 0;
        }
        if(ch[i] == '-'){
            t = 0;
            ta = pa + p;
            tba = pb + pba;
            tb = 0;
        }
        if(ch[i] == '?'){
            t = inv2 * p % mod;
            tb = inv2 * (pb + pba + pa) % mod;
            ta = inv2 * (pa + p);
            tba = inv2 * (pb + pba);
            pw = pw * 2 % mod;
        }
        p = t % mod;pb = tb % mod;pa = ta % mod;pba = tba % mod;
    }
    printf("%lld\n",ans * pw % mod);
    return;
}
};
bool edmemory;
signed main(){
    freopen("physics.in","r",stdin);
    freopen("physics.out","w",stdout);
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}