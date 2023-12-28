#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0';ch = getchar();}
    return x * f;
}
int n;
const int maxn = 1010;
int a[maxn], b[maxn], c[maxn][maxn];
int ans[maxn][maxn];
void work(int x){
    if(x == 1){
        for(int i = 1;i <= c[1][1] + 1;i++){
            for(int j = 1;j < i;j++){
                ans[i][j] = 1;
            }
        }
    }
    else{
        for(int i = 0;i < x;i++){
            c[i][x - 1] = c[x][x] - c[x - i][x];
        }
        work(x - 1);
        for(int i = 1;i <= c[x - 1][x - 1] + 1;i++){
            for(int j = 1;j < i;j++){
                ans[i][j] = !ans[i][j];
            }
        }
        for(int i = c[x - 1][x - 1] + 2;i <= c[1][x] + 1 + c[x - 1][x - 1];i++){
            for(int j = 1;j < i;j++){
                ans[i][j] = 1;
            }
        }
    }
}
signed main(){
    freopen("tournament.in","r",stdin);
    freopen("tournament.out","w",stdout);
    n = read();
    for(int i = 1;i <= n;i++){c[i][n] = read();}
    work(n);
    for(int i = 1;i <= c[n][n] + 1;i++){
        for(int j = 1;j < i;j++){
            ans[j][i] = ans[i][j];
        }
    }
    for(int i = 1;i <= c[n][n] + 1;i++){
        for(int j = 1;j <= c[n][n] + 1;j++){
            printf("%d ",ans[i][j]);
        }
        puts("");
    }
    return 0;
}