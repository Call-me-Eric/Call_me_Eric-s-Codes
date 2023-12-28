#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0';ch = getchar();}
    return x * f;
}
int n, k;
const int maxn = 1e5 + 10, max2 = 30;
int d[maxn][max2 + 1], s[maxn][max2 + 1],mi[maxn][max2 + 1];
signed main(){
    n = read() - 1; k = read();
    for(int i = 0;i <= n;i++){d[i][0] = read();}
    for(int i = 0;i <= n;i++){s[i][0] = mi[i][0] = read();}
    for(int i = 1;i <= max2;i++){
        for(int u = 0;u <= n;u++){
            d[u][i] = d[d[u][i - 1]][i - 1];
            s[u][i] = s[u][i - 1] + s[d[u][i - 1]][i - 1];
            mi[u][i] = min(mi[u][i - 1],mi[d[u][i - 1]][i - 1]);
        }
    }

    for(int i = 0;i <= n;i++){
        int now = i,minn = 1145141919810000,sum = 0;
        for(int j = 0;j <= max2;j++){
            if(k & (1LL << j)){
                sum += s[now][j];
                minn = min(minn,mi[now][j]);
                now = d[now][j];
            }
        }
        printf("%lld %lld\n", sum, minn);
    }
    printf("%lld\n",1145141919810000);
    return 0;
}
