#include<stdio.h>
#include<iostream>
using namespace std;
int a[10][10], n, f[10][10][10][10];
int main(){
    scanf("%d",&n);
    int x = -1,y = -1,t = -1;
    while(x != 0 && y != 0){
        scanf("%d%d%d",&x,&y,&t);
        a[x][y] = t;
    }
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= n;j++){
            for(int k = 1;k <= n;k++){
                for(int l = 1;l <= n;l++){
                    f[i][j][k][l] = max(max(f[i - 1][j][k - 1][l],f[i - 1][j][k][l - 1]),
                    max(f[i][j - 1][k - 1][l],f[i][j - 1][k][l - 1])) + a[i][j] + a[k][l];
                    if(i == k && j == l)f[i][j][k][l] -= a[i][j];
                }
            }
        }
    }
    printf("%d",f[n][n][n][n]);
    return 0;
}