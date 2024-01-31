#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f =  -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e3 + 10;
const ll mod = 1e9 + 7;
int n, m;
ll f[42][maxn];
signed main(){
    n = read(); m = read();
    for(int i = 1;i <= n;i++)f[1][i] = 1;
    for(int i = 2;i <= m * 2;i++){
        ll sum = 0;
        for(int j = 1;j <= n;j++){
            // printf("%d %d\n",i,j);
            sum += f[i - 1][j];
            if(sum > mod)sum -= mod;
            f[i][j] = sum;
        }
    }
    ll sum = 0;
    for(int i = 1;i <= n;i++){
        sum += f[m * 2][i];if(sum > mod)sum -= mod;
        // printf("%lld\n",f[m * 2][i]);
    }
    printf("%lld\n",sum);
    return 0;
}