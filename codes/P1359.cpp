#include<bits/stdc++.h>
using namespace std;
int n;
const int inf = 0x3f3f3f3f;
int e[201][201];
int ans = inf;
void DP(){
    for(int k = 3;k <= n;k++){
        for(int i = 1;i + k - 1<= n;i++){
            for(int j = i + 1;j < i + k - 1;j++){
                e[i][i + k - 1] = min(e[i][i + k - 1],e[i][j] + e[j][k + i - 1]);
            }
        }
    }
}
void dfs1(int now,int sum){
    if(sum > ans)return;
    if(now == n){
        if(ans > sum) ans = sum;
        return;
    }
    for(int i = now + 1;i <= n;i++){
        dfs1(i,sum + e[now][i]);
    }
}
void dfs(){
    dfs1(1,0);
    e[1][n] = ans;
    return;
}
void floyd(){
    for(int k = 1;k <= n;k++){
        for(int i = 1;i <= n;i++){
            for(int j = 1;j <= n;j++){
                if(e[i][k] + e[k][j] < e[i][j]){
                    e[i][j] = e[i][k] + e[k][j];
                }
            }
        }
    }
}
int main(){
    scanf("%d",&n);
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= n;j++){e[i][j] = inf;
        }
    }
    for(int i = 1;i < n;i++){
        for(int j = i + 1;j <= n;j++){
            scanf("%d",&e[i][j]);
        }
    }
    DP();
    printf("%d",e[1][n]);
    return 0;
}