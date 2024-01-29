#include<bits/stdc++.h>
using namespace std;
long long ans;
long long a, b;
int H, z;
long long M;
long long quickpower(long long m,long long n){
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
int main(){
    scanf("%d",&z);
    while(z--){
        ans = 0;
        scanf("%lld%d",&M,&H);
        for(int i = 1;i <= H;i++){
            scanf("%lld%lld",&a,&b);
            ans = (ans + quickpower(a,b)) % M;
        }
        printf("%lld\n",ans);
    }
    return 0;
}