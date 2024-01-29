#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x=  0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e4 + 10, maxm = 5e5 + 10, INF = 0x3f3f3f3f3f3f3f3f;
int n, a[maxn];
int d[maxn], f[maxm];
signed main(){
    int mx = 0;
    n = read();for(int i = 1;i <= n;i++)mx = max(mx,a[i] = read());
    for(int i = 1;i < n;i++)d[i] = a[i + 1] - a[i];
    for(int i = 1;i <= n * mx;i++){f[i] = INF;}
    sort(d + 1,d + n);a[0] = 0;
    for(int i = 1;i < n;i++){
        a[i] = a[i - 1] + d[i];
        if(!d[i])continue;
        for(int j = mx;j + 1;j--){
            if(f[j] == INF)continue;
            f[j + i * d[i]] = min(f[j + i * d[i]],f[j] + 2 * j * d[i] + i * d[i] * d[i]);
            f[j + a[i]] = min(f[j + a[i]],f[j] + a[i] * a[i]);
            mx = max(mx,max(j + i * d[i],j + a[i]));
            f[j] = INF;
        }
    }
    int ans = INF;
    for(int i = 0;i <= mx;i++)if(f[i] != INF)ans = min(ans,f[i] * n - i * i);
    printf("%lld\n",ans);
    return 0;
}