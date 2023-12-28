#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
int n, k;
signed main(){
    n = read();k = read();int lst = 0, ans = 0;
    for(int i = 1;i <= n;i++){
        int x = read();
        if(x + lst <= k && lst != 0){ans++;lst = 0;continue;}
        else{
            if(lst){x -= (k - lst);ans++;}
            ans += x / k;lst = x % k;
        }
    }
    if(lst)ans++;
    printf("%lld\n",ans);
    return 0;
}