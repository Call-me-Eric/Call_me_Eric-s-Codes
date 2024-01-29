#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0'; ch = getchar();}
    return x * f;
}
int n, k;
map<int,bool> mp;
signed main(){
    n = read(); k = read();
    int cnt = 0, x = 0;
    for(int i = 2;i * i * i <= n;i++){
        int t = i * i, m = 2;
        while(t <= n / i){
            t *= i;m++;
            if(m < k)continue;
            if(mp[t])continue;
            if((int)sqrtl(t) * sqrtl(t) == t)x++;
            mp[t] = true;cnt++;
        }
    }
    if(k == 1)printf("%lld\n",n);
    else if(k >= 3)printf("%lld\n",cnt + 1);
    else printf("%lld\n",(int)sqrtl(n) + cnt - x);
    return 0;
}