#include<bits/stdc++.h>
using namespace std;
int n,m;
const int maxn = 55;
int max_(int a,int b,int c,int d){
    if(a < b)a = b;
    if(a < c)a = c;
    if(a < d)a = d;
    return a; 
}
int f[maxn][maxn][maxn][maxn];
int a[maxn][maxn];
int main(){
    scanf("%d%d",&n,&m);
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            scanf("%d",&a[i][j]);
        }
    }
    for(int i = 1;i <= n;i++)
        for(int j = 1;j <= m;j++)
            for(int k = 1;k <= n;k++)
                for(int l = j + 1;l <= m;l++)
                    f[i][j][k][l] = max_(f[i - 1][j][k - 1][l],f[i - 1][j][k][l - 1],f[i][j - 1][k - 1][l],f[i][j - 1][k][l - 1]) + a[i][j] + a[k][l];
    printf("%d\n",f[n][m - 1][n - 1][m]);
    return 0;
}