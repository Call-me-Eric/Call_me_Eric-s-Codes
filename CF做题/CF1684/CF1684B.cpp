#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * f;
}
signed main(){
int T = read();
while(T--){
    int a = read(), b = read(), c = read();
    printf("%lld %lld %lld\n",a + b + c,b + c,c);
}
    return 0;
}