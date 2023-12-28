#include<bits/stdc++.h>
#define lowbit(x) (x) & (-(x))
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0';ch = getchar();}
    return x * f;
}
int n, m, T;
const int maxn = 1010,mod = 1e9 + 7;
int a[maxn], c[maxn * 4], f[maxn][maxn];
void update(int x,int y){for(;x <= n;x += lowbit(x))c[x] += y;}
int sum(int x){int ans = 0;for(;x;x -= lowbit(x))ans += c[x];return ans;}
signed main(){
    T = read();
    for(int cases = 1;cases <= T;cases++){
        n = read(); m = read();
        memset(a,0,sizeof(a));
        memset(f,0,sizeof(f));
        memset(c,0,sizeof(c));
        for(int i = 1;i <= n;i++){a[i] = read();f[1][i] = 1;}
        for(int i = 2;i <= m;i++){
            memset(c,0,sizeof(c));
            for(int k = 1;k <= n;k++){
                f[i][k] += sum(a[k] - 1);
                f[i][k] %= mod;
                update(a[k],f[i - 1][k]);
            }
        }
        int ans = 0;
        for(int i = 1;i <= n;i++){
            ans += f[m][i];
            ans %= mod;
        }
        printf("Case #%d: %d\n",cases,ans);
    }
    return 0;
}
