#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10, mod = 1e9 + 7;
int n, m, k;
pair<int,int> edg[maxn];
int qpow(int x,int a){
    int res = 1;
    while(a){
        if(a & 1)res = res * x % mod;
        x = x * x % mod;a >>= 1;
    }
    return res;
}
int pw[maxn], invpw[maxn];
int C(int n,int m){return pw[n] * invpw[m] % mod * invpw[n - m] % mod;}

signed main(){
    freopen("graph.in","r",stdin);
    freopen("graph.out","w",stdout);
    n = read(); m = read(); k = read();bool state1 = true, state2 = true;
    for(int i = 1;i <= m;i++){
        edg[i] = make_pair(read(),read());
        if(edg[i].first != 1)state1 = false;
        if(edg[i].first != i)state2 = false;
    }
    if(k == 1){printf("%lld\n",qpow(2,n - 2) * m % mod);return 0;}

    pw[0] = 1;invpw[0] = 1;
    for(int i = 1;i <= n;i++){pw[i] = pw[i - 1] * i % mod;}
    invpw[n] = qpow(pw[n],mod - 2);
    for(int i = n - 1;i;i--){invpw[i] = invpw[i + 1] * (i + 1) % mod;}
    if(state1){
        int ans = 0;
        for(int i = 1;i <= m;i++){
            ans = (ans + C(n - 1,i) * qpow(i,k) % mod) % mod;
        }
        printf("%lld\n",ans);
    }
    if(state2){
        int ans = qpow(m,k);
        printf("%lld\n",ans);
    }
    return 0;
}