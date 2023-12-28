#include<bits/stdc++.h>
using namespace std;
int n, tot;
int a[2049][2049], f[2049][2049];
signed main(){
    scanf("%d",&n);
    tot = (n + 1) * n / 2;
    bool flag = true;
    for(int i = 1;i <= n;i++){
        if(flag){
            for(int j = 1;j <= i;j++){
                a[i][j] = tot--;
            }
        }
        else {
            for(int j = i;j;j--){
                a[i][j] = tot--;
            }
        }
        flag = !flag;
        f[i][1] = f[i - 1][1] + a[i][1];
        f[i][i] = f[i - 1][i - 1] + a[i][i];
        for(int j = 2;j < i;j++){
            f[i][j] = min(f[i - 1][j], f[i - 1][j - 1]) + a[i][j];
        }
    }
    int ans = 0x3f3f3f3f;
    for(int i = 1;i <= n;i++){ans = min(ans,f[n][i]);}
    printf("%d\n",ans);
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= i;j++){
            printf("%d ",a[i][j]);
        }
        puts("");
    }
    return 0;
}