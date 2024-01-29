#include<iostream>
#include<stdio.h>
#include<string.h>
using namespace std;
int dp[2200][2200];
int m, n;
char id[2200];
int w[40];
int main(){
    scanf("%d%d",&n,&m);
    getchar();
    scanf("%s",id);
    getchar();
    for(int i = 1;i <= n;i++){
        char c = getchar();
        int a, b;
        getchar();
        scanf("%d%d",&a,&b);
        getchar();
        w[c - 'a'] = min(a,b);
    }
    for(int i = m - 1;i >= 0;i--){
        for(int j = i + 1;j < m;j++){
            if(id[i] == id[j]){
                dp[i][j] = dp[i + 1][j - 1];
            }
            else{
                dp[i][j] = min(dp[i][j - 1] + w[id[j] - 'a'],dp[i + 1][j] + w[id[i] - 'a']);
            }
        }
    }
    printf("%d",dp[0][m - 1]);
    return 0;
}