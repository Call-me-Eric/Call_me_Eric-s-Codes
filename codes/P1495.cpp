#include<bits/stdc++.h>
#define ll long long
#define TT long long
using namespace std;
inline TT read(){
    TT x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 3) + (x << 1) + ch - '0';ch = getchar();}
    return x * f;
}
const int maxn = 1e6 + 10;
ll n, a[11], b[11];
ll exgcd(ll a,ll b,ll &x,ll &y){
    if(b == 0){
        x = 1, y = 0;
        return a;
    }
    ll tmp = exgcd(b,a % b,x, y);
    ll t = x; x = y;y = t - a / b * y;
    return tmp;
}
ll CRT(){
    ll M = 1, ans = 0, Mi, Ti, y;
    for(int i = 1;i <= n;i++){
        M = b[i] * M;
    }
    for(int i = 1;i <= n;i++){
        Mi = M / b[i];
        exgcd(Mi, b[i], Ti, y);
        ans = (ans + Mi * Ti * a[i]) % M;
    }
    return (ans % M + M) % M;
}
int main(){
    n = read();
    for(int i = 1;i <= n;i++){
        b[i] = read(); a[i] = read();
    }
    printf("%lld\n", CRT());
    return 0;
}