#include<bits/stdc++.h>
using namespace std;
char a[1000];
int dp[200][200];
int main(){
    a[0] = '\0';
    while(a[0] != 'e'){
        scanf("%s",a);
        if(a[0] == 'e')break;
        int len = strlen(a);
        memset(dp,0,sizeof(dp));
        for(int k = 1;k < len;k++){
            for(int i = 0;i + k < len;i++){
                int l = i + k;
                if((a[i] == '(' && a[l] == ')') || (a[i] == '[' && a[l] == ']')){
                    dp[i][l] = dp[i + 1][l - 1] + 2;
                }
                for(int j = i;j < l;j++){
                    dp[i][l] = max(dp[i][l],dp[i][j] + dp[j + 1][l]);
                }
            }
        }
        printf("%d\n",dp[0][len - 1]);
    }
    return 0;
}