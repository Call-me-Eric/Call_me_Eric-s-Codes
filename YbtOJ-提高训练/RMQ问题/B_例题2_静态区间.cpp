#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 3) + (x << 1) + ch - '0';ch = getchar();}
    return x * f;
}
int n, m;
const int maxn = 5e4 + 10;
int f[maxn][25];
int gcd(int x,int y){if(x < y)swap(x,y);return y == 0 ? x : gcd(y,x % y);}
int query(int x,int y){int k = log2(y - x + 1);return gcd(f[x][k],f[y - (1 << k) + 1][k]);}
signed main(){
    n = read();m = read();
    for(int i = 1;i <= n;i++)f[i][0] = read();
    for(int j = 1;(1 << j) <= n;j++)
        for(int i = 1;i + (1 << j) - 1 <= n;i++)
            f[i][j] = gcd(f[i][j - 1],f[i + (1 << j - 1)][j - 1]);
    for(int i = 1;i <= m;i++){
        int x = read(), y = read();
        printf("%d\n",query(x,y));
    }
    return 0;
}