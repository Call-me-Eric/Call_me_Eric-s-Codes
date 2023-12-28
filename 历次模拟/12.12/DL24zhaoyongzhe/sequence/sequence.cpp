#include<bits/stdc++.h>
#define int long long 
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 4e3 + 10, mod = 998244353;
bool st;
int w[maxn];
int n;
int sum[101][101][101];
// int summ[101][101];
bool ed;
#define max(x,y) ((x) > (y) ? (x) : (y))
signed main(){
    // cerr << (&ed - &st) / 1024 / 1024 << "Mib" << endl;
    freopen("sequence.in","r",stdin);
    freopen("sequence.out","w",stdout);
    n = read();
    for(int i = 1;i <= n;i++)w[i] = read();
    for(int i = 1;i <= n;i++)
        for(int j = 1;j <= n;j++)
            for(int k = 1;k <= n;k++){
                int tmp = w[max(i,max(j, k))];
                sum[3][i][j] = (sum[3][i][j] + tmp);if(sum[3][i][j] > mod)sum[3][i][j] -= mod;
            }
    for(int i = 4;i <= n;i++){
        for(int j = 1;j <= n;j++){
            for(int k = 1;k <= n;k++){
                for(int w = 1;w <= n;w++){
                    int tmp = (sum[i - 1][k][w] * (::w[max(w,max(j, k))])) % mod;
                    sum[i][j][k] = (sum[i][j][k] + tmp);if(sum[i][j][k] > mod)sum[i][j][k] -= mod;
                }
            }
        }
    }
    int ans = 0;
    for(int i = 1;i <= n;i++)
        for(int j = 1;j <= n;j++)
            ans = (ans + sum[n][i][j]) % mod;
    printf("%lld\n",ans);
    return 0;
}