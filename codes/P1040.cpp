#include<bits/stdc++.h>
using namespace std;
int n;
const int maxn = 40;
long long f[maxn][maxn];//f[i][j] means the best score in [i,j] is f[i][j]
int root[maxn][maxn];//root[i][j] means in [i,j] the root is root[i][j]
void print(int x,int y){
    if(x > y)return;
    printf("%d ",root[x][y]);
    if(x == y)return;
    print(x,root[x][y] - 1);
    print(root[x][y] + 1,y);
    return;
}
int main(){
    scanf("%d",&n);
    for(int i = 1;i <= n;i++){
        scanf("%lld",&f[i][i]);
        f[i][i - 1] = 1;
        root[i][i] = i;
    }
    for(int len = 1;len < n;len++){
        for(int i = 1;i + len <= n;i++){
            int j = i + len;
            f[i][j] = f[i + 1][j] + f[i][i];
            root[i][j] = i;
            for(int k = i + 1;k < j;k++){
                if(f[i][j] < f[i][k - 1] * f[k + 1][j] + f[k][k]){
                    f[i][j] = f[i][k - 1] * f[k + 1][j] + f[k][k];
                    root[i][j] = k;
                }
            }
        }
    }
    printf("%lld\n",f[1][n]);
    print(1,n);
    return 0;
}