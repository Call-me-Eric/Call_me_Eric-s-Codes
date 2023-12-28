#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 3) + (x << 1) + ch - '0';ch = getchar();}
    return x * f;
}
int n, m, ans;
int e[110][110][25];
void dfs(int step,int day,int cost){
    if(day == m + 1){
        if(step == n){
            ans = min(ans,cost);
        }
        return;
    }
    if(cost > ans)return;
    for(int i = 1;i <= n;i++){
        if(i == step)continue;
        if(e[step][i][0] && e[step][i][(day - 1) % e[step][i][0] + 1]){
            dfs(i,day + 1,cost + e[step][i][(day - 1) % e[step][i][0] + 1]);
        }
    }
    return;
}
signed main(){
    freopen("lines.in","r",stdin);
    freopen("lines.out","w",stdout);
    n = read(); m = read();
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= n;j++){
            if(j == i){e[i][j][0] = 0;}
            else e[i][j][0] = read();
            for(int T = 1;T <= e[i][j][0];T++){
                e[i][j][T] = read();
            }
        }
    }
    ans = 0x3f3f3f3f;
    dfs(1,1,0);
    if(ans == 0x3f3f3f3f){puts("0");}
    else printf("%d\n",ans);
    return 0;
}