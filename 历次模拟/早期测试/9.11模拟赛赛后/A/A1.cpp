#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 3) + (x << 1) + ch - '0'; ch = getchar();}
    return x* f;
}
inline int get_(){
    char s[20];scanf("%s",s);
    int ans = 0;
    for(int i = 0,len = strlen(s);i < len;i++){
        ans |= (1 << (s[i] - '0'));
    }
    return ans;
}
int n, T, k;
const int maxn = 1e3 + 10;
int dp[maxn][maxn], last[maxn][11];
int a[maxn];
signed main(){
    freopen("9.in","r",stdin);
    freopen("A.out","w",stdout);
    T = read();
    while(T--){
        n = read(); k = read();
        memset(dp,128,sizeof(dp));
        for(int i = 1;i <= n;i++){
            a[i] = get_();
        }
        dp[0][0] = 0;
        for(int i = 1;i <= n;i++){
            for(int j = 0;j < 10;j++){
                if(a[i] & (1 << j)){
                    last[i][j] = i;
                }
                else last[i][j] = last[i - 1][j];
            }
        }
        for(int i = 1;i <= n;i++){
            vector<int> id(10);
            for(int j = 0;j < 10;j++){
                id[j] = last[i][j];
            }
            sort(id.rbegin(),id.rend());
            for(int j = 0;j < 10;j++){
                if(id[j] == 0)break;
                for(int z = 0;z <= k;z++){
                    dp[i][z] = max(dp[i][z],dp[i - 1][z]);
                    if(z)dp[i][z] = max(dp[i][z],dp[id[j] - 1][z - 1] + j + 1);
                }
            }
        }
        printf("%d\n",dp[n][k]);
    }
    return 0;
}