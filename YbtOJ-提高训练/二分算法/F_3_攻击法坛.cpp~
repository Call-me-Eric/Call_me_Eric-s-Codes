#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0';ch = getchar();}
    return x * f;
}
int n, R, G;
const int maxn = 2100;
int a[maxn];
int id1[maxn], id2[maxn];
int dp[maxn][maxn];
bool check(int mid){
    for(int i = 1;i <= n;i++){
        id1[i] = id2[i] = 0;
        for(int j = i;j <= n;j++){
            if(a[j] - a[i] < mid)id1[i] = j;
            if(a[j] - a[i] < mid * 2)id2[i] = j;
        }
        for(int j = 0;j <= G;j++)dp[i][j] = 0;
    }
    for(int i = 0;i <= G;i++)dp[0][i] = 0;
    id1[n + 1] = n;id2[n + 1] = n;
    for(int i = 0;i <= R;i++){
        for(int j = 0;j <= G;j++){
            if(i > 0)dp[i][j] = max(dp[i][j],id1[dp[i - 1][j] + 1]);
            if(j > 0)dp[i][j] = max(dp[i][j],id2[dp[i][j - 1] + 1]);
        }
    }
    return dp[R][G] == n;
}
signed main(){
    n = read(); R = read(); G = read();
    for(int i = 1;i <= n;i++)
        a[i] = read();
    if(G + R >= n){puts("1");return 0;}
    sort(a + 1,a + 1 + n);
    int l = 1, r = 1e9, ans = -1;
    while(l < r){
        int mid = (l + r) >> 1;
        if(check(mid)){r = mid;ans = mid;}
        else l = mid + 1;
    }
    printf("%d\n",l);
    return 0;
}
