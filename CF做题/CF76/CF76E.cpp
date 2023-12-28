#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10;
int n;
int x[maxn], y[maxn];
int sumx, summx, sumy,summy;
signed main(){
    n = read();
    for(int i = 1;i <= n;i++){
        x[i] = read();y[i] = read();
        sumx += x[i];summx += (x[i] * x[i]);
        sumy += y[i];summy += (y[i] * y[i]);
    }
    int ans = 0;
    for(int i = 1;i <= n;i++){
        ans -= x[i] * (sumx - x[i]);
        ans -= y[i] * (sumy - y[i]);
    }
    ans += (n - 1) * (summx + summy);
    printf("%lld\n",ans);
    return 0;
}