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
const int maxn = 5e3 + 10, mod = 1e9 + 7;
int n, m;
int sumx[maxn], sumy[maxn];
int dp[maxn][maxn];
int low[maxn][4], upp[maxn][4];
int yl[maxn], yr[maxn];
void maintain(int y,int l,int r){
    if(yl[y] > yr[y])return;
    l = max(l,yl[y]);r = min(r,yr[y]);
    if(l <= r){
        for(int x = yl[y];x < l;x++){
            sumx[x] = (sumx[x] - dp[y][x] + mod) % mod;
            sumy[y] = (sumy[y] - dp[y][x] + mod) % mod;
        }
        for(int x = yr[y];x > r;x--){
            sumx[x] = (sumx[x] - dp[y][x] + mod) % mod;
            sumy[y] = (sumy[y] - dp[y][x] + mod) % mod;
        }
    }
    else{
        for(int x = yl[y];x <= yr[y];x++){
            sumx[x] = (sumx[x] - dp[y][x] + mod) % mod;
            sumy[y] = (sumy[y] - dp[y][x] + mod) % mod;
        }
    }
    yl[y] = l;yr[y] = r;
}
void solve(){
    n = read(); m = read();
    for(int i = 0;i <= n;i++){
        yl[i] = 0;yr[i] = i; sumx[i] = sumy[i] = 0;
        for(int j = 1;j < 4;j++)
            low[i][j] = i,upp[i][j] = 0;
    }
    for(int i = 1;i <= m;i++){
        int l = read(), r = read(), x = read();
        low[r][x] = min(low[r][x],l); upp[r][x] = max(upp[r][x],l);
    }
    for(int i = 0;i <= n;i++)for(int j = 0;j <= n;j++)dp[i][j] = 0;
    sumx[0] = sumy[0] = 3;dp[0][0] = 3;
    int ans = 0;
    for(int i = 1;i <= n;i++){
        int xmin = upp[i][3], xmax = low[i][2];
        int ymin = upp[i][2], ymax = low[i][1];
        for(int y = 0;y < ymin;y++)maintain(y,i,i);
        for(int y = ymax;y < i;y++)maintain(y,i,i);
        for(int y = ymin;y < ymax;y++)maintain(y,xmin,xmax - 1);
        if(i == n){for(int x = xmin;x < xmax;x++)ans = (ans + sumx[x]) % mod;}
        else{
            for(int x = xmin;x < xmax;x++){dp[i][x] = (dp[i][x] + sumx[x]) % mod;}
            for(int y = ymin;y < ymax;y++){dp[i][y] = (dp[i][y] + sumy[y]) % mod;}
            for(int j = 0;j <= i;j++){sumx[j] = (sumx[j] + dp[i][j]) % mod; sumy[i] = (sumy[i] + dp[i][j]) % mod;}
        }
    }
    printf("%lld\n",ans);
}
void main(){int T = read();while(T--)solve();return;}
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