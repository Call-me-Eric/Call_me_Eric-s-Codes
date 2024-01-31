#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10;
int n, m, q;
char ch[maxn];
int L[maxn], R[maxn], U[maxn], D[maxn];
int dp[maxn][2];
signed main(){
    n = read(); m = read(); q = read();
    scanf("%s",ch + 1);for(int i = 1;i <= n;i++)L[i] = (ch[i] == 'B');
    scanf("%s",ch + 1);for(int i = 1;i <= n;i++)R[i] = (ch[i] == 'B');
    scanf("%s",ch + 1);for(int i = 1;i <= m;i++)U[i] = (ch[i] == 'B');
    scanf("%s",ch + 1);for(int i = 1;i <= m;i++)D[i] = (ch[i] == 'B');

    memset(dp,0x3f,sizeof(dp));dp[0][0] = dp[0][1] = 0;
    for(int i = 1;i <= m;i++){dp[0][0] += U[i];dp[0][1] += !U[i];}
    for(int i = 1;i <= n;i++){
        dp[i][0] = min(dp[i - 1][0],dp[i - 1][1] + m) +  L[i] +  R[i];
        dp[i][1] = min(dp[i - 1][1],dp[i - 1][0] + m) + !L[i] + !R[i];
    }
    for(int i = 1;i <= m;i++){dp[n][0] += D[i];dp[n][1] += !D[i];}
    int ans = 0x3f3f3f3f;ans = min(dp[n][0],dp[n][1]);

    memset(dp,0x3f,sizeof(dp));dp[0][0] = dp[0][1] = 0;
    for(int i = 1;i <= n;i++){dp[0][0] += L[i];dp[0][1] += !L[i];}
    for(int i = 1;i <= m;i++){
        dp[i][0] = min(dp[i - 1][0],dp[i - 1][1] + n) +  U[i] +  D[i];
        dp[i][1] = min(dp[i - 1][1],dp[i - 1][0] + n) + !U[i] + !D[i];
    }
    for(int i = 1;i <= n;i++){dp[m][0] += R[i];dp[m][1] += !R[i];}
    ans = min(min(dp[m][0],dp[m][1]),ans);
    printf("%d\n",ans);
    return 0;
}