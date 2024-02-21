#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll mod=998244353;
int n,m;
int a[35];
char mat[35][45];
ll dp[35][35][45][45];
int main(){
    freopen("duel.in","r",stdin);
    freopen("duel.out","w",stdout);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)scanf("%s",mat[i]+1);
    for(int i=1;i<=n+1;i++)for(int j=0;j<=m;j++)for(int k=0;k<=m;k++)dp[i][i-1][j][k]=1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++)if(mat[i][j]=='1')
            if(a[i]==0)for(int k=j+1;k<=m;k++)dp[i][i][j][k]=1;
            else if(a[i]==1)for(int k=1;k<=j;k++)dp[i][i][j][k]=1;
            else for(int k=1;k<=m;k++)dp[i][i][j][k]=1;
        for(int j=1;j<=m;j++)for(int k=1;k<=m;k++)dp[i][i][j][k]=(dp[i][i][j][k]+dp[i][i][j-1][k])%mod;
    }
    for(int l=n;l>=1;l--)
        for(int r=l+1;r<=n;r++){
            for(int i=1;i<=m;i++)
                for(int j=1;j<=m;j++)
                    for(int k=l;k<=r;k++)if(((a[k]!=1&&i+r-l<j)||(a[k]&&i+r-l>=j))&&mat[k][i]=='1')
                        dp[l][r][i][j]=(dp[l][r][i][j]+dp[l][k-1][i-1][max(j-(r-k+1),i)]*dp[k+1][r][i][max(j-(k-l+1),i)])%mod;
            for(int i=1;i<=m;i++)for(int j=1;j<=m;j++)dp[l][r][i][j]=(dp[l][r][i][j]+dp[l][r][i-1][j])%mod;
        }
    printf("%lld\n",dp[1][n][m][1]);
    return 0;
}