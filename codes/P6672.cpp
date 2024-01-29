#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x  = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
int n, m;
const int mod = 998244353;
signed main(){
    n = read();m = 0;int tmp = 1;
    for(int i = 1;i <= n;i++)m += read();
    for(int i = 1;i <= m;i++)if(i != m - n + 1)tmp = tmp * i % mod;
    printf("%lld\n",tmp);
    return 0;
}