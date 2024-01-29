#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll mod = 1e9 + 7;
ll qpow(ll x,ll a){
    ll res = 1;x = (x + mod) % mod;
    while(a){
        if(a & 1)res = res * x % mod;
        x = x * x % mod;a >>= 1;
    }
    return res;
}
signed main(){
    ll n = 0;char ch = getchar();
    while(ch < '0' || ch > '9'){ch = getchar();}
    while(ch >= '0' && ch <= '9'){n = (n * 10LL + ch - '0') % (mod - 1LL);ch = getchar();}
    printf("%lld\n",(485071604ll * qpow(940286408,n - 1) % mod + 514928404ll * qpow(59713601,n - 1) % mod) % mod); 
    return 0;
}