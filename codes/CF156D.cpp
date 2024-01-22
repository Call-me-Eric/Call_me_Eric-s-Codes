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
const int maxn = 1e5 + 10;
int n, m, mod;
int qpow(int x,int a){
    int res = 1;
    while(a){
        if(a & 1)res = (1ll * res * x) % mod;
        x = 1ll * x * x % mod;a >>= 1;
    }
    return res;
}

int fa[maxn], siz[maxn];
int getf(int x){return fa[x] == x ? x : fa[x] = getf(fa[x]);}

void main(){
    n = read(); m = read(); mod = read();
    if(n == 1){printf("%lld\n",1ll % mod);return;}
    for(int i = 1;i <= n;i++)fa[i] = i;
    for(int i = 1;i <= m;i++){
        int u = read(), v = read();
        if(getf(u) != getf(v))fa[getf(u)] = getf(v);
    }
    for(int i = 1;i <= n;i++){siz[getf(i)]++;}
    int ans = 1, cnt = 0;
    for(int i = 1;i <= n;i++){if(siz[i]){ans = (ans * siz[i]) % mod;cnt++;}}
    if(cnt == 1){printf("%lld\n",1ll % mod);return;}
    printf("%lld\n",ans * qpow(n,cnt - 2) % mod);
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