#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 210;
int n, k;int a[maxn], b[maxn];
int dp[maxn][12810];//dp[i][j][k] = 当前到第i个数，选了j个数，5的因数为k个时2的因数最大值
signed main(){
    n = read();k = read();int x = 0;
    for(int i = 1;i <= n;i++){
        x = read();if(!x)continue;
        while(x % 2 == 0){a[i]++;x /= 2;}
        while(x % 5 == 0){b[i]++;x /= 5;}
    }
    memset(dp,~0x3f,sizeof(dp)); dp[0][0] = 0;
    for(int i = 1;i <= n;i++)
        for(int j = k;j >= 1;j--)
            for(int l = 12800;l >= b[i];l--)
                dp[j][l] = max(dp[j][l],dp[j - 1][l - b[i]] + a[i]);
    int ans = 0;
    for(int i = 0;i <= 12800;i++){ans = max(ans,min(i,dp[k][i]));}
    printf("%lld\n",ans);
    return 0;
}