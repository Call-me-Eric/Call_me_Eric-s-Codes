#include<bits/stdc++.h>
#define int long long
using namespace std;
int n, m;
signed main(){
    scanf("%lld%lld",&n,&m);
    int ans = 0;
         if(n == 1){ans = (m / 6) * 6 + (max(m % 6 - 3,0LL) * 2);}
    else if(m == 1){ans = (n / 6) * 6 + (max(n % 6 - 3,0LL) * 2);}
    else if(n == 2){ans = (m == 2 ? 0 : (m == 3 ? 4 : (m == 7 ? 12 : (n * m))));}
    else if(m == 2){ans = (n == 2 ? 0 : (n == 3 ? 4 : (n == 7 ? 12 : (n * m))));}
    else if(n >= 3 && m >= 3 && (n % 2 == 0 || m % 2 == 0)){ans = n * m;}
    else ans = n * m - 1;
    printf("%lld\n",ans);
    return 0;
}