#include<bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define __int128 long long
#endif
#define i128 __int128
#define ll long long
using namespace std;
inline ll read(){
    ll x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}

inline i128 summ(i128 x){return (x + 1) * x / 2;}
inline i128 squu(i128 x){return x * (x + 1) * (2 * x + 1) / 6;}

i128 solve(i128 x,i128 y){
    if(x <= 0 || y <= 0)return 0;
    i128 n = min(x, y);
    i128 ans = summ(n * n);
    if(x > y){
        ans -= (x - y) * summ(y - 1);
        ans += (squu(x) - squu(y)) * y;
    }
    else if(x < y){
        ans += (y - x) * summ(x);
        ans += (squu(y - 1) - squu(x - 1)) * x;
    }
    return ans;
}

signed main(){
int T = read();
while(T--){
    ll xl = read(), yl = read(), xr = read(), yr = read();
    i128 ans = solve(xr,yr) - solve(xl - 1,yr) - solve(xr,yl - 1) + solve(xl - 1,yl - 1);
    if(ans > (i128)1e10){ans = ans % (i128)1e10;printf("...%010lld\n",(ll)ans);}
    else printf("%lld\n",(ll)ans);
}
    // printf("%lld\n",(ll)solve(1,3));
    return 0;
}