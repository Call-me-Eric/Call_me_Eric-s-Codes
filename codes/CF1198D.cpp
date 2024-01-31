#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) +  (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 55;
int f[maxn][maxn][maxn][maxn];
char ch[maxn][maxn];
int n;
int dfs(int xl,int yl,int xr,int yr){
    if(f[xl][yl][xr][yr] != -1)return f[xl][yl][xr][yr];
    int ans = max(xr - xl + 1,yr - yl + 1);
    for(int i = xl;i < xr;i++)ans = min(ans,dfs(xl,yl,i,yr) + dfs(i + 1,yl,xr,yr));
    for(int i = yl;i < yr;i++)ans = min(ans,dfs(xl,yl,xr,i) + dfs(xl,i + 1,xr,yr));
    return f[xl][yl][xr][yr] = ans;
}
signed main(){
    n = read();
    memset(f,-1,sizeof(f));
    for(int i = 1;i <= n;i++){
        scanf("%s",ch[i] + 1);
        for(int j = 1;j <= n;j++)
            f[i][j][i][j] = ch[i][j] == '#';
    }
    dfs(1,1,n,n);
    printf("%d\n",f[1][1][n][n]);
    return 0;
}