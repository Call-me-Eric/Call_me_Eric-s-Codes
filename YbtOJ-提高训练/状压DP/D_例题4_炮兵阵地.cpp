#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 3) + (x << 1) + ch - '0'; ch = getchar();}
    return x * f;
}
int n, m;
const int maxn = 110, maxm = 10;
int f[1 << maxm][1 << maxm][maxn];
char mapp[maxn][maxm];
int statement[maxn];
int tot[1 << maxm];
int start[1 << maxm];
int cnt;
signed main(){
    scanf("%d%d",&n,&m);
    for(int i = 1;i <= n;i++){
        scanf("%s",mapp[i] + 1);
        for(int j = 1;j <= m;j++){
            statement[i] = (statement[i] << 1) + (mapp[i][j] == 'H');
        }
    }
    start[++cnt] = 0;
    for(int i = 1;i < (1 << m);i++){
        if(i & (i << 1) || i & (i << 2) || i & (i >> 1) || i & (i >> 2))continue;
        start[++cnt] = i;
        int tmp = i;
        while(tmp){
            tot[cnt]++;
            tmp -= tmp & (-tmp);
        }
    }
    //TODO 1

    for(int i = 1;i <= cnt;i++){
        if(start[i] & statement[1])continue;
        f[i][0][1] = tot[i];
    }
    
    //FIXME 1
    
    //TODO 2
    
    for(int i = 1;i <= cnt;i++){
        if(start[i] & statement[2])continue;
        for(int j = 1;j <= cnt;j++){
            if(start[j] & statement[1] || start[i] & start[j])continue;
            f[i][j][2] = tot[i] + tot[j];
        }
    }
    
    //FIXME 2

    //TODO n
    for(int i = 3;i <= n;i++){
        for(int j = 1;j <= cnt;j++){
            if(start[j] & statement[i])continue;
            for(int k = 1;k <= cnt;k++){
                if(start[k] & statement[i - 1] || start[j] & start[k])continue;
                for(int k1 = 1;k1 <= cnt;k1++){
                    if(start[k1] & statement[i - 2] || start[k1] & start[j] || start[k1] & start[k])continue;
                    f[j][k][i] = max(f[j][k][i], f[k][k1][i - 1] + tot[j]);
                }
            }
        }
    }
    //FIXME n
    int ans = 0;
    for(int i = 0;i <= cnt;i++){
        if(start[i] & statement[n])continue;
        for(int j = 0;j <= cnt;j++){
            if(start[j] & statement[n - 1])continue;
            ans = max(ans,f[i][j][n]);
        }
    }
    printf("%d\n",ans);
    return 0;
}