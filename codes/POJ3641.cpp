#include<bits/stdc++.h>
using namespace std;
long long p = -1, a = -1;
long long quickpower(long long m,long long n,long long M){
    long long res = 1;
    while(n){
        if(n & 1){
            res = (res * (m % M)) % M;
        }
        n >>= 1;
        m = (m % M) * (m % M) % M;
    }
    return res;
}
bool isprime(long long m){
    for(long long i = 2;i * i <= m;i++){
        if(m % i == 0)return false;
    }
    if(m != 1)return true;
    return false;
}
int main(){
    while(p != 0 && a != 0){
        scanf("%lld%lld",&p,&a);
        if(p == 0 && a == 0)break;
        if(!isprime(p) && (quickpower(a,p,p) == a))
            puts("yes");
        else puts("no");
    }
    return 0;
}