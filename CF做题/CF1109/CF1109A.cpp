#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f=  1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
map<int,int> mp1,mp2;
int n;
signed main(){
    n = read();int sum = 0,ans = 0;
    mp2[0]++;
    for(int i = 1;i <= n;i++){
        sum ^= read();
        if(i & 1){ans += mp1[sum];mp1[sum]++;}
        else {ans += mp2[sum];mp2[sum]++;}
    }
    printf("%lld\n",ans);
    return 0;
}