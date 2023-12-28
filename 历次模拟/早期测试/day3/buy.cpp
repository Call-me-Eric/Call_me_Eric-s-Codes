#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
using namespace std;
int n, m;
int dp[1010];
int a[1010], v[1010];
int main(){
    scanf("%d%d",&n,&m);
    for(int i = 1;i <= m;i++){
        scanf("%d%d",&v[i],&a[i]);
    }
    for(int i = 1;i <= m;i++){
        for(int j = v[i];j <= n;j++){
            dp[j] = max(dp[j],dp[j - v[i]] + a[i]);
        }
    }
    printf("%d",dp[n]);
    return 0;
}