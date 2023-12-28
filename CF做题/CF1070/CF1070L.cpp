#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 2048;
bitset<maxn> f[maxn];
int n, m, d[maxn];
bool ans[maxn];
void solve(){
    n = read(); m = read();int u, v, cnt = 1;
    for(int i = 1;i <= n;i++){f[i].reset();d[i] = 0;ans[i] = 0;}
    for(int i = 1;i <= m;i++){
        u = read(); v = read();
        f[u].set(v); f[v].set(u);
        d[u]++; d[v]++;
    }
    for(int i = 1;i <= n;i++)cnt &= (!(d[i] & 1));
    if(cnt){puts("1");for(int i = 1;i <= n;i++){putchar('1');putchar(' ');}puts("");return;}
    for(int i = 1;i <= n;i++){
        f[i][n + 1] = f[i][i] = (d[i] & 1);
    }
    for(int i = 1;i <= n;i++){
        for(int j = i;j <= n;j++)
            if(f[j][i]){swap(f[j],f[i]);break;}
        for(int j = i + 1;j <= n;j++)
            if(f[j][i]){f[j] ^= f[i];}
    }
    // for(int i = 1;i <= n;i++){
    //     for(int j = 1;j <= n + 1;j++)
    //         putchar('0' + f[i][j]);
    //     puts("");
    // }
    puts("2");
    for(int i = n;i;i--){
        ans[i] = f[i][n + 1];
        for(int j = i + 1;j <= n;j++){
            ans[i] ^= (f[i][j] & ans[j]);
        }
    }
    for(int i = 1;i <= n;i++){putchar('1' + ans[i]);putchar(' ');}
    puts("");
}
signed main(){
    int T = read();
    while(T--)solve();
    return 0;
}