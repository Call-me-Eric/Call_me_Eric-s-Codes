#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch  = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10;
int a[maxn], n, m, k, suf[maxn];
int calc(int i,int j){return m * (j - i) - (i + j - 1) * (j - i) / 2;}

signed main(){
    freopen("biscuit.in","r",stdin);
    freopen("biscuit.out","w",stdout);
    n = read(); m = read(); k = read();
    for(int i = 1;i <= n;i++)a[i] = read();
    sort(a + 1,a + 1 + n);
    for(int i = n;i;i--)suf[i] = suf[i + 1] + a[i];
    int ans = 0;
    for(int i = 1;i <= n;i++){
        if(m >= suf[i]){break;}
        if(m >= suf[i + 1] && m < suf[i]){ans += calc(m - a[i],suf[i + 1]);break;}
        ans += calc(m - a[i],m);
    }
    printf("%lld\n",ans);
    return 0;
}