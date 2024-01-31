#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
int n, s;
bool check(int x){
    int tmp = x, res = 0;
    while(tmp){res += tmp % 10;tmp /= 10;}
    return x - res >= s;
}
signed main(){
    n = read(); s = read();int ans = max(n - s - 9 * 18,0LL);
    for(int i = 0;i <= 9 * 18 && s + i <= n;i++){if(check(s + i))ans++;}
    printf("%lld\n",ans);
    return 0;
}