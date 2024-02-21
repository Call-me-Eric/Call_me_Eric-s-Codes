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
const int maxn = 44, mod = 998244353;
int n, m;
int f[maxn][maxn][maxn][maxn];
int c[maxn];
char ch[maxn][maxn];
void main(){
    n = read(); m = read();
    for(int i = 1;i <= n;i++)c[i] = read();
    for(int i = 1;i <= n;i++)scanf("%s",ch[i] + 1);
    for(int i = 1;i <= n + 1;i++)
        for(int j = 0;j <= m;j++)
            for(int k = 0;k <= m;k++)
                f[i][i - 1][j][k] = 1;
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            if(ch[i][j] == '1'){
                if(c[i] != 1)for(int k = j + 1;k <= m;k++){f[i][i][j][k] = 1;}
                if(c[i] != 0)for(int k = 1;k <= j;k++){f[i][i][j][k] = 1;}
            }
        }
        for(int j = 1;j <= m;j++)
            for(int k = 1;k <= m;k++)f[i][i][j][k] = (f[i][i][j][k] + f[i][i][j - 1][k]) % mod;
    }
    for(int l = n;l;l--)for(int r = l + 1;r <= n;r++){
        for(int i = 1;i <= m;i++)for(int j = 1;j <= m;j++)
            for(int k = l;k <= r;k++)
            if(ch[k][i] == '1' && ((c[k] != 1 && i + r - l < j) || (c[k] && i + r - l >= j)))
                f[l][r][i][j] = (f[l][r][i][j] + f[l][k - 1][i - 1][max(i,j - (r - k + 1))] * f[k + 1][r][i][max(i,j - (k - l + 1))] % mod) % mod;
        for(int j = 1;j <= m;j++)for(int k = 1;k <= m;k++)f[l][r][j][k] = (f[l][r][j][k] + f[l][r][j - 1][k]) % mod;
    }
    printf("%lld\n",f[1][n][m][1]);
    return;
}
};
bool edmemory;
signed main(){
    freopen("duel.in","r",stdin);
    freopen("duel.out","w",stdout);
    auto stclock = clock();
    Call_me_Eric::main();
    auto edclock = clock();
    cerr << (&stmemory - &edmemory) / 1024.0 / 1024.0 << " Mib cost.\n";
    cerr << (edclock - stclock) * 1.0 / CLOCKS_PER_SEC << " Sec cost.\n";
    return 0;
}
/*
5 5
0 1 2 2 2
10100
01000
01000
00010
00001
*/