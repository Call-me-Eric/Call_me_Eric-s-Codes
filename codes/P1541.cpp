#include<bits/stdc++.h>
using namespace std;
int n, m;
int g[5];
int dp[50][50][50][50];
int a[350], b[350];
int main(){
    scanf("%d%d",&n,&m);
    for(int i = 1;i <= n;i++){
        scanf("%d",&a[i]);
    }
    for(int i = 1;i <= m;i++){
        scanf("%d",&b[i]);
        g[b[i]]++;
    }
    dp[0][0][0][0] = a[1];
    for(int i = 0;i <= g[1];i++){
        for(int j = 0;j <= g[2];j++){
            for(int k = 0;k <= g[3];k++){
                for(int l = 0;l <= g[4];l++){
                    int tmp = 1 + i*1 + j*2 + k*3 + l*4;
                    //PS:because the start is 1 but not 0,
                    //so we need add 1 to make sure it starts from 1
                    if(i != 0)dp[i][j][k][l] = max(dp[i][j][k][l],dp[i - 1][j][k][l] + a[tmp]);
                    if(j != 0)dp[i][j][k][l] = max(dp[i][j][k][l],dp[i][j - 1][k][l] + a[tmp]);
                    if(k != 0)dp[i][j][k][l] = max(dp[i][j][k][l],dp[i][j][k - 1][l] + a[tmp]);
                    if(l != 0)dp[i][j][k][l] = max(dp[i][j][k][l],dp[i][j][k][l - 1] + a[tmp]);
                }
            }
        }
    }
    printf("%d\n",dp[g[1]][g[2]][g[3]][g[4]]);
    return 0;
}