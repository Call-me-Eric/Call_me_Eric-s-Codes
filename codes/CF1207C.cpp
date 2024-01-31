#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f  = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch= getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 2e5 + 10;
int f[maxn][2];
int n, a, b;
char ch[maxn];
signed main(){
int T = read();
while(T--){
    memset(f,0x3f,sizeof f);
    n = read(); a = read(); b = read();
    scanf("%s",ch + 1);f[0][0] = b;
    for(int i = 1;i <= n;i++){
        f[i][0] = min(f[i - 1][0] + a + b,f[i - 1][1] + 2LL * a + b);
        f[i][1] = min(f[i - 1][0] + 2LL * a + 2LL * b,f[i - 1][1] + a + 2LL * b);
        if(ch[i] == '1' || ch[i + 1] == '1')f[i][0] = 0x3f3f3f3f3f3f3f3f;
    }
    // for(int i = 1;i <= n;i++){printf("i=%lld:%lld %lld\n",i,f[i][0],f[i][1]);}
    printf("%lld\n",f[n][0]);
}
    return 0;
}