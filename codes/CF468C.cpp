#include<bits/stdc++.h>
using namespace std;
signed main(){
    long long mod; cin >> mod;
    long long p =  (long long)(1e18) % mod * 9LL % mod * 9LL % mod;
    printf("%lld %lld\n",(mod - p),(long long)1e18 - p + mod - 1);
    return 0;
}