#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 3e3 + 10;
int n;
char ch[maxn][maxn];
bool a[maxn][maxn], b[maxn][maxn];
bool lf[maxn][maxn], ri[maxn][maxn], down[maxn][maxn];
bool opt[maxn][maxn];
signed main(){
int T = read();
while(T--){
    n = read();
    for(int i = 1;i <= n;i++){
        scanf("%s",ch[i] + 1);
        for(int j = 1;j <= n;j++){
            a[i][j] = ch[i][j] - '0';
            down[i][j] = ri[i][j] = lf[i][j] = opt[i][j] = 0;
        }
    }
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= n;j++){
            if(down[i - 1][j]){down[i][j] ^= 1;}
            if(lf[i - 1][j]){down[i][j - 1] ^= 1;lf[i][j - 1] ^= 1;}
            if(ri[i - 1][j]){down[i][j + 1] ^= 1;ri[i][j + 1] ^= 1;}
        }
        for(int j = 1;j <= n;j++){
            a[i][j] ^= down[i][j];
            // printf("%d ",a[i][j]);
            if(a[i][j]){
                opt[i][j] = 1;a[i][j] ^= 1;
                lf[i][j] ^= 1;down[i][j] ^= 1;ri[i][j] ^= 1;
            }
        }
        // for(int j = 1;j <= n;j++)printf("%d ",down[i][j] + ((int)lf[i][j] << 1) + ((int)ri[i][j] << 2));
        // puts("");
    }
    int ans = 0;
    for(int i = 1;i <= n;i++)
        for(int j = 1;j <= n;j++)
            ans += opt[i][j];
    printf("%d\n",ans);
    // for(int i = 1;i <= n;i++){
    //     for(int j = 1;j <= n;j++)
    //         printf("%d ",opt[i][j]);
    //     puts("");
    // }
}
    return 0;
}