#include<iostream>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
using namespace std;
char c[100];
bool S[100][100];
int n, dp[100];
bool cmp(int u,int v,int x,int y){
    for(int i = u,j = x;i <= v && j <= y;i++,j++){
        if(c[i] != c[j])return false;
    }
    return true;
}
int main(){
    freopen("string.in","r",stdin);
    freopen("string.out","w",stdout);
    scanf("%s",c);
    n = strlen(c);
    for(int i = 0;i < n;i++){
        dp[i] = i + 1;
    }
    for(int i = 1;i < n;i++){
        for(int j = (i + 1) / 2;j >= 1;j--){
            if(cmp(i - j + 1,i,i - j - j + 1,i - j)){
                dp[i] = dp[i - j] + 1;
                for(int k = 0;k < n;k++){
                    S[i][k] = S[i - j][k];
                }
                S[i][n] = S[i - j][n] - S[i][i - j - j + 1] + 1;
                S[i][i - j - j + 1] = 1;
            }
        }
    }
    printf("%d\n",dp[n - 1] + S[n - 1][n]);
    return 0;
}