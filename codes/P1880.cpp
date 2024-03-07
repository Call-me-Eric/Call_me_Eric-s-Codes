#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0'; ch = getchar();}
    return x * f;
}
const int maxn = 110;
int minn[maxn * 2][maxn * 2], maxx[maxn * 2][maxn * 2],a[maxn * 2][maxn * 2];
int n;
signed main(){
    n = read();
    memset(minn,0x3f,sizeof(minn));
    for(int i = 1;i <= n;i++){a[i][i] = read();minn[i][i] = 0;}
    for(int i = n + 1;i <= n * 2;i++){a[i][i] = a[i - n][i - n];minn[i][i] = 0;}
    for(int len = 1;len < n;len++){
        for(int i = 1;i + len <= n * 2;i++){
            int j = i + len;
            for(int k = i;k < j;k++){
                a[i][j] = a[i][k] + a[k + 1][j];
                minn[i][j] = min(minn[i][j],a[i][j] + minn[i][k] + minn[k + 1][j]);
                maxx[i][j] = max(maxx[i][j],a[i][j] + maxx[i][k] + maxx[k + 1][j]);
            }
        }
    }
    int ans1 = 0x3f3f3f3f, ans2 = -1;
    for(int i = 1;i <= n;i++){
        ans1 = min(minn[i][i + n - 1],ans1);
        ans2 = max(maxx[i][i + n - 1],ans2);
    }
    printf("%d\n%d\n",ans1,ans2);
    return 0;
}