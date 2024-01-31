#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0'; ch = getchar();}
    return x * f;
}
const int maxn = 500000 + 10, maxm = 1e3 + 10;
int n, q, len;
int a[maxn];
int dp[maxm][maxm];
signed main(){
    int opt, x, y;
    n = 5e5; q = read(); len = sqrt(n);
    while(q--){
        opt = read(); x = read(); y = read();
        if(opt == 1){
            a[x] += y;
            for(long long i = 1;i <= len;i++){
                dp[i][x % i] += y;
            }
        }
        else{
            if(x <= len)printf("%lld\n",dp[x][y % x]);
            else{
                int ans = 0;
                for(long long i = y % x;i <= n;i += x)ans += a[i];
                printf("%lld\n",ans);
            }
        }
    }
    return 0;
}