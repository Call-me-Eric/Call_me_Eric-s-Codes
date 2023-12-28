#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 13, maxm = 2100;
int n, m;
struct COL{
    int row[maxn], mx;
    void init(){for(int i = 1;i <= n;i++)mx = max(mx,row[i]);}
    friend bool operator < (COL a,COL b){return a.mx > b.mx;}
}a[maxm];
int w[1 << maxn], f[maxn][1 << maxn];
signed main(){
int T = read();
while(T--){
    memset(a,0,sizeof(a));memset(w,0,sizeof(w));memset(f,0,sizeof(f));
    n = read(); m = read();
    for(int i = 1;i <= n;i++)
        for(int j = 1;j <= m;j++)
            a[j].row[i] = read();
    for(int i = 1;i <= m;i++){a[i].init();}
    sort(a + 1,a + 1 + m);
    for(int i = 1;i <= min(n, m);i++){
        for(int j = 0;j < (1 << n);j++){
            w[j] = 0;
            for(int k = 0;k < n;k++){
                int tmp = 0;
                for(int l = 1;l <= n;l++)
                    if(j & (1 << (l - 1)))
                        tmp += a[i].row[(l + k - 1) % n + 1];
                w[j] = max(w[j],tmp);
            }
        }
        for(int j = 0;j < (1 << n);j++){
            f[i][j] = f[i - 1][j];if(i == 1){f[i][j] = w[j];continue;}
            for(int k = j;k;k = (k - 1) & j) f[i][j] = max(f[i - 1][k] + w[k ^ j],f[i][j]);
        }
    }
    printf("%d\n",f[min(n, m)][(1 << n) - 1]);
}
    return 0;
}