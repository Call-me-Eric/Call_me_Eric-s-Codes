#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch =  getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
int m, b;
signed main(){
    m = read(); b = read();
    int ans = 0;
    for(int y = 0;y <= b;y++){
        int x = m * (b - y);
        ans = max(ans,(x + 1) * y * (y + 1) / 2 + (x + 1) * x * (y + 1) / 2);
    }
    printf("%lld\n",ans);
    return 0;
}