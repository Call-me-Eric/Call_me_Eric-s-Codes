#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0 , f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e6 + 10;
int n, m;
int a[maxn], L;
int c[maxn], sum[maxn];
signed main(){
int T = read();
while(T--){
    n = read(); m = read();int ans = 0;
    for(int i = 1;i <= n;i++){ans += abs(a[i] = read());}
    L = read();for(int i = 2;i <= m;i++)L = __gcd(L,read());
    for(int i = 0;i < L;i++){c[i] = 0;sum[i] = 0x3f3f3f3f;}
    
    for(int i = 1;i <= n;i++){c[i % L] += (a[i] < 0);sum[i % L] = min(sum[i % L],abs(a[i]));}
    for(int i = 0;i < L;i++){if(c[i] & 1){ans -= sum[i] * 2;}}
    int ans1 = ans;ans = 0;
    for(int i = 0;i < L;i++){a[i + 1] = -a[i + 1];c[i] = 0;sum[i] = 0x3f3f3f3f;}
    for(int i = 1;i <= n;i++)ans += abs(a[i]);
    for(int i = 1;i <= n;i++){c[i % L] += (a[i] < 0);sum[i % L] = min(sum[i % L],abs(a[i]));}
    for(int i = 0;i < L;i++){if(c[i] & 1){ans -= sum[i] * 2;}}
    printf("%lld\n",max(ans,ans1));
}
    return 0;
}