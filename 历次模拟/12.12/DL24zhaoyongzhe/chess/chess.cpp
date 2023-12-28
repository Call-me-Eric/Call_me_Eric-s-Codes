#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 2e3 + 10, mod = 1e9 + 7;
const int dx[4] = { 1, 0, 0,-1};
const int dy[4] = { 0, 1,-1, 0};
int n, m;
char ch[maxn][maxn];
int qpow(int x,int a){
    int res = 1;
    while(a){
        if(a & 1)res = res * x % mod;
        x = x * x % mod;a >>= 1;
    }
    return res;
}
signed main(){
    freopen("chess.in","r",stdin);
    freopen("chess.out","w",stdout);
    n = read(); m = read();int cnt = 0;
    for(int i = 1;i <= n;i++)
        scanf("%s",ch[i] + 1);
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            for(int k = 0;k < 4;k++){
                int nx = i + dx[k], ny = j + dy[k];
                if(nx < 1 || nx > n || ny < 1 || ny > m)continue;
                if(ch[nx][ny] != ch[i][j]){cnt++;break;}
            }
        }
    }
    cnt = n * m - cnt;
    printf("%lld\n",qpow(2,cnt));
    return 0;
}