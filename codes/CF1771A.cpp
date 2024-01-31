#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
const int maxn = 1e5 + 10;
int n;
signed main(){
    int T = read();
while(T--){
    n = read();int mx = -1,mxtime = 0,mn = 0x3f3f3f3f,mntime = 0,u;
    for(int i = 1;i <= n;i++){
        u = read();
        if(u > mx){mxtime = 1;mx = u;}
        else if(u == mx){mxtime++;}
        if(u < mn){mntime = 1;mn = u;}
        else if(u == mn){mntime++;}
    }
    if(mn != mx)printf("%lld\n",mxtime * mntime * 2ll);
    else printf("%lld\n",n * (n - 1));
}
    return 0;
}